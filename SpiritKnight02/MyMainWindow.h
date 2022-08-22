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

private:
    Ui::MyMainWindowClass ui;
    int map_choose;
    int timeID1;
    Hero hero_one;
    LittleMonster k;
    QTimer map_time;
};
