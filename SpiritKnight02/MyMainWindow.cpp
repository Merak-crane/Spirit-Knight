#include "MyMainWindow.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QPainter>
MyMainWindow::MyMainWindow(QWidget *parent)
    : QMainWindow(parent)
{  
    QDesktopWidget w;
    int DeskWidth = w.width() / 2;
    int DeskHeight = w.height() / 2;//获取设备的分辨率
    this->setFixedSize(DeskWidth, DeskHeight);//设置窗口大小
    this->setWindowTitle(QString::fromUtf16(u"英灵骑士"));//设置窗口标题
    this->setWindowIcon(QIcon(":/icon/Resource/icon/htmlogo.png"));//设置窗口logo
}

MyMainWindow::~MyMainWindow()
{
}

void MyMainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    map_choose = 0;
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/battleback1.png"));
    if ( map_choose == 1) {
        painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/battleback1.png"));
    }
    if ( map_choose == 2) {
        painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/battleback2.png"));
    }
    painter.drawPixmap(hero_one.GetX(), hero_one.GetY(), QPixmap(hero_one.GetStand()));
}

