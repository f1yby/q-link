//
// Created by jiarui on 8/1/22.
//

#include "link_link.h"

#include "block/blank.h"
#include "block/diamond.h"
#include "block/player.h"
#include <memory>
using namespace link_link::block;
using namespace link_link;
link_link::LinkLink::LinkLink()
    : map(generateBlocks({
        mapSize[0],
        mapSize[1],
      })),
      players({std::make_shared<Player>(Point{1, 1})}) {}
void link_link::LinkLink::render(QPainter &qPainter) {
  qPainter.save();
  auto position = players.front()->position;
  qPainter.translate(20 * position.second, 20 * position.first);
  players.front()->render(qPainter);
  qPainter.restore();
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
void link_link::LinkLink::manipulate(link_link::Op op) {
  for (const auto &player: players) {
    auto reactions = player->onManipulated(op);
    for (auto reaction: reactions) {
      handleReaction(reaction, player->position);
    }
  }
}


void link_link::LinkLink::handleReaction(const Reaction &reaction,
                                         Point point) {
  Reactions collidedReactions;
  Point colliding = point;
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
  handleCollidedReaction(players[0], collided,
                         map[collided.first][collided.second]->onCollided());
}
void LinkLink::handleCollidedReaction(PlayerPointer &colliding, Point &collided,
                                      const Reactions &reactions) {
  for (auto i: reactions) {
    switch (i) {
      case Reaction::Penetrate: {
        colliding->position = collided;
      } break;
      case Reaction::Select: {
        if (collided != selectedBlock &&
            map[collided.first][collided.second]->id() ==
              map[selectedBlock.first][selectedBlock.second]->id()) {
          map[collided.first][collided.second] = BlockPointer(new Blank());
          map[selectedBlock.first][selectedBlock.second] =
            BlockPointer(new Blank());
        } else {
          selectedBlock = collided;
        }
      }
      default:
        break;
    }
  }
}