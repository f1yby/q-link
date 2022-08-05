//
// Created by jiarui on 8/3/22.
//
#pragma once
#include "type.h"
#include <QPainter>
namespace link_link::block {
  class Block {
public:
    virtual void render(QPainter &) const = 0;
    [[nodiscard]] virtual Reactions onCollided() const = 0;
    virtual bool operator==(Block &) const = 0;
    [[nodiscard]] virtual bool penetratable() const = 0;
  };

}// namespace link_link::block