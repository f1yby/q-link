#pragma once

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
};