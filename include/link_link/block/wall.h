//
// Created by jiarui on 8/4/22.
//

#pragma once
#include "block.h"
namespace link_link ::block {
  class Wall : public Block {
public:
    [[nodiscard]] Reactions onCollided() const override;
    void render(QPainter &) const override;
    [[nodiscard]] uint64_t id() const override;
    static Row generate();
  };

}// namespace link_link::block