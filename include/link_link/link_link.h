//
// Created by jiarui on 8/1/22.
//
#pragma once
#include "block/block_interface.h"
#include <vector>
#include <cstdint>
namespace link_link {
  namespace block {
    class Block;
  }

  class LinkLink {
    typedef std::vector<std::vector<block::Block>> Map;
    constexpr static const uint16_t mapSize[2] = {5, 5};

public:
    LinkLink();

private:
    Map map;
  };
}// namespace link_link
