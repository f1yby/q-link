//
// Created by jiarui on 8/1/22.
//

#include "link_link.h"
using namespace link_link::block;
link_link::LinkLink::LinkLink()
    : map(generateBlocks({
        mapSize[0],
        mapSize[1],
      })) {}
void link_link::LinkLink::render(QPainter &qPainter) {
  for (auto &i: map) {
    for (auto &j: i) { j->render(qPainter); }
  }
}
