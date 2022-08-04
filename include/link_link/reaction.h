//
// Created by jiarui on 8/2/22.
//

#pragma once
#include <vector>
namespace link_link {

  enum class Reaction {

    Delete,
    Select,
    None,
  };
  typedef std::vector<Reaction> Reactions;
}// namespace link_link