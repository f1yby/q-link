//
// Created by jiarui on 8/4/22.
//
#include "block/wall.h"
using namespace link_link;
using namespace link_link::block;
Reactions Wall::onCollided() const { return {Reaction::Delete}; }
void Wall::render(QPainter &qPainter) const {
  static const QPoints shape = {
    {0, 0},
    {0, 20},
    {20, 20},
    {20, 0},
  };
  qPainter.drawConvexPolygon(&shape[0], shape.size());
}
uint64_t Wall::id() const { return static_cast<uint64_t>(BlockType::Wall); }