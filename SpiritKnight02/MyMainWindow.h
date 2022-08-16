#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MyMainWindow.h"

class MyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MyMainWindow(QWidget *parent = nullptr);
    ~MyMainWindow();
    void InitScene();

private:
    Ui::MyMainWindowClass ui;
};
