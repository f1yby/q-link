//
// Created by jiarui on 8/3/22.
//
#pragma once
#include "block_interface.h"
namespace link_link ::block {
  class Diamond : public Block {
public:
    Reactions onCollided() override;
    bool manipulatable() override;
    Reactions onManipulated(Op) override;
    void render(QPainter &) override;
    static Row generate();


private:


    QColor qColor;
    Shape shape;
  };

}// namespace link_link::block