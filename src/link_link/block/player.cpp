//
// Created by jiarui on 8/3/22.
//
#include "block/player.h"

#include "block/type.h"
#include <utility>

using namespace link_link;
using namespace link_link::block;

Reactions Player::onCollided() const { return {}; }
Reactions Player::onManipulated(Op op) const {
  Reactions reactions;
  switch (op) {
    case Op::Left:
      reactions.push_back(Reaction::MoveLeft);
      break;
    case Op::Right:
      reactions.push_back(Reaction::MoveRight);
      break;
    case Op::Up:
      reactions.push_back(Reaction::MoveUp);
      break;
    case Op::Down:
      reactions.push_back(Reaction::MoveDown);
      break;
    case Op::Select:
      break;
  }

  return reactions;
}
void Player::render(QPainter &qPainter) const {
  static const QPoints shape = {
    {10, 2},
    {2, 18},
    {18, 18},
  };
  qPainter.drawConvexPolygon(&shape[0], shape.size());
}
Row Player::generate() { return {}; }
Player::Player(Point position) : position(std::move(position)) {}
uint64_t Player::id() const { return static_cast<uint64_t>(BlockType::Player); }
