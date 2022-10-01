#include "link_link/link_link.h"
#include <QtTest>
class GameLogicTest : public QObject {
    Q_OBJECT
private:
    link_link::LinkLink engine;
private slots:
    void check_single_timer_end()
    {
        engine.reset();
        // Init
        QVERIFY(engine.isGameSolvable());
        QVERIFY(!engine.isGameEnd());
        QVERIFY(engine.getGameTimeLeft() == 100);
        QVERIFY(engine.getP1Score() == 0);
        engine.elapse(1);
        QVERIFY(engine.getGameTimeLeft() == 99);
        // Paused
        engine.togglePaused();
        engine.elapse(1);
        QVERIFY(engine.getGameTimeLeft() == 99);
        engine.togglePaused();
        // Time up
        engine.elapse(99);
        QVERIFY(engine.getGameTimeLeft() == 0);
        QVERIFY(engine.isGameEnd());
        QVERIFY(engine.isGameSolvable());
        engine.elapse(1);
        QVERIFY(engine.getGameTimeLeft() == 0);
    }

    void check_duel_timer_end()
    {
        engine.reset();
        engine.switchToContest();
        // Init
        QVERIFY(engine.isGameSolvable());
        QVERIFY(!engine.isGameEnd());
        QVERIFY(engine.getGameTimeLeft() == 100);
        QVERIFY(engine.getP1Score() == 0);
        engine.elapse(1);
        QVERIFY(engine.getGameTimeLeft() == 99);
        // Paused
        engine.togglePaused();
        engine.elapse(1);
        QVERIFY(engine.getGameTimeLeft() == 99);
        engine.togglePaused();
        // Time up
        engine.elapse(99);
        QVERIFY(engine.getGameTimeLeft() == 0);
        QVERIFY(engine.isGameEnd());
        QVERIFY(engine.isGameSolvable());
        engine.elapse(1);
        QVERIFY(engine.getGameTimeLeft() == 0);
    }

    void check_single_score()
    {
        engine.reset();
        // Paused
        engine.togglePaused();
        engine.elapse(1);
        QVERIFY(engine.getGameTimeLeft() == 99);
        engine.togglePaused();
        // Time up
        engine.elapse(99);
        QVERIFY(engine.getGameTimeLeft() == 0);
        QVERIFY(engine.isGameEnd());
        QVERIFY(engine.isGameSolvable());
        engine.elapse(1);
        QVERIFY(engine.getGameTimeLeft() == 0);
    }

public:
};

#include "game_logic.moc"
QTEST_MAIN(GameLogicTest)