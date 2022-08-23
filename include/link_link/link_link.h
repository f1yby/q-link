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
    LinkLink(block::GameMode gameMode);
    void render(QPainter &qPainter);

private:
    block::Map map;
    block::Players players;
    block::Points linkedPath;
    block::Points hintedPoints;

public:
    void manipulate(Qt::Key key);
    void elapse(uint32_t second);

private:
    void handleReaction(const Reaction &reaction, block::PlayerPointer point);
    void handleCollidedReaction(block::PlayerPointer &colliding,
                                block::Point &collided,
                                const Reactions &reactions);

private:
    block::Points genLinkablePath(block::Line) const;
    bool checkLinePenetratable(block::Line) const;
    block::Points genPenetratableLine(block::Line)const;
    block::Points findLinkedPair()const;
    uint64_t gameTime;
    uint64_t hintTime;
    bool isHintEnd() const;

    bool paused;
    bool isPaused() const;

public:
    uint64_t getGameTime() const;
    uint64_t getP1Score() const;
    uint64_t getP2Score() const;

    bool isGameEnd() const;
    void togglePaused();
  };
}// namespace link_link
