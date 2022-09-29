#include "widget/game.h"
#include "ui_game.h"
#include <QFileDialog>
#include <QKeyEvent>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <fstream>
#include <iostream>
#include <qpushbutton.h>
#include <qwidget.h>
#include <spdlog/spdlog.h>
#include <string>
using namespace link_link::block;
using namespace std;
Game::Game(QWidget *parent)
    : QWidget(parent), ui(new Ui::Game), gameEngine(),
      status(GameStatus::Normal)
{
    ui->setupUi(this);
    auto *renderTimer = new QTimer(this);
    connect(renderTimer, &QTimer::timeout, this,
            QOverload<>::of(&Game::update));
    renderTimer->start(1);


    auto *secondTimer = new QTimer(this);
    connect(secondTimer, &QTimer::timeout, this, &Game::elaspe1Second);
    secondTimer->start(1000);

    connect(ui->exit, &QPushButton::pressed, this, [this]() {
        reset();
        emit exitGame();
    });
    connect(ui->save, &QPushButton::pressed, this, [this]() {
        QString filename = QFileDialog::getSaveFileName(
          nullptr, QObject::tr("Save Game"), QDir::currentPath(),
          QObject::tr("Game achive (*.ga)"));
        if (filename.isEmpty()) {
            return;
        }
        ofstream out;
        out.open(filename.toStdString());
        gameEngine.save(out);
        out.close();
    });

    connect(ui->load, &QPushButton::pressed, this, [this]() {
        QString filename = QFileDialog::getOpenFileName(
          nullptr, QObject::tr("Load Game"), QDir::currentPath(),
          QObject::tr("Game achive (*.ga)"));

        if (filename.isEmpty()) {
            return;
        }
        ifstream in;

        in.open(filename.toStdString());
        gameEngine.load(in);
        in.close();
    });
}

Game::~Game()
{
    delete ui;
}

void Game::paintEvent(QPaintEvent *event)
{
    switch (status) {
        case GameStatus::Normal:
            renderNormalLayout();
            break;
        case GameStatus::Paused:
            renderPausedLayout();
            break;
        case GameStatus::End:
            renderEndLayout();
            break;
        default:
            break;
    }
}

void Game::renderNormalLayout()
{
    QPainter painter(this);
    gameEngine.render(painter);

    ui->timeValue->setText(QString::number(gameEngine.getGameTimeLeft()));
    ui->p1Score->setText(QString::number(gameEngine.getP1Score()));
    ui->p2Score->setText(QString::number(gameEngine.getP2Score()));

    ui->title->hide();
    ui->save->hide();
    ui->load->hide();
    ui->exit->hide();

    if (!gameEngine.isGameSolvable()) {
        ui->status->setText("Not Sovable");
        status = GameStatus::End;
    }
    if (gameEngine.isGameEnd()) {
        status = GameStatus::End;
    }
}
void Game::renderPausedLayout()
{
    ui->timeValue->setText(QString::number(gameEngine.getGameTimeLeft()));
    ui->p1Score->setText(QString::number(gameEngine.getP1Score()));
    ui->p2Score->setText(QString::number(gameEngine.getP2Score()));

    ui->title->setText(QString("Paused"));
    ui->title->show();
    ui->save->show();
    ui->load->show();
    ui->exit->show();
}

void Game::renderEndLayout()
{
    ui->timeValue->setText(QString::number(gameEngine.getGameTimeLeft()));
    ui->p1Score->setText(QString::number(gameEngine.getP1Score()));
    ui->p2Score->setText(QString::number(gameEngine.getP2Score()));

    ui->title->setText(QString("Game Over"));
    ui->title->show();
    ui->save->show();
    ui->load->show();
    ui->exit->show();
}


void Game::elaspe1Second()
{
    gameEngine.elapse(1);
}

void Game::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Escape:
            //  emit exitGame();
            status = status == GameStatus::Paused ? GameStatus::Normal
                                                  : GameStatus::Paused;
            gameEngine.togglePaused();
            break;
        default:
            gameEngine.manipulate(static_cast<Qt::Key>(event->key()));
            break;
    }
}

void Game::mousePressEvent(QMouseEvent *event)
{
    spdlog::info("Mouse Pressed: Pos({}, {})", event->position().x(),
                 event->position().y());
    gameEngine.click(event->position());
}

void Game::switchToSingle()
{
    gameEngine.switchToSingle();
}
void Game::switchToContest()
{
    gameEngine.switchToContest();
}

void Game::reset()
{
    status = GameStatus::Normal;
    ui->status->setText("");
    gameEngine.reset();
}