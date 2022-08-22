//
// Created by jiarui on 8/1/22.
//
#pragma once

#include "block/block.h"
#include "block/type.h"
#include <cstdint>
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
    block::Points linkedPath;
    block::Points hintedPoints;

public:
    void manipulate(Op op);
    void elapse(uint32_t second);

private:
    void handleReaction(const Reaction &reaction, block::PlayerPointer point);
    void handleCollidedReaction(block::PlayerPointer &colliding,
                                block::Point &collided,
                                const Reactions &reactions);

private:
    block::Points genLinkablePath(block::Line);
    bool checkLinePenetratable(block::Line);
    block::Points genPenetratableLine(block::Line);
    block::Points findLinkedPair();
    uint64_t gameTime;
    uint64_t hintTime;

public:
    uint64_t getGameTime();
    uint64_t getP1Score();
    bool isGameEnd();
    bool isHintEnd();
  };
}// namespace link_link
