#pragma once

#include "block.h"

namespace link_link ::block {

  class Diamond : public Block {

public:
    [[nodiscard]] Reactions onCollided() const override;
    void render(QPainter &) const override;

    [[nodiscard]] uint64_t id() const override;
    [[nodiscard]] inline bool penetratable() const override { return false; };

public:
    static Row generate();


private:
    Color color;
    Shape shape;

public:
    Diamond(const Color &color, const Shape &shape);
    explicit Diamond(uint64_t id);
  };

}// namespace link_link::block