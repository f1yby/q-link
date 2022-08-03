#include "main_window.h"
#include "../link_link/link_link.h"
#include "menu.h"
#include "ui_main_window.h"
#include <iostream>
#include <qwidget.h>
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::MainWindow), menu(new Menu(this)),
      game(new Game(this)) {
  ui->setupUi(this);
  ui->horizontalLayout->addWidget(menu);
  ui->horizontalLayout->addWidget(game);
  connect(menu, &Menu::exitButtonPushed, this, &MainWindow::close);
  connect(menu, &Menu::startGameButtonPushed, this,
          [this]() { switchWidget(game); });
  connect(game, &Game::exitGame, this, [this]() { switchWidget(menu); });
}
MainWindow::~MainWindow() {
  delete ui;
  delete game;
  delete menu;
}
void MainWindow::switchWidget(QWidget *widget) {
  menu->close();
  game->close();
  widget->show();
  widget->focusWidget();
}
void MainWindow::switchToGame() { switchWidget(game); }
void MainWindow::switchToMenu() { switchWidget(menu); }
void MainWindow::keyPressEvent(QKeyEvent *event) {
  std::cout << "parent";
  // game->keyPressEvent(event);
}
