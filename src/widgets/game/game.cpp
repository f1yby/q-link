#include "game.h"
#include "ui_game.h"
#include <QKeyEvent>
#include <QPainter>
#include <iostream>
#include <qwidget.h>
Game::Game(QWidget *parent) : QWidget(parent), ui(new Ui::Game) {}

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
    case Qt::Key_Left:
      break;
    case Qt::Key_Right:
      break;
    case Qt::Key_Down:
      break;
    case Qt::Key_Up:
      break;
    case Qt::Key_Space:
      break;
    case Qt::Key_A:
      emit exitGame();
      break;
    default:
      QWidget::keyPressEvent(event);
      break;
  }
}
