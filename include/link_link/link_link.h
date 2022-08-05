//
// Created by jiarui on 8/1/22.
//
#pragma once

#include "block/type.h"
#include "block/block_interface.h"
#include <cstdint>
#include <vector>
namespace link_link {
  namespace block {
    class Block;
  }

  class LinkLink {
    constexpr static const uint16_t mapSize[2] = {28, 38};

public:
    LinkLink();
    void render(QPainter &qPainter);

private:
    block::Map map;
    block::Players players;

public:
    void manipulate(Op op);

private:
    void handleReaction(const Reaction &reaction, block::Point point);
    void handleCollidedReaction(block::PlayerPointer &colliding,
                                block::Point &collided,
                                const Reactions &reactions);
  };
}// namespace link_link
