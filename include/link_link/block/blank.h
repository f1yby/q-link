#pragma once
#include "block.h"
namespace link_link ::block {
  class Blank : public Block {
public:
    [[nodiscard]] Reactions onCollided() const override;
    void render(QPainter &) const override;
    [[nodiscard]] uint64_t id() const override;
    [[nodiscard]] inline bool penetratable() const { return true; };

public:
    static Row generate();
  };

}// namespace link_link::block