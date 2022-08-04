//
// Created by jiarui on 8/3/22.
//
#include "block/type.h"
#include "block/blank.h"
#include "block/block_interface.h"
using namespace link_link::block;
using namespace QColorConstants::Svg;
const std::map<BlockTypes, Range> link_link::block::blockConstrain{
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

const std::map<Shape, QPoints> link_link::block::shapeMap{
  {
    Shape::Square,
    {
      {0, 0},
      {0, 10},
      {10, 10},
      {10, 0},
    },
  },
};
const std::vector<QColor> link_link::block::colors = {
  red, orange, yellow, green, cyan, blue, purple,
};
Map link_link::block::generateBlocks(Point size) {
  Map map;
  for (auto j = 0; j < size.first; ++j) {
    map.push_back({});
    for (auto i = 0; i < size.second; ++i) {
      map[j].push_back(std::move(std::unique_ptr<Block>{new Blank()}));
    }
  }


  return map;
}
