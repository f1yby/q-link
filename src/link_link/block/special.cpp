#include "special.h"

using namespace link_link;
using namespace link_link::block;

link_link::block::Special::Special(SpecialType type) : type(type) {}

Reactions link_link::block::Special::onCollided() const {
  switch (type) {
    case link_link::block::SpecialType::PlusOneSecond:
      return {
        Reaction::Penetrate,
        Reaction::ReplaceWithBlank,
        Reaction::PlusOneSecond,
      };
    case link_link::block::SpecialType::Shuffle:
      return {
        Reaction::Penetrate,
        Reaction::ReplaceWithBlank,
        Reaction::Shuffle,
      };
    case link_link::block::SpecialType::Hint:
      return {
        Reaction::Penetrate,
        Reaction::ReplaceWithBlank,
        Reaction::Hint,
      };
    default:
      break;
  }
}

uint64_t link_link::block::Special::id() const {
  return static_cast<uint64_t>(BlockType::Special) +
         blockType * (static_cast<uint64_t>(type));
}

void link_link::block::Special::render(QPainter &qPainter) const {
  qPainter.save();
  Shape shape;
  switch (type) {
    case link_link::block::SpecialType::PlusOneSecond:
      shape = Shape::WordT;
      break;
    case link_link::block::SpecialType::Shuffle:
      shape = Shape::WordS;
      break;
    case link_link::block::SpecialType::Hint:
      shape = Shape::WordH;
      break;
    default:
      break;
  }
  auto &points = shapeMap.find(shape)->second;
  qPainter.drawConvexPolygon(&points[0], points.size());
  qPainter.restore();
}

link_link::block::Special::Special(uint64_t id) {
  id /= blockType;
  type = static_cast<SpecialType>(id);
}
