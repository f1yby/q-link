#pragma once
#include <QTest>

class GameLogicTest: public QObject{
    Q_OBJECT
private slots:
    void should_end_1();
public:
    GameLogicTest();
};
