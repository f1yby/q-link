#include "game.h"
#include "ui_game.h"
#include <QKeyEvent>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <iostream>
#include <qwidget.h>
Game::Game(QWidget *parent) : QWidget(parent), ui(new Ui::Game) {
  auto *timer = new QTimer(this);
  // 将计时器的超时事件与 AnalogClock 的 update 函数绑定，即一旦计时器时间到了，就会调用一次 update 函数
  connect(timer, &QTimer::timeout, this, QOverload<>::of(&Game::update));
  // 计时器开始计时，每次时间间隔 1000 ms
  timer->start(1);
}

Game::~Game() { delete ui; }
void Game::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  //  painter.setRenderHint(QPainter::Antialiasing);
  //  static const QPoint hourHand[3] = {QPoint(7, 8), QPoint(-7, 8),
  //                                     QPoint(0, -40)};
  //  QColor hourColor(127, 0, 127);
  //  painter.translate(width() / 2.0, height() / 2.0);
  //  painter.save();
  //
  //  painter.setPen(Qt::NoPen);
  //  painter.setBrush(hourColor);
  //  painter.drawConvexPolygon(hourHand, 3);
  //  painter.restore();
  gameEngine.render(painter);
}

void Game::keyPressEvent(QKeyEvent *event) {
  std::cout << "child";
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
