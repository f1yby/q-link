//
// Created by jiarui on 8/3/22.
//
#pragma once
#include "block.h"
namespace link_link ::block {
  class Diamond : public Block {
public:
    [[nodiscard]] Reactions onCollided() const override;
    void render(QPainter &) const override;
    static Row generate();
    [[nodiscard]] uint64_t id() const override;
    [[nodiscard]] inline bool penetratable() const override { return false; };


private:
    Color color;
    Shape shape;

public:
    Diamond(const Color &color, const Shape &shape);
  };

}// namespace link_link::block