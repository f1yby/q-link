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
        bool changed;

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
        // Generate the linkable pair
        [[nodiscard]] block::Points genLinkablePath(block::Line) const;
        // Check if any blocks exists in a strait line.
        [[nodiscard]] bool checkLinePenetratable(block::Line) const;
        // Generate a line of all penetratable blocks.
        static block::Points genPenetratableLine(block::Line);
        // Find a pair of blocks that can be linked
        [[nodiscard]] block::Points findLinkedPair() const;
        // Check if user can reach the position
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

        [[nodiscard]] bool isGameEnd();
        [[nodiscard]] bool isGameSolvable();
        void togglePaused();

        void switchToSingle();
        void switchToContest();

        void reset();

        void set_map(block::Map map);

    public:
        void save(std::ostream &) const;
        void load(std::istream &);

    };
}// namespace link_link
