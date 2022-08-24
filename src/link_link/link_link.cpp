#include "link_link.h"
#include "block/blank.h"
#include "block/diamond.h"
#include "block/path.h"
#include "block/player.h"
#include "link_link.h"
#include <iostream>
#include <memory>
#include <random>
#include <spdlog/spdlog.h>
using namespace link_link::block;
using namespace link_link;
using namespace std;
using namespace spdlog;
using namespace Qt;

link_link::LinkLink::LinkLink()
    : map(generateBlocks({
        mapSize[0],
        mapSize[1],
      })),
      players({
        make_shared<Player>(Point{1, 1}, PlayerType::Player1, Point{0, 0}),
      }),
      linkedPath(), gameTime(100), hintTime(0), paused(false) {}

void link_link::LinkLink::render(QPainter &qPainter) {
  //Leave Space for border
  qPainter.save();
  qPainter.translate(1, 1);

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

  //Draw Players
  {

    for (const auto &player: players) {

      qPainter.save();
      auto position = player->position;
      qPainter.translate(20 * position.second, 20 * position.first);
      player->render(qPainter);
      qPainter.restore();

      //Draw Select Mark
      qPainter.save();
      auto selectedBlock = player->selectedPoint;
      if (selectedBlock != Point{0, 0}) {
        qPainter.translate(20 * selectedBlock.second, 20 * selectedBlock.first);
        player->renderSelectedMark(qPainter);
      }
      qPainter.restore();
    }
  }


  //Draw Paths
  for (const auto &i: linkedPath) {
    qPainter.save();
    qPainter.translate(20 * i.second, 20 * i.first);
    Path().render(qPainter);
    qPainter.restore();
  }


  {

    if (!isHintEnd()) {
      for (const auto &i: hintedPoints) {
        qPainter.save();
        qPainter.translate(20 * i.second, 20 * i.first);
        qPainter.drawLine(QLine(1, 1, 19, 19));
        qPainter.drawLine(QLine(1, 19, 19, 1));
        qPainter.restore();
      }
    }
  }


  //Restore qPainter
  qPainter.restore();
}

void link_link::LinkLink::manipulate(Key key) {
  if (isGameEnd()) { return; }
  for (const auto &player: players) {
    auto reactions = player->onManipulated(key);
    for (auto reaction: reactions) { handleReaction(reaction, player); }
  }
}

void link_link::LinkLink::elapse(uint32_t second) {
  if (isGameEnd() || isPaused()) { return; }

  this->gameTime -= second;
  if (!isHintEnd()) { this->hintTime -= second; }
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
  info("Collision: ({}, {}) with ({}, {})", colliding.first, colliding.second,
       collided.first, collided.second);
  handleCollidedReaction(player, collided,
                         map[collided.first][collided.second]->onCollided());
}

void LinkLink::handleCollidedReaction(PlayerPointer &colliding, Point &collided,
                                      const Reactions &reactions) {
  for (const auto &i: reactions) {
    switch (i) {
      case Reaction::Penetrate:
        colliding->position = collided;
        break;
      case Reaction::Select: {
        auto &selectedBlock = colliding->selectedPoint;
        if (collided != selectedBlock &&
            map[collided.first][collided.second]->id() ==
              map[selectedBlock.first][selectedBlock.second]->id()) {
          auto path = genLinkablePath({selectedBlock, collided});
          if (!path.empty()) {
            linkedPath = path;
            map[collided.first][collided.second] =
              BlockPointer(make_shared<Blank>());
            map[selectedBlock.first][selectedBlock.second] =
              BlockPointer(make_shared<Blank>());
            colliding->score += 1;
            if (!isHintEnd()) { hintedPoints = findLinkedPair(); }
            selectedBlock = {0, 0};
            break;
          }
        }
        selectedBlock = collided;
        break;
      }
      case Reaction::ReplaceWithBlank:
        map[collided.first][collided.second] =
          BlockPointer(make_shared<Blank>());
        break;
      case Reaction::PlusOneSecond:
        gameTime += 30;
        break;
      case Reaction::Shuffle: {
        for (auto &i: players) { i->position = {1, 1}; }
        auto size = Point(map.size(), map[0].size());
        Row weight;
        for (auto j = 2, ii = 0; j < size.first - 2; ++j) {
          for (auto i = 2; i < size.second - 2; ++i, ++ii) {
            weight.push_back(map[j][i]);
          }
        }
        static random_device rd;
        shuffle(weight.begin(), weight.end(), default_random_engine(rd()));
        for (auto j = 2, ii = 0; j < size.first - 2; ++j) {
          for (auto i = 2; i < size.second - 2; ++i, ++ii) {
            map[j][i] = weight[ii];
          }
        }
        linkedPath.clear();
      }
      case Reaction::Hint: {
        hintedPoints = findLinkedPair();
        hintTime = 10;
      }
      default:
        break;
    }
  }
}


Points link_link::LinkLink::genLinkablePath(Line line) const {

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
    auto ret = Points();
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
bool link_link::LinkLink::checkLinePenetratable(Line line) const {

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
      info("Penetration: Line (({}, {}), ({}, {})) is inpenetratbale, because "
           "({}, {}) is inpenetratable",
           line.first.first, line.first.second, line.second.first,
           line.second.second, i, j);
      return false;
    }
  }
  info("Penetration: Line (({}, {}), ({}, {})) is penetratbale",
       line.first.first, line.first.second, line.second.first,
       line.second.second);
  return true;
}

Points link_link::LinkLink::genPenetratableLine(Line line) const {
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

uint64_t link_link::LinkLink::getGameTime() const { return gameTime; }

bool link_link::LinkLink::isGameEnd() const { return gameTime == 0; }

bool link_link::LinkLink::isHintEnd() const { return hintTime == 0; }

uint64_t link_link::LinkLink::getP1Score() const { return players[0]->score; }

uint64_t link_link::LinkLink::getP2Score() const {
  return players.size() == 2 ? players[1]->score : 0;
}

static inline bool isDiamond(uint64_t id) {
  if (id % blockType == static_cast<uint64_t>(BlockType::Diamond)) {
    return true;
  }
  return false;
}

Points link_link::LinkLink::findLinkedPair() const {

  // From left to right
  for (auto i = 0; i < map.size(); ++i) {
    for (auto j = 0; j < map[0].size(); ++j) {
      if (map[i][j]->id() != static_cast<uint64_t>(BlockType::Blank)) {
        continue;
      }
      std::map<uint64_t, Point> points;
      auto id = map[i][j - 1]->id();
      if (isDiamond(id)) { points.insert({id, {i, j - 1}}); }

      auto k = j;
      for (; map[i][k]->id() == static_cast<uint64_t>(BlockType::Blank); ++k) {
        auto c = i;
        // Go up
        {
          for (; map[c][k]->id() == static_cast<uint64_t>(BlockType::Blank);
               --c) {}
          auto id = map[c][k]->id();
          auto iter = points.find(id);
          if (iter != points.end()) { return {iter->second, {c, k}}; }
          if (isDiamond(id)) { points.insert({id, {c, k}}); }
        }
        // Go down
        {
          for (c = i;
               map[c][k]->id() == static_cast<uint64_t>(BlockType::Blank);
               ++c) {}
          auto id = map[c][k]->id();
          auto iter = points.find(id);
          if (iter != points.end()) { return {iter->second, {c, k}}; }
          if (isDiamond(id)) { points.insert({id, {c, k}}); }
        }
      }
      id = map[i][k]->id();
      auto iter = points.find(id);
      if (iter != points.end()) { return {iter->second, {i, k}}; }
      j = k;
    }
  }

  //From up to down
  for (auto j = 0; j < map[0].size();) {
    for (auto i = 0; i < map.size(); ++i) {
      if (map[i][j]->id() != static_cast<uint64_t>(BlockType::Blank)) {
        continue;
      }
      std::map<uint64_t, Point> points;
      points.insert({map[i - 1][j]->id(), {i - 1, j}});
      auto k = i;
      for (; map[k][j]->id() == static_cast<uint64_t>(BlockType::Blank); ++k) {
        auto c = i;
        // Go left
        {
          for (; map[k][c]->id() == static_cast<uint64_t>(BlockType::Blank);
               --c) {}
          auto id = map[k][c]->id();
          auto iter = points.find(id);
          if (iter != points.end()) { return {iter->second, {k, c}}; }
          if (isDiamond(id)) { points.insert({id, {k, c}}); }
        }

        // Go right
        {
          for (c = i;
               map[k][c]->id() == static_cast<uint64_t>(BlockType::Blank);
               ++c) {}
          auto id = map[k][c]->id();
          auto iter = points.find(id);
          if (iter != points.end()) { return {iter->second, {k, c}}; }
          if (isDiamond(id)) { points.insert({id, {k, c}}); }
        }
      }
      auto id = map[k][j]->id();
      auto iter = points.find(id);
      if (iter != points.end()) { return {iter->second, {k, j}}; }
      i = k;
    }
  }


  return {};
}

bool link_link::LinkLink::isPaused() const { return paused; }

void link_link::LinkLink::togglePaused() { paused = !isPaused(); };

void link_link::LinkLink::reset() {

  gameTime = 100;
  hintTime = 0;
  paused = false;

  for (auto &player: players) {
    player->score = 0;
    player->selectedPoint = {0, 0};
    player->position = {1, 1};
  }

  linkedPath.clear();

  map = generateBlocks({
    mapSize[0],
    mapSize[1],
  });
}

void link_link::LinkLink::switchToSingle() { players.resize(1); }
void link_link::LinkLink::switchToContest() {
  if (players.size() == 1) {
    players.push_back(
      make_shared<Player>(Point{1, 1}, PlayerType::Player2, Point{0, 0}));
  }
}
