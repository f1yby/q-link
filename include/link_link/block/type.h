//
// Created by jiarui on 8/3/22.
//
#pragma once
#include "../operation.h"
#include "../reaction.h"
#include "qpainter.h"
#include "qpoint.h"
#include <map>
#include <vector>

namespace link_link::block {
  class Block;
  class Player;

  enum class BlockType {
    Player,
    Blank,
    Diamond,
    Wall,
    Path,
    Special,
    None,
  };
  constexpr uint64_t blockType = static_cast<uint64_t>(BlockType::None);
  typedef std::pair<int, int> Range;
  typedef std::pair<int, int> Point;
  typedef std::vector<Point> Points;
  typedef std::pair<Point, Point> Line;
  typedef std::vector<QPoint> QPoints;

  typedef std::vector<std::shared_ptr<Block>> Row;
  typedef std::vector<std::shared_ptr<Player>> Players;
  typedef std::shared_ptr<Player> PlayerPointer;
  typedef std::shared_ptr<Block> BlockPointer;
  typedef Row Blocks;
  typedef std::vector<Row> Map;
  extern const std::map<BlockType, Range> blockConstrain;

  enum class Shape { Square, Triangle, Circle, WordT, WordS, WordH };
  extern const std::map<Shape, QPoints> shapeMap;
  extern const uint64_t shapes;
  enum class Color {
    Red,
    Orange,
    Yellow,
    Green,
    Cyan,
    Blue,
    Purple,
  };
  extern const std::map<Color, QColor> colorMap;
  extern const uint64_t colors;

  Map generateBlocks(Point size);

  enum class SpecialType {
    PlusOneSecond,
    Shuffle,
    Hint,
  };

}// namespace link_link::block