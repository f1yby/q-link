#include "game.h"
#include "ui_game.h"
#include <QKeyEvent>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <iostream>
#include <qwidget.h>
Game::Game(QWidget *parent) : QWidget(parent), ui(new Ui::Game) {
  ui->setupUi(this);
  auto *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, QOverload<>::of(&Game::update));
  timer->start(1);
}

Game::~Game() { delete ui; }
void Game::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  gameEngine.render(painter);
}

void Game::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
    case Qt::Key_A:
      gameEngine.manipulate(link_link::Op::Left);
      break;
    case Qt::Key_D:
      gameEngine.manipulate(link_link::Op::Right);
      break;
    case Qt::Key_W:
      gameEngine.manipulate(link_link::Op::Up);
      break;
    case Qt::Key_S:
      gameEngine.manipulate(link_link::Op::Down);
      break;
    case Qt::Key_Space:
      break;
    case Qt::Key_Escape:
      emit exitGame();
      break;
    default:
      
      break;
  }
}
