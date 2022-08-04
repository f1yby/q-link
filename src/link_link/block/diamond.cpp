//
// Created by jiarui on 8/3/22.
//
#include "block/diamond.h"
using namespace link_link;
using namespace link_link::block;

Reactions Diamond::onCollided() { return {Reaction::None}; }
bool Diamond::manipulatable() { return true; }
Reactions Diamond::onManipulated(Op op) { return {Reaction::None}; }
void Diamond::render(QPainter &) {}
Row Diamond::generate() {


  return {}; }
