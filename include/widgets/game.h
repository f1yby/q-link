#pragma once

#include "../link_link/block/block.h"
#include "../link_link/block/player.h"
#include "../link_link/link_link.h"
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

public slots:
    void elaspe1Second();

protected:
    void paintEvent(QPaintEvent *event) override;
    void renderEndLayout();
    void renderPausedLayout();
    void renderNormalLayout();

public:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

public:
    void switchToSingle();
    void switchToContest();

    void reset();

<<<<<<< HEAD

public:
    void save();
    void load();


    enum class GameStatus{
      Normal,
      Paused,
      End,
    };
=======

public:
    enum class GameStatus {
        Normal,
        Paused,
        End,
    };
>>>>>>> 18a6fc0 (add solvable check)

private:
    GameStatus status;
    link_link::LinkLink gameEngine;
};