//
// Created by jiarui on 8/3/22.
//
#include "block/player.h"
#include "block/type.h"
using namespace link_link;
using namespace link_link::block;

Reactions Player::onCollided() { return {Reaction::None}; }
bool Player::manipulatable() { return true; }
Reactions Player::onManipulated(Op op) { return {Reaction::None}; }
void Player::render(QPainter &) {}
