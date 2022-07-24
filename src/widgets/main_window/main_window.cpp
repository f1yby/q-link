#include "main_window.h"
#include "menu.h"
#include "ui_main_window.h"
#include <qlayoutitem.h>
#include <qpushbutton.h>
#include <qwidget.h>
#include <qwindowdefs.h>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->horizontalLayout->addWidget(new Menu(this));
}

MainWindow::~MainWindow() { delete ui; }
