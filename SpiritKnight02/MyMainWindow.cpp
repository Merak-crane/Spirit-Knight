#include "MyMainWindow.h"
#include "config.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QPainter>
#include <QKeyEvent>

MyMainWindow::MyMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);    
    QDesktopWidget w;
    int DeskWidth = w.width() / 2;
    int DeskHeight = w.height() / 2;//获取设备的分辨率
    this->setFixedSize(DeskWidth, DeskHeight);//设置窗口大小
    this->setWindowTitle(QString::fromUtf16(u"英灵骑士"));//设置窗口标题
    this->setWindowIcon(QIcon(":/icon/Resource/icon/htmlogo.png"));//设置窗口logo
    map_time.setInterval(GAME_RATE);
    map_time.start();
    connect(&map_time, &QTimer::timeout, [=]() {
        update();
        UpdateOne();
    });
}

MyMainWindow::~MyMainWindow()
{
}

void MyMainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    map_choose = 2;
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/battleback1.png"));
    if ( map_choose == 1) {
        painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/battleback1.png"));
    }
    else if ( map_choose == 2) {
        painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/battleback2.png"));
    }
    if (hero_one.kind == 0 &&hero_one.GetDirection() == 1) {
        painter.drawPixmap(hero_one.GetX(), hero_one.GetY(), QPixmap(":/image/Resource/image/stand01left.png"));
    }
    if (hero_one.kind == 0 && hero_one.GetDirection() == 0) {
        painter.drawPixmap(hero_one.GetX(), hero_one.GetY(), QPixmap(":/image/Resource/image/stand01.png"));
    }
    if (hero_one.kind == 1 && hero_one.GetDirection() == 0) {
        painter.drawPixmap(hero_one.GetX(), hero_one.GetY(), hero_one.photo);
    }
    if (hero_one.kind == 1 && hero_one.GetDirection() == 1) {
        painter.drawPixmap(hero_one.GetX(), hero_one.GetY(), hero_one.photo);
    }
    if (hero_one.kind == 2) {
        painter.drawPixmap(hero_one.GetX(), hero_one.GetY(), hero_one.photo);
    }
}

void MyMainWindow::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_A:
        hero_one.SetDirection(1);
        hero_one.kind = 1;
        hero_one.x_speed_right = 5;
        break;
    case Qt::Key_D:
        hero_one.SetDirection(0);
        hero_one.kind = 1;
        hero_one.x_speed_left = 5;
        break;
    case Qt::Key_W:
        hero_one.WalkTop();
        break;
    case Qt::Key_S:
        hero_one.WalkDown();
        break;
    case Qt::Key_J:
        hero_one.attack = 1;
        hero_one.kind = 2;
        break;
    case Qt::Key_K:
        hero_one.WalkDown();
        break;
    default:
        break;
    }
}

void MyMainWindow::keyReleaseEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_A:
        hero_one.SetDirection(1);
        hero_one.kind = 0;
        break;
    case Qt::Key_D:
        hero_one.SetDirection(0);
        hero_one.kind = 0;
        break;
    case Qt::Key_W:
        hero_one.WalkTop();
        break;
    case Qt::Key_S:
        hero_one.WalkDown();
        break;
    default:
        break;
    }
}

void MyMainWindow::UpdateOne() {
    if (hero_one.kind == 1) {
        if(hero_one.GetDirection() == 1)hero_one.WalkLeft();
        if(hero_one.GetDirection() == 0)hero_one.WalkRight();
    }
    if (hero_one.kind == 2) {
        if (hero_one.count_attack > 10)
        {
            hero_one.kind = 0;
        }
        hero_one.Attack();
    }
}