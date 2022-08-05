//
// Created by jiarui on 8/4/22.
//

#pragma once
#include "block_interface.h"
namespace link_link ::block {
  class Wall : public Block {
public:
    [[nodiscard]] Reactions onCollided() const override;
    void render(QPainter &) const override;
    bool operator==(Block &) const override;
    static Row generate();
    [[nodiscard]] bool penetratable() const override;
  };

}// namespace link_link::block