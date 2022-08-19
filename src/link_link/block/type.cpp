//
// Created by jiarui on 8/3/22.
//
#include "block/type.h"
#include "block/blank.h"
#include "block/block.h"
#include "block/player.h"
#include "block/wall.h"
#include "diamond.h"
#include <random>
using namespace link_link::block;
using namespace QColorConstants::Svg;
using namespace std;
const map<BlockType, Range> link_link::block::blockConstrain{
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

const map<Shape, QPoints> link_link::block::shapeMap{
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
const map<Color, QColor> link_link::block::colorMap = {
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
  vector<BlockPointer> weight;
  uint64_t diamonds = (size.first - 4) * (size.second - 4);
  weight.reserve(diamonds);
  for (auto i = 0; i < diamonds; ++ ++i) {
    weight.push_back(BlockPointer(new Diamond(static_cast<Color>(i % colors),
                                              static_cast<Shape>(i % shapes))));
    weight.push_back(BlockPointer(new Diamond(static_cast<Color>(i % colors),
                                              static_cast<Shape>(i % shapes))));
  }
  random_device rd;
  shuffle(weight.begin(), weight.end(), default_random_engine(rd()));
  for (auto j = 2, ii = 0; j < size.first - 2; ++j) {
    for (auto i = 2; i < size.second - 2; ++i, ++ii) { map[j][i] = weight[ii]; }
  }
  return map;
}
