//
// Created by jiarui on 8/5/22.
//

//
// Created by jiarui on 8/3/22.
//
#pragma once

#include "block.h"

namespace link_link ::block {
  class Player : public Block {
public:
    [[nodiscard]] Reactions onCollided() const override;
    [[nodiscard]] Reactions onManipulated(Op) const;
    void render(QPainter &) const override;
    uint64_t id() const override;
public:
    static Row generate();
public:
    Point position;
public:
    explicit Player(Point  position);

  };

}// namespace link_link::block