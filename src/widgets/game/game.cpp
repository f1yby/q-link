#include "game.h"
#include "ui_game.h"
#include <qwidget.h>

Game::Game(QWidget *parent) : QWidget(parent), ui(new Ui::Game) {
}

Game::~Game() {
  delete ui;
}
