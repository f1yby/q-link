//
// Created by jiarui on 8/3/22.
//
#include "block/blank.h"
using namespace link_link;
using namespace link_link::block;

Reactions Blank::onCollided() const { return {Reaction::Penetrate}; }
void Blank::render(QPainter &qPainter) const {}
Row Blank::generate() { return {}; }
bool Blank::operator==(Block &) const { return false; }
bool Blank::penetratable() const { return false; }
