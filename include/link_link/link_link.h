//
// Created by jiarui on 8/1/22.
//
#pragma once

#include "block/block.h"
#include "block/type.h"
#include <cstdint>
#include <iostream>
namespace link_link {
    namespace block {
        class Block;
    }

    class LinkLink {
        constexpr static const uint16_t mapSize[2] = {28, 28};

    public:
        enum class GameType { Single, Contest };

    public:
        LinkLink();
        void render(QPainter &qPainter);

    private:
        static block::Map generateBlocks(block::Point size, GameType gameType);

    private:
        block::Map map;
        block::Players players;
        block::Points linkedPath;
        block::Points hintedPoints;
        GameType gameType;

    public:
        void manipulate(Qt::Key key);
        void click(QPointF point);
        void elapse(uint32_t second);

    private:
        void handleReaction(const Reaction &reaction,
                            block::PlayerPointer point);
        void handleCollidedReaction(block::PlayerPointer &colliding,
                                    block::Point &collided,
                                    const Reactions &reactions);

    private:
        block::Points genLinkablePath(block::Line) const;
        bool checkLinePenetratable(block::Line) const;
        static block::Points genPenetratableLine(block::Line);
        block::Points findLinkedPair() const;
        bool checkPathable(block::Line) const;

    private:
        uint64_t gameTime;

        uint64_t gameEndStamp;
        uint64_t hintTimeStamp;

        bool isHintEnd() const;

        bool isP1Freeze() const;
        bool isP2Freeze() const;

        bool isP1Dizzy() const;
        bool isP2Dizzy() const;

        bool paused;
        bool isPaused() const;

        bool flashing;
        bool isFlashing() const;

        uint64_t getGameTime() const;

    public:
        uint64_t getGameTimeLeft() const;

        uint64_t getP1Score() const;
        uint64_t getP2Score() const;

        bool isGameEnd() const;
        void togglePaused();

        void switchToSingle();
        void switchToContest();

        void reset();

    public:
        void save(std::ostream &) const;
        void load(std::istream &);
    };
}// namespace link_link
