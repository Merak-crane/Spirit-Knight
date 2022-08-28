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
    void UpdateOne(int mode);
    void timerEvent(QTimerEvent* event);
    void UpdateM(MiddleMonster* []);

private:
    Ui::MyMainWindowClass ui;
    int map_choose;
    int close_num;
    int timeID1;
    int timeID3[3];
    int timeID4[3];
    int timeID5[2];
    int timeID6[2];
    int timeIDm1;
    vector<int> little_monster_time;
    vector<LittleMonster*> little_monster;
    vector<bool> little_monster_survive;
    vector<int> middle_monster_time_one;
    vector<int> middle_monster_time_two;
    vector<MiddleMonster*> middle_monster;
    vector<bool> middle_monster_survive;
    vector<UltraMonster*> ultra_monster;
    vector<bool> ultra_monster_survive;
    vector<int> ultra_monster_time_one;
    vector<int> ultra_monster_time_two;
    Hero hero_one;
    LittleMonster* k;
    QTimer map_time;
};
