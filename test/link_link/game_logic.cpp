#include "link_link/block/blank.h"
#include "link_link/block/diamond.h"
#include "link_link/block/special.h"
#include "link_link/block/wall.h"
#include "link_link/link_link.h"
#include <QtTest>
using namespace std;
using namespace link_link::block;
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
        QVERIFY(engine.getGameTimeLeft() == 100);
        engine.togglePaused();
        // Time up
        engine.elapse(100);
        QVERIFY(engine.getGameTimeLeft() == 0);
        QVERIFY(engine.isGameEnd());
        QVERIFY(engine.isGameSolvable());
        engine.elapse(1);
        QVERIFY(engine.getGameTimeLeft() == 0);
    }

    void check_solvable()
    {
        engine.reset();
        engine.set_map({
          {make_shared<Wall>(), make_shared<Wall>(), make_shared<Wall>(),
           make_shared<Wall>()},
          {make_shared<Wall>(), make_shared<Blank>(), make_shared<Blank>(),
           make_shared<Wall>()},
          {make_shared<Wall>(), make_shared<Blank>(), make_shared<Blank>(),
           make_shared<Wall>()},
          {make_shared<Wall>(), make_shared<Wall>(), make_shared<Wall>(),
           make_shared<Wall>()},
        });
        QVERIFY(engine.isGameSolvable() == false);

        engine.set_map({
          {make_shared<Wall>(), make_shared<Wall>(), make_shared<Wall>(),
           make_shared<Wall>()},
          {make_shared<Wall>(), make_shared<Blank>(), make_shared<Blank>(),
           make_shared<Wall>()},
          {make_shared<Wall>(), make_shared<Blank>(),
           make_shared<Special>(SpecialType::Flash), make_shared<Wall>()},
          {make_shared<Wall>(), make_shared<Wall>(), make_shared<Wall>(),
           make_shared<Wall>()},
        });
        QVERIFY(engine.isGameSolvable() == true);

        engine.set_map({
          {make_shared<Wall>(), make_shared<Wall>(), make_shared<Wall>(),
           make_shared<Wall>()},
          {make_shared<Wall>(), make_shared<Blank>(), make_shared<Blank>(),
           make_shared<Wall>()},
          {make_shared<Wall>(),
           make_shared<Diamond>(Color::Blue, Shape::Square),
           make_shared<Diamond>(Color::Blue, Shape::Square),
           make_shared<Wall>()},
          {make_shared<Wall>(), make_shared<Wall>(), make_shared<Wall>(),
           make_shared<Wall>()},
        });
        QVERIFY(engine.isGameSolvable() == true);
        engine.set_map({
          {make_shared<Wall>(), make_shared<Wall>(), make_shared<Wall>(),
           make_shared<Wall>()},
          {make_shared<Wall>(), make_shared<Blank>(),
           make_shared<Diamond>(Color::Blue, Shape::Square),
           make_shared<Wall>()},
          {make_shared<Wall>(), make_shared<Diamond>(Color::Red, Shape::Square),
           make_shared<Diamond>(Color::Blue, Shape::Square),
           make_shared<Wall>()},
          {make_shared<Wall>(), make_shared<Wall>(), make_shared<Wall>(),
           make_shared<Wall>()},
        });
        QVERIFY(engine.isGameSolvable() == false);
    }

    void check_get_score()
    {
        engine.reset();
        engine.set_map({
          {make_shared<Wall>(), make_shared<Wall>(), make_shared<Wall>(),
           make_shared<Wall>(), make_shared<Wall>(), make_shared<Wall>()},
          {make_shared<Wall>(), make_shared<Blank>(), make_shared<Blank>(),
           make_shared<Blank>(), make_shared<Blank>(), make_shared<Wall>()},
          {make_shared<Wall>(), make_shared<Blank>(), make_shared<Diamond>(Color::Red, Shape::Square),
           make_shared<Diamond>(Color::Red, Shape::Square),make_shared<Blank>(), make_shared<Wall>()},
          {make_shared<Wall>(), make_shared<Blank>(), make_shared<Blank>(),
           make_shared<Blank>(), make_shared<Blank>(), make_shared<Wall>()},
          {make_shared<Wall>(), make_shared<Blank>(), make_shared<Blank>(),
           make_shared<Blank>(), make_shared<Blank>(), make_shared<Wall>()},
          {make_shared<Wall>(), make_shared<Wall>(), make_shared<Wall>(),
           make_shared<Wall>(), make_shared<Wall>(), make_shared<Wall>()},
        });
        engine.manipulate(Qt::Key_D);
        engine.manipulate(Qt::Key_S);
        engine.manipulate(Qt::Key_D);
        engine.manipulate(Qt::Key_S);
        QVERIFY(engine.getP1Score() == 1);
    }

public:
};

#include "game_logic.moc"
QTEST_MAIN(GameLogicTest)