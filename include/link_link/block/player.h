#pragma once

#include "block.h"

namespace link_link ::block {
  class Player : public Block {
public:
    [[nodiscard]] Reactions onCollided() const override;
    [[nodiscard]] Reactions onManipulated(Op) const;
    [[nodiscard]] inline bool penetratable() const override { return true; };
    uint64_t id() const override;
    void render(QPainter &) const override;

public:
    static Row generate();

public:
    Point position;
    uint64_t score;

public:
    explicit Player(Point position);
  };

}// namespace link_link::block