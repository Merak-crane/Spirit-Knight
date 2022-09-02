#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_MyMainWindow.h"
#include "Character.h"
#include "Player.h"
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QSound>
class MyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QLabel* hp;
    QLabel* mp;
    QLabel* exp;
    QLabel* died;
    QLabel* user_information_label;
    Player* local;
    MyMainWindow(QWidget *parent = nullptr);
    MyMainWindow(int mode, Player* local, int mapchoose = 0, QWidget* parent = nullptr);
    ~MyMainWindow();
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void UpdateOne();
    void timerEvent(QTimerEvent* event);
    void UpdateM(MiddleMonster* []);
   /* QSound* froestBGM, * battle1;
    QSound* h_satt;*/
private:
    Ui::MyMainWindowClass ui;
    int map_choose;
    int mode;
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
    QMediaPlayer* player2 = new QMediaPlayer(this);
    QMediaPlaylist* playlist = new QMediaPlaylist(this);
    QMediaPlayer* player = new QMediaPlayer(this);
    Hero hero_one;
    LittleMonster* k;
    QTimer map_time;
};
