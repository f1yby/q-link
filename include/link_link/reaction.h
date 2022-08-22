//
// Created by jiarui on 8/2/22.
//

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
    None,
  };
  typedef std::vector<Reaction> Reactions;
}// namespace link_link