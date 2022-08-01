#include "menu.h"
#include "ui_menu.h"
#include <qpushbutton.h>
#include <qtmetamacros.h>
#include <qwidget.h>

Menu::Menu(QWidget *parent) : QWidget(parent), ui(new Ui::Menu) {
  ui->setupUi(this);
  connect(ui->exitButton, &QPushButton::pressed, this,
          [this]() { emit this->exitButtonPushed(); });
  connect(ui->startButton, &QPushButton::pressed, this,
          [this]() { emit this->startGameButtonPushed(); });
}
Menu::~Menu() { delete ui; }
