#include "block/path.h"
using namespace link_link;
using namespace link_link::block;
Reactions Path::onCollided() const { return {Reaction::Delete}; }
void Path::render(QPainter &qPainter) const {
  static const QPoints shape = {
    {8, 8},
    {8, 12},
    {12, 12},
    {12, 8},
  };
  qPainter.drawConvexPolygon(&shape[0], shape.size());
}
uint64_t Path::id() const { return static_cast<uint64_t>(BlockType::Path); }