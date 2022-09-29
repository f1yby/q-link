//
// Created by jiarui on 8/4/22.
//

#pragma once
#include "block.h"
namespace link_link ::block {
    class Wall : public Block {
    public:
        [[nodiscard]] Reactions onCollided() const override;
        [[nodiscard]] uint64_t id() const override;
        [[nodiscard]] inline bool penetratable() const override
        {
            return false;
        };
        void render(QPainter &) const override;
    };

}// namespace link_link::block