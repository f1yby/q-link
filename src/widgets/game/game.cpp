#include "game.h"
#include "ui_game.h"
#include <QKeyEvent>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <iostream>
#include <qwidget.h>
#include <spdlog/spdlog.h>
#include <string>
using namespace link_link::block;
Game::Game(QWidget *parent)
    : QWidget(parent), ui(new Ui::Game), gameEngine(GameMode::Contest) {
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
  ui->p2Score->setText(QString::number(gameEngine.getP2Score()));
}

void Game::elaspe1Second() { gameEngine.elapse(1); }

void Game::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
    case Qt::Key_Escape:
      emit exitGame();
      break;
    default:
      gameEngine.manipulate(static_cast<Qt::Key>(event->key()));
      break;
  }
}

void Game::mousePressEvent(QMouseEvent *event) {
  spdlog::info("Mouse Pressed: Pos({}, {})", event->localPos().x(),
               event->localPos().y());
}
