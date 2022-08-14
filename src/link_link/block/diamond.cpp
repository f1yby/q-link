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
  auto c = colorMap.find(color)->second;
  qPainter.setBrush(c);
  auto points = shapeMap.find(shape)->second;
  qPainter.drawConvexPolygon(&points[0], points.size());
  qPainter.restore();
}
Row Diamond::generate() { return {}; }
Diamond::Diamond(const Color &color, const Shape &shape)
    : color(color), shape(shape) {}
uint64_t Diamond::id() const {
  return static_cast<uint64_t>(BlockType::Diamond) +
         blockType * (static_cast<uint64_t>(shape) +
                      shapes * static_cast<uint64_t>(color));
}
