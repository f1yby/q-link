#include "player.h"
//
// Created by jiarui on 8/3/22.
//
#include "block/player.h"

#include "block/type.h"
#include <iostream>
#include <map>
using namespace link_link;
using namespace link_link::block;
using namespace std;
using namespace Qt;

Reactions Player::onCollided() const { return {}; }
Reactions Player::onManipulated(Key key) const {
  Reactions reactions;

  switch (player) {
    case link_link::block::PlayerType::Player1:
      switch (key) {
        case Key_A:
          reactions.push_back(Reaction::MoveLeft);
          break;
        case Key_D:
          reactions.push_back(Reaction::MoveRight);
          break;
        case Key_W:
          reactions.push_back(Reaction::MoveUp);
          break;
        case Key_S:
          reactions.push_back(Reaction::MoveDown);
          break;
      }
      break;
    case link_link::block::PlayerType::Player2:
      switch (key) {
        case Key_Left:
          reactions.push_back(Reaction::MoveLeft);
          break;
        case Key_Right:
          reactions.push_back(Reaction::MoveRight);
          break;
        case Key_Up:
          reactions.push_back(Reaction::MoveUp);
          break;
        case Key_Down:
          reactions.push_back(Reaction::MoveDown);
          break;
      }
      break;
    default:
      break;
  }


  return reactions;
}

void link_link::block::Player::renderSelectedMark(QPainter &qPainter) const {
  static const map<PlayerType, QLine> lines = {
    {
      PlayerType::Player1,
      {
        {10, 2},
        {10, 18},
      },
    },
    {
      PlayerType::Player2,
      {
        {2, 10},
        {18, 10},
      },
    },
  };
  auto line = lines.find(player)->second;
  qPainter.drawLine(line);
}

void Player::render(QPainter &qPainter) const {

  auto shape = QPoints{
    {10, 2},
    {2, 10},
    {10, 18},
    {18, 10},

  };
  qPainter.drawConvexPolygon(&shape[0], shape.size());

  static const map<PlayerType, QLine> lines = {
    {
      PlayerType::Player1,
      {
        {10, 2},
        {10, 18},
      },
    },
    {
      PlayerType::Player2,
      {
        {2, 10},
        {18, 10},
      },
    },
  };
  auto line = lines.find(player)->second;
  qPainter.drawLine(line);
}

Row Player::generate() { return {}; }

Player::Player(Point position, PlayerType player, Point selectedPoint)
    : position(std::move(position)), score(0), player(player),
      selectedPoint(selectedPoint) {}

uint64_t Player::id() const { return static_cast<uint64_t>(BlockType::Player); }

void Player::save(ostream &out) {
  out << score << ' ';
  out << position.first << ' ';
  out << position.second << ' ';
  out << selectedPoint.first << ' ';
  out << selectedPoint.second << ' ';
}