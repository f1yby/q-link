#include "link_link.h"
#include "block/blank.h"
#include "block/diamond.h"
#include "block/path.h"
#include "block/player.h"
#include "link_link.h"
#include <iostream>
#include <memory>
using namespace link_link::block;
using namespace link_link;
using namespace std;


link_link::LinkLink::LinkLink()
    : map(generateBlocks({
        mapSize[0],
        mapSize[1],
      })),
      players({std::make_shared<Player>(Point{1, 1})}), linkedPath(),
      second(100) {}
void link_link::LinkLink::render(QPainter &qPainter) {
  //Leave Space for border
  qPainter.save();
  qPainter.translate(1, 1);

  //Draw Players
  {
    qPainter.save();
    auto position = players.front()->position;
    qPainter.translate(20 * position.second, 20 * position.first);
    players.front()->render(qPainter);
    qPainter.restore();
  }


  //Draw Paths
  for (const auto &i: linkedPath) {
    qPainter.save();
    qPainter.translate(20 * i.second, 20 * i.first);
    Path().render(qPainter);
    qPainter.restore();
  }

  //Draw Diamonds
  {
    qPainter.save();
    for (auto &i: map) {
      qPainter.save();
      for (auto &j: i) {
        j->render(qPainter);
        qPainter.translate(20, 0);
      }
      qPainter.restore();
      qPainter.translate(0, 20);
    }
    qPainter.restore();
  }

  //Draw Select Mark
  {
    qPainter.save();
    if (selectedBlock != Point{0, 0}) {
      qPainter.translate(20 * selectedBlock.second, 20 * selectedBlock.first);
      qPainter.drawLine(QLine(10, 1, 10, 19));
    }

    qPainter.restore();
  }

  //Restore qPainter
  qPainter.restore();
}
void link_link::LinkLink::manipulate(link_link::Op op) {
  if (isEnd()) { return; }
  for (const auto &player: players) {
    auto reactions = player->onManipulated(op);
    for (auto reaction: reactions) { handleReaction(reaction, player); }
  }
}

void link_link::LinkLink::elapse(uint32_t second) {
  if (!isEnd()) { this->second -= second; }
}


void link_link::LinkLink::handleReaction(const Reaction &reaction,
                                         PlayerPointer player) {
  Reactions collidedReactions;
  Point colliding = player->position;
  Point collided;

  switch (reaction) {
    case Reaction::MoveLeft:
      collided = {colliding.first, colliding.second - 1};
      break;
    case Reaction::MoveRight:
      collided = {colliding.first, colliding.second + 1};
      break;
    case Reaction::MoveUp:
      collided = {colliding.first - 1, colliding.second};
      break;
    case Reaction::MoveDown:
      collided = {colliding.first + 1, colliding.second};
      break;
    default:
      return;
  }
  handleCollidedReaction(player, collided,
                         map[collided.first][collided.second]->onCollided());
}
void LinkLink::handleCollidedReaction(PlayerPointer &colliding, Point &collided,
                                      const Reactions &reactions) {
  for (auto i: reactions) {
    switch (i) {
      case Reaction::Penetrate:
        colliding->position = collided;
        break;
      case Reaction::Select: {
        if (collided != selectedBlock &&
            map[collided.first][collided.second]->id() ==
              map[selectedBlock.first][selectedBlock.second]->id()) {
          auto path = genLinkablePath({selectedBlock, collided});
          if (!path.empty()) {
            linkedPath = path;
            map[collided.first][collided.second] = BlockPointer(new Blank());
            map[selectedBlock.first][selectedBlock.second] =
              BlockPointer(new Blank());
            colliding->score += 1;
            selectedBlock = {0, 0};
            break;
          }
        }
        selectedBlock = collided;
        break;
      }
      case Reaction::ReplaceWithBlank:
        map[collided.first][collided.second] = BlockPointer(new Blank());
        break;
      case Reaction::PlusOneSecond:
        second += 30;
        break;
      default:
        break;
    }
  }
}


vector<Point> link_link::LinkLink::genLinkablePath(Line line) {

  auto first = line.first;
  auto second = line.second;
  bool find = false;
  Point fV;
  Point sV;
  auto yMax = map.size();
  auto xMax = map[0].size();

  for (int i = 0; i < yMax; ++i) {
    auto lines =
      vector<Line>{{{i, first.second}, {i, second.second}},
                   {{i, first.second}, {first.first, first.second}},
                   {{i, second.second}, {second.first, second.second}}};
    bool valid = true;
    for (const auto &line: lines) {
      if (!checkLinePenetratable(line)) {
        valid = false;
        break;
      }
    }
    if (!map[i][first.second]->penetratable() && first.first != i ||
        !map[i][second.second]->penetratable() && second.first != i) {
      valid = false;
    }
    if (!valid) { continue; }
    auto ret = vector<Point>();
    for (const auto &line: lines) {
      auto penetratableLine = genPenetratableLine(line);
      ret.insert(ret.end(), penetratableLine.begin(), penetratableLine.end());
    }
    return ret;
  }

  for (int j = 0; j < xMax; ++j) {
    auto lines =
      vector<Line>{{{first.first, j}, {second.first, j}},
                   {{first.first, j}, {first.first, first.second}},
                   {{second.first, j}, {second.first, second.second}}};
    bool valid = true;
    for (const auto &line: lines) {
      if (!checkLinePenetratable(line)) {
        valid = false;
        break;
      }
    }
    if (!map[first.first][j]->penetratable() && first.second != j ||
        !map[second.first][j]->penetratable() && second.second != j) {
      valid = false;
    }
    if (!valid) { continue; }
    auto ret = vector<Point>();
    for (const auto &line: lines) {
      auto penetratableLine = genPenetratableLine(line);
      ret.insert(ret.end(), penetratableLine.begin(), penetratableLine.end());
    }
    return ret;
  }
  return {};
}
bool link_link::LinkLink::checkLinePenetratable(Line line) {

  int *variable = nullptr;
  auto first = line.first;
  auto second = line.second;
  int i = first.first;
  int j = first.second;
  int end = 0;
  Range mm;
  if (first.first == second.first) {
    mm = minmax({first.second, second.second});
    variable = &j;
  } else if (first.second == second.second) {
    mm = minmax({first.first, second.first});
    variable = &i;
  } else {
    return false;
  }

  for (*variable = mm.first + 1; *variable < mm.second; ++*variable) {
    if (!map[i][j]->penetratable()) {
      cout << "Col: " << j << " Row: " << i << " Inpenetratable" << endl;
      return false;
    }
  }
  return true;
}
vector<Point> link_link::LinkLink::genPenetratableLine(Line line) {
  auto first = line.first;
  auto second = line.second;
  int *variable = nullptr;
  int i = first.first;
  int j = first.second;
  int end = 0;
  Range mm;
  if (first.first == second.first) {
    mm = minmax({first.second, second.second});
    variable = &j;
  } else if (first.second == second.second) {
    mm = minmax({first.first, second.first});
    variable = &i;
  } else {
    return {};
  }
  vector<Point> ret;
  for (*variable = mm.first; *variable <= mm.second; ++*variable) {
    ret.emplace_back(i, j);
  }
  return ret;
}

uint64_t link_link::LinkLink::getTime() { return second; }

bool link_link::LinkLink::isEnd() { return second == 0; }

uint64_t link_link::LinkLink::getP1Score() { return players[0]->score; }