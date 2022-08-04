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
  enum class BlockTypes {
    Player,
    Blank,
    Diamond,
  };
  typedef std::pair<int, int> Range;
  typedef std::pair<int, int> Point;
  typedef std::vector<QPoint> QPoints;

  typedef std::vector<std::unique_ptr<Block>> Row;
  typedef std::vector<Row> Map;
  extern const std::map<BlockTypes, Range> blockConstrain;

  enum class Shape {
    Square,
  };
  extern const std::map<Shape, QPoints> shapeMap;
  extern const std::vector<QColor> colors;


  Map generateBlocks(Point size);


}// namespace link_link::block