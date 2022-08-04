//
// Created by jiarui on 8/3/22.
//
#include "block/blank.h"
using namespace link_link;
using namespace link_link::block;

Reactions Blank::onCollided() { return {}; }
bool Blank::manipulatable() { return false; }
Reactions Blank::onManipulated(link_link::Op) { return {}; }
void Blank::render(QPainter &qPainter) {
  static const QPoints shape = {
    {0, 0},
    {0, 10},
    {10, 10},
    {10, 0},
  };
  qPainter.drawConvexPolygon(&shape[0], shape.size());
}
Row Blank::generate() { return {}; }
bool Blank::operator==(Block &) { return false; }
