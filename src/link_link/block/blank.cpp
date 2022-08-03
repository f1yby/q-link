//
// Created by jiarui on 8/3/22.
//
#include "block/blank.h"
using namespace link_link;
using namespace link_link::block;
Reactions Blank::onCollided() { return {}; }
bool Blank::manipulatable() { return false; }
Reactions Blank::onManipulated(link_link::Op) { return {}; }
void Blank::render(QPainter &) {}
