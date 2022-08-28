#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MyMainWindow.h"
#include "Character.h"
#include <QTimer>
#include <QLabel>

class MyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QLabel* hp;
    QLabel* mp;
    MyMainWindow(QWidget *parent = nullptr);
    MyMainWindow(int mode, QWidget *parent = nullptr);
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
    int timeID2[3];
    int timeID3[3];
    int timeID4[3];
    int timeID5[2];
    int timeID6[2];
    int timeIDm1;
    LittleMonster* little_monster[3];
    MiddleMonster* middle_monster[3];
    vector<UltraMonster*> ultra_monster;
    bool little_monster_survive[3];
    bool middle_monster_survive[3];
    bool ultra_monster_survive[2];
    Hero hero_one;
    LittleMonster* k;
    QTimer map_time;
};
