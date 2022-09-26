#include "menu.h"
#include "ui_menu.h"
#include <qpushbutton.h>
#include <qtmetamacros.h>
#include <qwidget.h>

Menu::Menu(QWidget *parent) : QWidget(parent), ui(new Ui::Menu)
{
    ui->setupUi(this);
    connect(ui->exitButton, &QPushButton::pressed, this,
            [this]() { emit this->exitButtonPushed(); });
    connect(ui->singleButton, &QPushButton::pressed, this,
            [this]() { emit this->startSingleGameButtonPushed(); });
    connect(ui->contestButton, &QPushButton::pressed, this,
            [this]() { emit this->startContestGameButtonPushed(); });
}
Menu::~Menu()
{
    delete ui;
}
