#pragma once

#include "../link_link/block/block.h"
#include "../link_link/block/player.h"
#include "../link_link/link_link.h"
#include <QWidget>
QT_BEGIN_NAMESPACE
namespace Ui {
  class Game;
}
QT_END_NAMESPACE
class Game : public QWidget {
  Q_OBJECT


  public:
  explicit Game(QWidget *parent = nullptr);
  ~Game() override;

  private:
  Ui::Game *ui;

  signals:
  void exitGame();
  void startGame();

  public slots:
  void elaspe1Second();

  protected:
  void paintEvent(QPaintEvent *event) override;

  public:
  void keyPressEvent(QKeyEvent *event) override;

  private:
  //      link_link::block::Player player;
  link_link::LinkLink gameEngine;
};