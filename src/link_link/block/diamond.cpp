//
// Created by jiarui on 8/3/22.
//
#include "block/diamond.h"
using namespace link_link;
using namespace link_link::block;

Reactions Diamond::onCollided() const { return {Reaction::Select}; }
void Diamond::render(QPainter &qPainter) const {
  qPainter.save();
  qPainter.setPen(Qt::NoPen);
  qPainter.setBrush(qColor);
  auto points = shapeMap.find(shape)->second;
  qPainter.drawConvexPolygon(&points[0], points.size());
  qPainter.restore();
}
Row Diamond::generate() { return {}; }
Diamond::Diamond(const QColor &qColor, const Shape &shape)
    : qColor(qColor), shape(shape) {}
uint64_t Diamond::id() const {
  return static_cast<uint64_t>(BlockTypes::Diamond);
}
