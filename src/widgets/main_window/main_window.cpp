#include "main_window.h"
#include "../link_link/link_link.h"
#include "menu.h"
#include "ui_main_window.h"
#include <iostream>
#include <qwidget.h>
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::MainWindow), menu(new Menu(this)),
      game(new Game(this))
{
    ui->setupUi(this);
    ui->horizontalLayout->addWidget(menu);
    ui->horizontalLayout->addWidget(game);
    connect(menu, &Menu::exitButtonPushed, this, &MainWindow::close);

    connect(menu, &Menu::startSingleGameButtonPushed, this,
            &MainWindow::switchToSingleGame);
    connect(menu, &Menu::startContestGameButtonPushed, this,
            &MainWindow::switchToContestGame);


    connect(game, &Game::exitGame, this, &MainWindow::switchToMenu);
    switchWidget(menu);
}
MainWindow::~MainWindow()
{
    delete ui;
    delete game;
    delete menu;
}
void MainWindow::switchWidget(QWidget *widget)
{
    menu->close();
    game->close();
    widget->show();
    widget->setFocus();
}
void MainWindow::switchToSingleGame()
{
    game->switchToSingle();
    switchWidget(game);
}
void MainWindow::switchToContestGame()
{
    game->switchToContest();
    switchWidget(game);
}
void MainWindow::switchToMenu()
{
    switchWidget(menu);
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //game->keyPressEvent(event);
}
