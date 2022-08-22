#include "MyMainWindow.h"
#include "config.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QPainter>
#include <QKeyEvent>
MyMainWindow::MyMainWindow(QWidget *parent)
    : QMainWindow(parent)
{  
    QDesktopWidget w;
    int DeskWidth = w.width() / 2;
    map_choose = 2;
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
    if ( map_choose == 1) {
        painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/background/battleback1.png"));
    }
    else if ( map_choose == 2) {
        painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/background/battleback1.png"));
    }
    painter.drawRect(hero_one.attack_range);
    painter.drawRect(hero_one.real_body);
    painter.drawRect(k.real_body);
    if (hero_one.GetKind() == 0 && hero_one.GetDirection() == 1) {
        QImage image(":/image/Resource/image/main_character/running3/zero4_5.png");
        QImage mirroredImage = image.mirrored(true, false);
        hero_one.photo = QPixmap::fromImage(mirroredImage);
    }
    else if (hero_one.GetKind() == 0 && hero_one.GetDirection() == 0) {
        hero_one.photo = QPixmap(":/image/Resource/image/main_character/running3/zero4_5.png");
    }
    painter.drawPixmap(hero_one.GetX(), hero_one.GetY(), hero_one.image_width, hero_one.image_height, hero_one.photo);
    if (k.GetKind() == 0 && k.GetDirection() == 1) {
        QImage image(":/image/Resource/image/main_character/running3/zero4_5.png");
        QImage mirroredImage = image.mirrored(true, false);
        k.photo = QPixmap::fromImage(mirroredImage);
    }
    else if (k.GetKind() == 0 && k.GetDirection() == 0) {
        k.photo = QPixmap(":/image/Resource/image/main_character/running3/zero4_5.png");
    }
    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    painter.drawRect(50, 40, 500, 20);
    painter.drawRect(50, 75, 300, 15);
    painter.setBrush(Qt::red);
    if (hero_one.GetHP() <= 0) {
        hero_one.SetHP(0);
    }
    painter.drawRect(50, 40, 500 * (double(hero_one.GetHP()) / hero_one.GetHPMAX()), 15);
    painter.setBrush(Qt::blue);
    painter.drawRect(50, 75, 300 * (double(hero_one.GetMP()) / hero_one.GetMPMAX()), 10);
    painter.drawPixmap(k.GetX(), k.GetY(), k.image_width,k.image_height,k.photo);
    painter.setBrush(QBrush(Qt::NoBrush));
    painter.drawRect(k.real_body_x, k.real_body_x, 500 * (double(hero_one.GetHP()) / hero_one.GetHPMAX()), 15);
    painter.setBrush(Qt::blue);
    painter.drawRect(50, 75, 300 * (double(hero_one.GetMP()) / hero_one.GetMPMAX()), 10);
    painter.drawPixmap(k.GetX(), k.GetY(), k.image_width, k.image_height, k.photo);
    painter.setBrush(QBrush(Qt::NoBrush));
    painter.drawRect(k.attack_range);
}
//以下是键盘敲击事件函数，影响角色行为
void MyMainWindow::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_A://向左跑
        hero_one.SetDirection(1);//设置人物朝向
        hero_one.SetKind(1);;//设置人物状态
        break;
    case Qt::Key_D:
        hero_one.SetDirection(0);
        hero_one.SetKind(1);
        break;
    case Qt::Key_W:
        hero_one.SetKind(2);
        break;
    case Qt::Key_S:
        hero_one.SetKind(3);
        break;
    case Qt::Key_J:
        hero_one.attacknum = 1;
        hero_one.SetKind(4);
        break;
    case Qt::Key_K:
        hero_one.WalkDown();
        break;
    default:
        break;
    }
}
//以下是键盘松开事件函数，影响角色行为
void MyMainWindow::keyReleaseEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_A:
        hero_one.SetDirection(1);
        hero_one.SetKind(0);
        break;
    case Qt::Key_D:
        hero_one.SetDirection(0);
        hero_one.SetKind(0);
        break;
    case Qt::Key_W:
        hero_one.SetKind(0);
        break;
    case Qt::Key_S:
        hero_one.SetKind(0);
        break;
    default:
        break;
    }
}
void MyMainWindow::timerEvent(QTimerEvent* event) {
    int tmp = event->timerId();
    if (tmp == timeID1) {
        hero_one.SetStrong(0);
    }
    if (tmp == timeID2) {
        k.SetStrong(0);
    }
}
//以下是更新函数，主要更新角色属性，怪物属性，加载动作动画等
void MyMainWindow::UpdateOne() {
    k.Move(hero_one);
    hero_one.SetStrong(1);
    if (k.GetStrong() == 0) {
        k.BeAttacked(hero_one);
    }
    if (hero_one.GetHP() == 0) {
        hero_one.SetStrong(1);
        hero_one.SetKind(6);
    }
    if (hero_one.GetStrong() == 0) {
        hero_one.BeAttacked(k);
    }
    hero_one.real_body.moveTo(hero_one.real_body_x - hero_one.real_body_width / 2, hero_one.real_body_y - hero_one.real_body_height / 2);
    hero_one.real_body.setWidth(hero_one.real_body_width);   //攻击矩形(碰撞检测)
    hero_one.real_body.setHeight(hero_one.real_body_height);
    k.real_body.moveTo(k.real_body_x - k.real_body_width / 2, k.real_body_y - k.real_body_height / 2);
    k.real_body.setWidth(k.real_body_width);   //攻击矩形(碰撞检测)
    k.real_body.setHeight(k.real_body_height);
    if (hero_one.GetKind() == 1) {
        if(hero_one.GetDirection() == 1)hero_one.WalkLeft();
        if(hero_one.GetDirection() == 0)hero_one.WalkRight();
    }
    if (hero_one.GetKind() == 2) {
        hero_one.WalkTop();
    }
    if (hero_one.GetKind() == 3) {
        hero_one.WalkDown();
    }
    if (hero_one.GetKind() == 4) {
        if (hero_one.count_attack > 10)
        {
            hero_one.SetKind(0);
        }
        hero_one.Attack();
    }
    if (hero_one.GetKind() == 5 && hero_one.GetStrong() == 0) {
        hero_one.BeAttackedAnimation();
        if (hero_one.count_attack >= 11) {
            hero_one.SetHP(hero_one.GetHP()- 50);
            timeID1 = startTimer(1000);
            hero_one.SetStrong(1);
            hero_one.SetKind(0);
        }
    }
    if (hero_one.GetKind() == 6) {
        hero_one.Die();
    }
    if (k.GetKind() == 5 && k.GetStrong() == 0) {
        k.BeAttackedAnimation();
        if (k.count_attack >= 11) {
            k.SetHP(hero_one.GetHP() - 50);
            timeID2 = startTimer(1000);
            k.SetStrong(1);
            k.SetKind(0);
        }
    }
}