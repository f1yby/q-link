//
// Created by jiarui on 8/3/22.
//
#include "block/diamond.h"
using namespace link_link;
using namespace link_link::block;

Reactions Diamond::onCollided() const { return {}; }
void Diamond::render(QPainter &) const {}
Row Diamond::generate() { return {}; }
bool Diamond::operator==(Block &) const { return false; }
bool Diamond::penetratable() const { return false; }
