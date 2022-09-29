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
        [[nodiscard]] block::Points genLinkablePath(block::Line) const;
        [[nodiscard]] bool checkLinePenetratable(block::Line) const;
        static block::Points genPenetratableLine(block::Line);
        [[nodiscard]] block::Points findLinkedPair() const;
        [[nodiscard]] bool checkPathable(block::Line) const;

    private:
        uint64_t gameTime;

        uint64_t gameEndStamp;
        uint64_t hintTimeStamp;
        [[nodiscard]] bool isHintEnd() const;

        bool paused;
        [[nodiscard]] bool isPaused() const;



        bool flashing;
        [[nodiscard]] bool isFlashing() const;

        [[nodiscard]] uint64_t getGameTime() const;

    public:
        [[nodiscard]] uint64_t getGameTimeLeft() const;

        [[nodiscard]] uint64_t getP1Score() const;
        [[nodiscard]] uint64_t getP2Score() const;

        [[nodiscard]] bool isGameEnd() const;
        [[nodiscard]] bool isGameSolvable() const;
        void togglePaused();

        void switchToSingle();
        void switchToContest();

        void reset();

    public:
        void save(std::ostream &) const;
        void load(std::istream &);

    };
}// namespace link_link
