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

private:
    Ui::MyMainWindowClass ui;
    int map_choose;
    Hero hero_one;
    LittleMonster k;
    QTimer map_time;
};
