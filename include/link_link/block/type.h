//
// Created by jiarui on 8/3/22.
//
#pragma once

#include "block_interface.h"
#include "player.h"
#include <map>
#include <vector>
namespace link_link::block{
   enum class BlockTypes { Player, Blank, Diamond };
   typedef std::pair<int, int> Range;
   const auto blockConstrain = std::map<BlockTypes, Range>{
     {
       BlockTypes::Player,
       {
         1,
         1,
       },
     },
     {
       BlockTypes::Blank,
       {
         0,
         0,
       },
     },
     {
       BlockTypes::Diamond,
       {
         0,
         0,
       },
     },
   };
   std::vector<Player> generateBlocks(uint32_t size);
 }// namespace link_link::block