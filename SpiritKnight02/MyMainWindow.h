#pragma once
#pragma execution_character_set("utf-8")  
#include <QtWidgets/QMainWindow>
#include "ui_MyMainWindow.h"
#include "Character.h"
#include "Player.h"
#include <QTimer>
#include <QLabel>
#include <QPushButton>

#include <QSound>
class MyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QLabel* hp;
    QLabel* mp;
    QLabel* died;
    QLabel* user_information_label;
    Player* local;
    MyMainWindow(QWidget *parent = nullptr);
    MyMainWindow(int mode, Player* local, int mapchoose = 0, QWidget* parent = nullptr);
    ~MyMainWindow();
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void UpdateOne(int mode);
    void timerEvent(QTimerEvent* event);
    void UpdateM(MiddleMonster* []);
   /* QSound* froestBGM, * battle1;
    QSound* h_satt;*/
private:
    Ui::MyMainWindowClass ui;
    int map_choose;
    int close_num;
    int timeID1;
    int timeIDm1;
    QPushButton* set_up_btn;
    vector<int> sorcerer_one_time;
    vector<SorcererOne*> sorcerer_one;
    vector<bool> sorcerer_one_survive;
    vector<int> little_monster_time;
    vector<LittleMonster*> little_monster;
    vector<bool> little_monster_survive;
    vector<int> little_monster2_time;
    vector<LittleMonster*> little_monster2;
    vector<bool> little_monster2_survive;
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
