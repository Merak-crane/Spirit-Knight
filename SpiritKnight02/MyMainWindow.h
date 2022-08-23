#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MyMainWindow.h"
#include "Character.h"
#include <QTimer>

class MyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MyMainWindow(QWidget *parent = nullptr);
    ~MyMainWindow();
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void UpdateOne();
    void timerEvent(QTimerEvent* event);
    void UpdateM(MiddleMonster* []);

private:
    Ui::MyMainWindowClass ui;
    int map_choose;
    int timeID1;
    int timeID2[11];
    int timeID3[11];
    LittleMonster* little_monster[11];
    MiddleMonster* middle_monster[11];
    bool little_monster_survive[11];
    bool middle_monster_survive[11];
    Hero hero_one;
    LittleMonster* k;
    QTimer map_time;
};
