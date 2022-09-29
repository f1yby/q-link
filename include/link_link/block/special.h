#pragma once

#include "block.h"

namespace link_link ::block {

    class Special : public Block {
    public:
    public:
        [[nodiscard]] Reactions onCollided() const override;
        [[nodiscard]] inline bool penetratable() const override
        {
            return true;
        };
        [[nodiscard]] uint64_t id() const override;
        void render(QPainter &qPainter) const override;

    private:
        SpecialType type;

    public:
        explicit Special(SpecialType type);
        explicit Special(uint64_t id);
    };

}// namespace link_link::block