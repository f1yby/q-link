#include "main_window.h"
#include "menu.h"
#include "ui_main_window.h"
#include <qwidget.h>
#include <qwindowdefs.h>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::MainWindow), menu(new Menu(this)),
      game(new Game(this)) {
  ui->setupUi(this);
  ui->horizontalLayout->addWidget(menu);
  ui->horizontalLayout->addWidget(game);
  connect(menu, &Menu::exitButtonPushed, this, &QWidget::close);
  connect(menu, &Menu::startGameButtonPushed, this,
          [this]() { switchWidget(game); });
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
}
