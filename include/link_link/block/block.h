//
// Created by jiarui on 8/3/22.
//
#pragma once
#include "type.h"
#include <QPainter>
namespace link_link::block {
  class Block {
public:
    virtual void render(QPainter &qPainter) const = 0;
    [[nodiscard]] virtual Reactions onCollided() const = 0;
    inline bool operator==(Block &block) const {
      return this->id() == block.id();
    };
    [[nodiscard]] virtual uint64_t id() const = 0;
  };

}// namespace link_link::block