#pragma once
#include <vector>
namespace link_link {

    enum class Reaction {
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown,
        Delete,
        Select,
        Penetrate,
        ReplaceWithBlank,
        PlusOneSecond,
        Shuffle,
        Hint,
        StartFlash,
        Freeze,
        Dizzy,
        None,
    };
    typedef std::vector<Reaction> Reactions;
}// namespace link_link