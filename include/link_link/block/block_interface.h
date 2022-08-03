//
// Created by jiarui on 8/3/22.
//
#pragma once
#include "../link_link.h"
#include "../operation.h"
#include "../reaction.h"
#include <QPainter>
namespace link_link::block {
  class Block {
public:
    virtual void render(QPainter &) = 0;
    virtual Reactions onCollided() = 0;
    virtual bool manipulatable() = 0;
    virtual Reactions onManipulated(Op) = 0;
  };

}// namespace link_link::block