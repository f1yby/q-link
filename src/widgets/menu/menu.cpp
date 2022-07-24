#include "menu.h"
#include "ui_menu.h"
#include <qpushbutton.h>
#include <qwidget.h>
#include <qwindowdefs.h>

Menu::Menu(QWidget *parent)
    : QWidget(parent), ui(new Ui::Menu) {
  ui->setupUi(this);
  connect(ui->exitButton,&QPushButton::pressed,parentWidget(),&QWidget::close);

}

Menu::~Menu() { delete ui; }
