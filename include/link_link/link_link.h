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
    constexpr static const uint16_t mapSize[2] = {5, 5};

public:
    LinkLink();
    void render(QPainter& qPainter);

private:
    block::Map map;
  };
}// namespace link_link
