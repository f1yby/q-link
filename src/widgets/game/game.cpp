#include "game.h"
#include "ui_game.h"
#include <QKeyEvent>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <iostream>
#include <qwidget.h>
#include <string>
Game::Game(QWidget *parent) : QWidget(parent), ui(new Ui::Game) {
  ui->setupUi(this);
  auto *renderTimer = new QTimer(this);
  connect(renderTimer, &QTimer::timeout, this, QOverload<>::of(&Game::update));
  renderTimer->start(1);
  auto *secondTimer = new QTimer(this);
  connect(secondTimer, &QTimer::timeout, this,
          QOverload<>::of(&Game::elaspe1Second));
  secondTimer->start(1000);
}

Game::~Game() { delete ui; }

void Game::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  gameEngine.render(painter);
  ui->time->setText(QString::number(gameEngine.getGameTime()));
  ui->p1Score->setText(QString::number(gameEngine.getP1Score()));
}

void Game::elaspe1Second() { gameEngine.elapse(1); }

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
