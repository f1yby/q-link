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

private:
    QColor qColor;
    Shape shape;
public:
    Diamond(const QColor& qColor,const Shape& shape);
  };

}// namespace link_link::block