#include "MyMainWindow.h"
#include "config.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QPainter>
#include "stdio.h"
#include "time.h"
#include <QKeyEvent>
MyMainWindow::MyMainWindow(QWidget *parent)
    : QMainWindow(parent)
{  
    srand((unsigned)time(NULL));
    QDesktopWidget w;
    int DeskWidth = w.width() / 2;
    map_choose = 2;
    int DeskHeight = w.height() / 2;//获取设备的分辨率
    this->setFixedSize(DeskWidth, DeskHeight);//设置窗口大小
    this->setWindowTitle(QString::fromUtf16(u"英灵骑士"));//设置窗口标题
    this->setWindowIcon(QIcon(":/icon/Resource/icon/htmlogo.png"));//设置窗口logo
    map_time.setInterval(GAME_RATE);
    map_time.start();
    k = new LittleMonster;
    connect(&map_time, &QTimer::timeout, [=]() {
        update();
        UpdateOne();
    });
    for (int i = 1; i < 11; i++) {
        little_monster[i] = new LittleMonster();
        little_monster_survive[i] = false;
    }
    for (int i = 1; i < 11; i++) {
        middle_monster[i] = new MiddleMonster();
        middle_monster_survive[i] = true;
    }
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
    if ( hero_one.GetKind() == 0 && hero_one.GetDirection() == 1) {
        QImage image(":/image/Resource/image/main_character/running3/zero4_5.png");
        QImage mirroredImage = image.mirrored(true, false);
        hero_one.photo = QPixmap::fromImage(mirroredImage);
    }
    else if ( hero_one.GetKind() == 0 && hero_one.GetDirection() == 0) {
        hero_one.photo = QPixmap(":/image/Resource/image/main_character/running3/zero4_5.png");
    }
    if ( hero_one.GetHP() <= 0) {
        hero_one.SetHP(0);
    }
    painter.drawPixmap(hero_one.GetX(), hero_one.GetY(), hero_one.image_width, hero_one.image_height, hero_one.photo);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    painter.drawRect(50, 40, 500, 20);
    painter.drawRect(50, 75, 300, 15);
    painter.setBrush(Qt::red);
    painter.drawRect(50, 40, 500 * (double(hero_one.GetHP()) / hero_one.GetHPMAX()), 15);
    painter.setBrush(Qt::blue);
    painter.drawRect(50, 75, 300 * (double(hero_one.GetMP()) / hero_one.GetMPMAX()), 10);
    painter.setBrush(Qt::red);
    painter.setBrush(QBrush(Qt::NoBrush));

    for (int i = 1; i < 11; i++) {
        if (little_monster_survive[i] == true) {
            if (little_monster[i]->GetKind() == 0 && little_monster[i]->GetDirection() == 1) {
                QImage image(":/image/Resource/image/main_character/running3/zero4_5.png");
                QImage mirroredImage = image.mirrored(true, false);
                little_monster[i]->photo = QPixmap::fromImage(mirroredImage);
            }
            else if (little_monster[i]->GetKind() == 0 && little_monster[i]->GetDirection() == 0) {
                little_monster[i]->photo = QPixmap(":/image/Resource/image/main_character/running3/zero4_5.png");
            }
            if (little_monster[i]->GetHP() <= 0) {
                little_monster[i]->SetHP(0);
                little_monster[i]->SetKind(6);
                qDebug() << little_monster[i]->GetKind();
            }
            if (little_monster[i]->GetKind() != 6) {
                painter.drawRect(little_monster[i]->real_body);
                painter.setBrush(Qt::red);
                painter.drawPixmap(little_monster[i]->GetX(), little_monster[i]->GetY(), little_monster[i]->image_width, little_monster[i]->image_height, little_monster[i]->photo);
                painter.drawRect(little_monster[i]->real_body_x, little_monster[i]->real_body_y + 50, 500 * (double(little_monster[i]->GetHP()) / little_monster[i]->GetHPMAX()), 15);
                painter.setBrush(Qt::blue);
                painter.drawRect(little_monster[i]->real_body_x, little_monster[i]->real_body_y, 300 * (double(little_monster[i]->GetMP()) / little_monster[i]->GetMPMAX()), 10);
                painter.setBrush(QBrush(Qt::NoBrush));
                painter.drawRect(little_monster[i]->attack_range);
            }
        }
    }
    for (int i = 1; i < 11; i++) {
        if (middle_monster_survive[i] == true) {
            if (middle_monster[i]->GetKind() == 0 && middle_monster[i]->GetDirection() == 1) {
                QImage image(":/image/Resource/image/main_character/running3/zero4_5.png");
                QImage mirroredImage = image.mirrored(true, false);
                middle_monster[i]->photo = QPixmap::fromImage(mirroredImage);
            }
            else if (middle_monster[i]->GetKind() == 0 && middle_monster[i]->GetDirection() == 0) {
                middle_monster[i]->photo = QPixmap(":/image/Resource/image/main_character/running3/zero4_5.png");
            }
            if (middle_monster[i]->GetHP() <= 0) {
                middle_monster[i]->SetHP(0);
                middle_monster[i]->SetKind(6);
                qDebug() << middle_monster[i]->GetKind();
            }
            if (middle_monster[i]->GetKind() != 6) {
                painter.drawRect(middle_monster[i]->real_body);
                painter.setBrush(Qt::red);
                painter.drawPixmap(middle_monster[i]->GetX(), middle_monster[i]->GetY(), middle_monster[i]->image_width, middle_monster[i]->image_height, middle_monster[i]->photo);
                painter.drawRect(middle_monster[i]->real_body_x, middle_monster[i]->real_body_y + 50, 500 * (double(middle_monster[i]->GetHP()) / middle_monster[i]->GetHPMAX()), 15);
                painter.setBrush(Qt::blue);
                painter.drawRect(middle_monster[i]->real_body_x, middle_monster[i]->real_body_y, 300 * (double(middle_monster[i]->GetMP()) / middle_monster[i]->GetMPMAX()), 10);
                painter.setBrush(QBrush(Qt::NoBrush));
                painter.drawRect(middle_monster[i]->attack_range);
            }
        }
    }
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
    for (int i = 1; i < 11; i++) {
        if (tmp == timeID2[i] && little_monster_survive[i] == true) {
            little_monster[i]->SetStrong(0);
        }
    }
    for (int i = 1; i < 11; i++) {
        if (tmp == timeID3[i] && middle_monster_survive[i] == true) {
            middle_monster[i]->SetStrong(0);
        }
    }
}
//以下是更新函数，主要更新角色属性，怪物属性，加载动作动画等
void MyMainWindow::UpdateOne() {
    if (hero_one.GetHP() == 0) {
        hero_one.SetStrong(1);
        hero_one.SetKind(6);
    }
    if (hero_one.GetStrong() == 0) {
        hero_one.BeAttacked(little_monster, little_monster_survive);
    }
    hero_one.real_body.moveTo(hero_one.real_body_x - hero_one.real_body_width / 2, hero_one.real_body_y - hero_one.real_body_height / 2);
    hero_one.real_body.setWidth(hero_one.real_body_width);   //攻击矩形(碰撞检测)
    hero_one.real_body.setHeight(hero_one.real_body_height);
    if (hero_one.GetKind() != 4) {
        hero_one.attack_range.setWidth(0);
        hero_one.attack_range.setHeight(0);
    }
    if (hero_one.GetKind() == 1) {
        if (hero_one.GetDirection() == 1)hero_one.WalkLeft();
        if (hero_one.GetDirection() == 0)hero_one.WalkRight();
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
            hero_one.SetHP(hero_one.GetHP()- 1);
            timeID1 = startTimer(1000);
            hero_one.SetStrong(1);
            hero_one.SetKind(0);
        }
    }
    if (hero_one.GetKind() == 6) {
        hero_one.Die();
    }
    for (int i = 1; i < 11; i++) {
        if (little_monster_survive[i] == true) {
            little_monster[i]->Move(hero_one);
            if (little_monster[i]->GetStrong() == 0) {
                little_monster[i]->BeAttacked(hero_one);
            }
            if (little_monster[i]->GetHP() == 0) {
                little_monster[i]->SetStrong(1);
                little_monster[i]->SetKind(6);
            }
            if (little_monster[i]->GetKind() == 6) {
                little_monster[i]->Die();
                little_monster_survive[i] = false;
                delete little_monster[i];
            }
            if (little_monster[i]->GetKind() != 4) {
                little_monster[i]->attack_range.setWidth(0);
                little_monster[i]->attack_range.setHeight(0);
            }
            if (little_monster[i]->GetKind() != 7) {
                little_monster[i]->real_body.moveTo(little_monster[i]->real_body_x - little_monster[i]->real_body_width / 2, little_monster[i]->real_body_y - little_monster[i]->real_body_height / 2);
                little_monster[i]->real_body.setWidth(little_monster[i]->real_body_width);   //攻击矩形(碰撞检测)
                little_monster[i]->real_body.setHeight(little_monster[i]->real_body_height);
            }
            else {
                little_monster[i]->real_body.moveTo(little_monster[i]->real_body_x - little_monster[i]->real_body_width / 2, little_monster[i]->real_body_y - little_monster[i]->real_body_height / 2);
                little_monster[i]->real_body.setWidth(0);   //攻击矩形(碰撞检测)
                little_monster[i]->real_body.setHeight(0);
                little_monster[i]->attack_range.setWidth(0);
                little_monster[i]->attack_range.setHeight(0);
            }
            if (little_monster[i]->GetKind() == 5 && little_monster[i]->GetStrong() == 0) {
                little_monster[i]->BeAttackedAnimation();
                if (little_monster[i]->count_attack >= 9) {
                    little_monster[i]->SetHP(little_monster[i]->GetHP() - 30);
                    timeID2[i] = startTimer(1000);
                    little_monster[i]->SetStrong(1);
                    little_monster[i]->SetKind(0);
                }
            }
        }
    }
    for (int i = 1; i < 11; i++) {
        if (middle_monster_survive[i] == true) {
            middle_monster[i]->Move(hero_one);
            if (middle_monster[i]->GetStrong() == 0) {
                middle_monster[i]->BeAttacked(hero_one);
            }
            if (middle_monster[i]->GetHP() == 0) {
                middle_monster[i]->SetStrong(1);
                middle_monster[i]->SetKind(6);
            }
            if (middle_monster[i]->GetKind() == 6) {
                middle_monster[i]->Die();
                middle_monster_survive[i] = false;
                delete middle_monster[i];
            }
            if (middle_monster[i]->GetKind() != 4) {
                middle_monster[i]->attack_range.setWidth(0);
                middle_monster[i]->attack_range.setHeight(0);
            }
            if (middle_monster[i]->GetKind() != 7) {
                middle_monster[i]->real_body.moveTo(middle_monster[i]->real_body_x - middle_monster[i]->real_body_width / 2, middle_monster[i]->real_body_y - middle_monster[i]->real_body_height / 2);
                middle_monster[i]->real_body.setWidth(middle_monster[i]->real_body_width);   //攻击矩形(碰撞检测)
                middle_monster[i]->real_body.setHeight(middle_monster[i]->real_body_height);
            }
            else {
                middle_monster[i]->real_body.moveTo(middle_monster[i]->real_body_x - middle_monster[i]->real_body_width / 2, middle_monster[i]->real_body_y - middle_monster[i]->real_body_height / 2);
                middle_monster[i]->real_body.setWidth(0);   //攻击矩形(碰撞检测)
                middle_monster[i]->real_body.setHeight(0);
                middle_monster[i]->attack_range.setWidth(0);
                middle_monster[i]->attack_range.setHeight(0);
            }
            if (middle_monster[i]->GetKind() == 5 && middle_monster[i]->GetStrong() == 0) {
                middle_monster[i]->BeAttackedAnimation();
                if (middle_monster[i]->count_attack >= 4) {
                    middle_monster[i]->SetHP(middle_monster[i]->GetHP() - 30);
                    timeID3[i] = startTimer(1000);
                    middle_monster[i]->SetStrong(1);
                    middle_monster[i]->SetKind(0);
                }
            }
        }
    }
}
