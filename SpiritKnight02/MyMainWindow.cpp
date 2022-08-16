#include "MyMainWindow.h"
#include <QDesktopWidget>
#include <QDebug>
MyMainWindow::MyMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QDesktopWidget w;
    int DeskWidth = w.width()/2;
    int DeskHeight = w.height()/2;
    this->setFixedSize(DeskWidth, DeskHeight);//设置窗口大小
    this->setWindowTitle("英灵骑士");//设置窗口标题
    this->setWindowIcon(QIcon(":/icon/Resource/icon/htmlogo.png"));//
}

MyMainWindow::~MyMainWindow()
{}
