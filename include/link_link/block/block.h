#pragma once
#include "type.h"
#include <QPainter>
namespace link_link::block {
    class Block {
    public:
        virtual void render(QPainter &qPainter) const = 0;
        [[nodiscard]] virtual Reactions onCollided() const = 0;
        [[nodiscard]] virtual uint64_t id() const = 0;
        [[nodiscard]] virtual inline bool penetratable() const = 0;

    public:
        inline bool operator==(Block &block) const
        {return this->id() == block.id();
    };
    [[nodiscard]] inline BlockType getType() const {
      return static_cast<BlockType>(id() % blockType);
    }
  };

}// namespace link_link::block