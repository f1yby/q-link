//
// Created by jiarui on 8/3/22.
//
#include "block/type.h"
#include "block/blank.h"
#include "block/block.h"
#include "block/player.h"
#include "block/wall.h"
#include "diamond.h"
using namespace link_link::block;
using namespace QColorConstants::Svg;
const std::map<BlockType, Range> link_link::block::blockConstrain{
  {
    BlockType::Player,
    {
      1,
      1,
    },
  },
  {
    BlockType::Blank,
    {
      0,
      0,
    },
  },
  {
    BlockType::Diamond,
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
      {0, 20},
      {20, 20},
      {20, 0},
    },
  },
};
const uint64_t link_link::block::shapes = shapeMap.size();
const std::map<Color, QColor> link_link::block::colorMap = {
  {
    Color::Red,
    red,
  },
  {
    Color::Orange,
    orange,
  },
  {
    Color::Yellow,
    yellow,
  },
  {
    Color::Green,
    green,
  },
  {
    Color::Blue,
    blue,
  },
  {
    Color::Cyan,
    cyan,
  },
  {
    Color::Purple,
    purple,
  },
};
const uint64_t link_link::block::colors = colorMap.size();
Map link_link::block::generateBlocks(Point size) {
  Map map;
  for (auto j = 0; j < size.first; ++j) {
    map.push_back({});
    for (auto i = 0; i < size.second; ++i) {
      map[j].push_back(std::shared_ptr<Block>(new Blank()));
    }
  }
  for (auto j = 0; j < size.first; ++j) {
    for (auto i = 0; i < size.second; ++i) {
      if (j == 0 || j == size.first - 1) {
        map[j][i] = std::shared_ptr<Block>(new Wall());
      } else if (i == 0 || i == size.second - 1) {
        map[j][i] = std::shared_ptr<Block>(new Wall());
      }
    }
  }

  for (auto j = 2; j < size.first - 2; ++j) {
    for (auto i = 2; i < size.second - 2; ++i) {
      map[j][i] = std::shared_ptr<Block>(new Diamond(Color::Cyan, Shape::Square));
    }
  }
  return map;
}
