#pragma once

#include "block.h"

namespace link_link ::block {
  class Player : public Block {
public:
    [[nodiscard]] Reactions onCollided() const override;
    [[nodiscard]] inline bool penetratable() const override { return true; };
    uint64_t id() const override;
    void render(QPainter &) const override;

public:
    [[nodiscard]] Reactions onManipulated(Qt::Key) const;
    void renderSelectedMark(QPainter &) const;

public:
    static Row generate();

public:
    Point position;
    uint64_t score;
    Point selectedPoint;
    uint64_t freezedTimeStamp;
    uint64_t dizzyedTimeStamp;

public:
    void save(std::ostream &)const;
    void load(std::istream &);

public:
    explicit Player(Point position, PlayerType player, Point selectedPoint);

private:
    PlayerType player;
  };

}// namespace link_link::block