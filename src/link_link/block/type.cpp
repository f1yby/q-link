//
// Created by jiarui on 8/3/22.
//
#include "block/type.h"
#include "block/blank.h"
#include "block/block.h"
#include "block/player.h"
#include "block/special.h"
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
  {
    Shape::WordT,
    {
      {0, 1},
      {20, 1},
      {20, 5},
      {12, 5},
      {12, 20},
      {8, 20},
      {8, 5},
      {1, 5},
    },
  },
  {
    Shape::WordS,
    {
      {10, 1},
      {14, 5},
      {10, 9},
      {14, 13},
      {10, 19},
      {6, 15},
      {10, 11},
      {6, 7},
    },
  },
  {
    Shape::WordH,
    {
      {0, 1},
      {4, 1},
      {4, 8},
      {16, 8},
      {16, 1},
      {20, 1},
      {20, 20},
      {16, 20},
      {16, 12},
      {4, 12},
      {4, 20},
      {0, 20},
    },
  },
  {
    Shape::WordF,
    {
      {2, 2},
      {18, 2},
      {18, 7},
      {5, 7},
      {5, 10},
      {16, 10},
      {16, 14},
      {5, 14},
      {5, 18},
      {2, 18},
    },
  },
  {
    Shape::Dizzy,
    {
      {1, 10},
      {10, 1},
      {10, 19},
      {19, 10},

    },
  },
};

const uint64_t link_link::block::shapes = 1; // shapeMap.size();

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

BlockPointer link_link::block::generateById(uint64_t id)
{
    auto type = static_cast<BlockType>(id % blockType);
    switch (type) {
        case BlockType::Blank:
            return make_shared<Blank>();
            break;
        case BlockType::Diamond:
            return make_shared<Diamond>(id);
            break;
        case BlockType::Wall:
            return make_shared<Wall>();
            break;
        case BlockType::Special:
            return make_shared<Special>(id);
            break;
        default:
            break;
    }
    return make_shared<Blank>();
}
