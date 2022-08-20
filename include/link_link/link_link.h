//
// Created by jiarui on 8/1/22.
//
#pragma once

#include "block/block.h"
#include "block/type.h"
#include <cstdint>
#include <vector>
namespace link_link {
  namespace block {
    class Block;
  }

  class LinkLink {
    constexpr static const uint16_t mapSize[2] = {28, 28};

public:
    LinkLink();
    void render(QPainter &qPainter);

private:
    block::Map map;
    block::Players players;
    block::Point selectedBlock;
    std::vector<block::Point> linkedPath;

public:
    void manipulate(Op op);
    void elapse(uint32_t second);

private:
    void handleReaction(const Reaction &reaction, block::PlayerPointer point);
    void handleCollidedReaction(block::PlayerPointer &colliding,
                                block::Point &collided,
                                const Reactions &reactions);

private:
    std::vector<block::Point> genLinkablePath(block::Line);
    bool checkLinePenetratable(block::Line);
    std::vector<block::Point> genPenetratableLine(block::Line);
    uint64_t second;

public:
    uint64_t getTime();
    uint64_t getP1Score();
    bool isEnd();
  };
}// namespace link_link
