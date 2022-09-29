#pragma once
#include "block.h"
#include "type.h"
#include <QPainter>
namespace link_link::block {
    class Path : public Block {
    public:
        void render(QPainter &qPainter) const override;
        [[nodiscard]] Reactions onCollided() const override;
        [[nodiscard]] inline bool penetratable() const override
        {
            return true;
        };
        [[nodiscard]] uint64_t id() const override;
    };

}// namespace link_link::block