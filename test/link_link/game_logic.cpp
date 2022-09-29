#include <QtTest>
#include "link_link/link_link.h"
class GameLogicTest: public QObject{
    Q_OBJECT
private:
private slots:
    void check_init(){    link_link::LinkLink engine;
        QVERIFY(engine.isGameSolvable());
        QVERIFY(!engine.isGameEnd());
    }
public:
};

#include "game_logic.moc"
QTEST_MAIN(GameLogicTest)