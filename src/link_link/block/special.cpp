#include "special.h"

using namespace link_link;
using namespace link_link::block;

link_link::block::Special::Special(SpecialType type) : type(type) {}

Reactions link_link::block::Special::onCollided() const {
  return {
    Reaction::Penetrate,
    Reaction::ReplaceWithBlank,
    Reaction::PlusOneSecond,
  };
}

Reactions link_link::block::Special::onManipulated(Op) const {
  return Reactions();
}

uint64_t link_link::block::Special::id() const { return uint64_t(); }

void link_link::block::Special::render(QPainter &qPainter) const {
  qPainter.save();
  auto points = shapeMap.find(Shape::WordT)->second;
  qPainter.drawConvexPolygon(&points[0], points.size());
  qPainter.restore();
}
