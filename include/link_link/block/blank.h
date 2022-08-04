//
// Created by jiarui on 8/3/22.
//
#pragma once
#include "../operation.h"
#include "../reaction.h"
#include "block_interface.h"
namespace link_link ::block {
  class Blank : public Block {
public:
    Reactions onCollided() override;
    bool manipulatable() override;
    Reactions onManipulated(Op) override;
    void render(QPainter &) override;
 bool operator==(Block &)override;
    static Row generate();
  };

}// namespace link_link::block