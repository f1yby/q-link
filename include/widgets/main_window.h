#pragma once

#include "game.h"
#include "menu.h"
#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui {
  class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QWidget {
  Q_OBJECT

  public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;


  private:
  Ui::MainWindow *ui;
  Menu *menu;
  Game *game;

  private:
  void switchWidget(QWidget *widget);

  private slots:
  void switchToGame();
  void switchToMenu();


  protected:
  void keyPressEvent(QKeyEvent *event) override;
};