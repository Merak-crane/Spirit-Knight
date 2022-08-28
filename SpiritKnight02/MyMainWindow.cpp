#include "MyMainWindow.h"
#include "config.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QPainter>
#include "stdio.h"
#include "time.h"
#include <QKeyEvent>
MyMainWindow::MyMainWindow(int mode, QWidget *parent)
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
    ultra_monster.resize(2);
    k = new LittleMonster;
    connect(&map_time, &QTimer::timeout, [=]() {
        update();
        UpdateOne();
    });
    for (int i = 1; i < 3; i++) {
        little_monster[i] = new LittleMonster();
        little_monster_survive[i] = false;
    }
    for (int i = 1; i < 3; i++) {
        middle_monster[i] = new MiddleMonster();
        middle_monster_survive[i] = false;
    }
    for (int i = 1; i < ultra_monster.size(); i++) {
        ultra_monster[i] = new UltraMonster;
        ultra_monster_survive[i] = true;
    }
    hp = new QLabel(this);
    hp->setObjectName("HP");
    mp = new QLabel(this);
    mp->setObjectName("MP");
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
    painter.drawPixmap(0, 0, 500, 150, QPixmap(":/image/Resource/image/main_character/hp.png"));
    hp->setGeometry(155, 110, hero_one.GetHP() * 320 / hero_one.GetHPMAX(), 10);
    mp->setGeometry(155, 122, hero_one.GetMP() * 320 / hero_one.GetMPMAX(), 10);
    painter.drawPixmap(hero_one.GetX(), hero_one.GetY(), hero_one.image_width, hero_one.image_height, hero_one.photo);

    for (int i = 1; i < 3; i++) {
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
                painter.drawRect(little_monster[i]->real_body_x - 30, little_monster[i]->real_body_y + 65, 80 * (double(little_monster[i]->GetHP()) / little_monster[i]->GetHPMAX()), 15);
                painter.setBrush(Qt::blue);
                painter.drawRect(little_monster[i]->real_body_x - 30, little_monster[i]->real_body_y + 50, 80 * (double(little_monster[i]->GetMP()) / little_monster[i]->GetMPMAX()), 10);
                painter.setBrush(QBrush(Qt::NoBrush));
                painter.drawRect(little_monster[i]->attack_range);
            }
        }
    }
    for (int i = 1; i < 3; i++) {
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
                painter.drawRect(middle_monster[i]->real_body_x - 30, middle_monster[i]->real_body_y + 65, 80 * (double(middle_monster[i]->GetHP()) / middle_monster[i]->GetHPMAX()), 15);
                painter.setBrush(Qt::blue);
                painter.drawRect(middle_monster[i]->real_body_x - 30, middle_monster[i]->real_body_y + 50, 80 * (double(middle_monster[i]->GetMP()) / middle_monster[i]->GetMPMAX()), 10);
                painter.setBrush(QBrush(Qt::NoBrush));
                painter.drawRect(middle_monster[i]->attack_range);
            }
        }
    }
    for (int i = 1; i < ultra_monster.size(); i++) {
        if (ultra_monster_survive[i] == true) {
            if (ultra_monster[i]->GetKind() == 0 && ultra_monster[i]->GetDirection() == 1) {
                QImage image(":/image/Resource/image/main_character/running3/zero4_5.png");
                QImage mirroredImage = image.mirrored(true, false);
                ultra_monster[i]->photo = QPixmap::fromImage(mirroredImage);
            }
            else if (ultra_monster[i]->GetKind() == 0 && ultra_monster[i]->GetDirection() == 0) {
                ultra_monster[i]->photo = QPixmap(":/image/Resource/image/main_character/running3/zero4_5.png");
            }
            if (ultra_monster[i]->GetHP() <= 0) {
                ultra_monster[i]->SetHP(0);
                ultra_monster[i]->SetKind(6);
                qDebug() << ultra_monster[i]->GetKind();
            }
            if (ultra_monster[i]->GetKind() != 6) {
                painter.drawRect(ultra_monster[i]->real_body);
                painter.setBrush(Qt::red);
                painter.drawPixmap(ultra_monster[i]->GetX(), ultra_monster[i]->GetY(), ultra_monster[i]->image_width, ultra_monster[i]->image_height, ultra_monster[i]->photo);
                painter.drawRect(ultra_monster[i]->real_body_x, ultra_monster[i]->real_body_y + 65, 80 * (double(ultra_monster[i]->GetHP()) / ultra_monster[i]->GetHPMAX()), 15);
                painter.setBrush(Qt::blue);
                painter.drawRect(ultra_monster[i]->real_body_x, ultra_monster[i]->real_body_y + 50, 80 * (double(ultra_monster[i]->GetMP()) / ultra_monster[i]->GetMPMAX()), 10);
                painter.setBrush(QBrush(Qt::NoBrush));
                painter.drawRect(ultra_monster[i]->attack_range);
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
    for (int i = 1; i < 3; i++) {
        if (tmp == timeID2[i] && little_monster_survive[i] == true) {
            little_monster[i]->SetStrong(0);
        }
    }
    for (int i = 1; i < 3; i++) {
        if (tmp == timeID3[i] && middle_monster_survive[i] == true) {
            middle_monster[i]->SetStrong(0);
        }
    }
    for (int i = 1; i < 3; i++) {
        if (tmp == timeID4[i] && middle_monster_survive[i] == true) {
            middle_monster[i]->SetKind(0);
        }
    }
    for (int i = 1; i < ultra_monster.size(); i++) {
        if (tmp == timeID5[i] && ultra_monster_survive[i] == true) {
            ultra_monster[i]->SetStrong(0);
        }
    }
    for (int i = 1; i < ultra_monster.size(); i++) {
        if (tmp == timeID6[i] && ultra_monster_survive[i] == true) {
            ultra_monster[i]->SetKind(0);
        }
    }
    if (tmp == timeIDm1) {
        hero_one.x_speed_left = 50;
        hero_one.x_speed_right = 50;
        hero_one.y_speed = 40;
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
            hero_one.SetHP(hero_one.GetHP() - 1);
            timeID1 = startTimer(1000);
            hero_one.SetStrong(1);
            hero_one.SetKind(0);
        }
    }
    if (hero_one.GetKind() == 6) {
        hero_one.Die();
    }
    if (hero_one.GetKind() == 8) {
        hero_one.photo = QPixmap(":/image/Resource/image/main_character/die/zero1_30.png");
        hero_one.x_speed_left = 0;
        hero_one.x_speed_right = 0;
        hero_one.y_speed = 0;
        timeIDm1 = startTimer(800);
    }
    for (int i = 1; i < 3; i++) {
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
    for (int i = 1; i < 3; i++) {
        if (middle_monster_survive[i] == true) {
            middle_monster[i]->Move(hero_one);
            if (middle_monster[i]->GetStrong() == 0) {
                middle_monster[i]->BeAttacked(hero_one);
            }
            if (middle_monster[i]->GetHP() == 0) {
                middle_monster[i]->SetStrong(1);
                middle_monster[i]->SetKind(6);
                middle_monster[i]->SetLay(0);
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
                    if (middle_monster[i]->GetLay() != 1) {
                        middle_monster[i]->SetKind(0);
                    }
                }
            }
            qDebug() << middle_monster[1]->GetKind();
            if (middle_monster[i]->GetKind() == 8) {
                middle_monster[i]->AttackAnimation();
                middle_monster[i]->x_speed_left = 5;
                middle_monster[i]->x_speed_right = 5;
                if (middle_monster[i]->count_attack >= 9) {
                    middle_monster[i]->SetKind(9);
                    middle_monster[i]->photo = QPixmap(":/image/Resource/image/firemonkey/die/firemonkey_63.png");
                    timeID4[i] = startTimer(2000);
                }
            }
            if (middle_monster[i]->GetKind() == 9) {
                middle_monster[i]->SetLay(1);
            }
        }
    }
    for (int i = 1; i < ultra_monster.size(); i++) {
        if (ultra_monster_survive[i] == true) {
            ultra_monster[i]->Move(hero_one);
            if (ultra_monster[i]->GetStrong() == 0) {
                ultra_monster[i]->BeAttacked(hero_one);
            }
            if (ultra_monster[i]->GetHP() == 0) {
                ultra_monster[i]->SetStrong(1);
                ultra_monster[i]->SetKind(12);
                ultra_monster[i]->SetLay(0);
            }
            if (ultra_monster[i]->GetKind() == 6) {
                ultra_monster[i]->Die();
                ultra_monster_survive[i] = false;
                delete ultra_monster[i];
            }
            if (ultra_monster[i]->GetKind() != 4) {
                ultra_monster[i]->attack_range.setWidth(0);
                ultra_monster[i]->attack_range.setHeight(0);
            }
            if (ultra_monster[i]->GetKind() != 7) {
                ultra_monster[i]->real_body.moveTo(ultra_monster[i]->real_body_x - ultra_monster[i]->real_body_width / 2, ultra_monster[i]->real_body_y - ultra_monster[i]->real_body_height / 2);
                ultra_monster[i]->real_body.setWidth(ultra_monster[i]->real_body_width);   //攻击矩形(碰撞检测)
                ultra_monster[i]->real_body.setHeight(ultra_monster[i]->real_body_height);
            }
            else {
                ultra_monster[i]->real_body.moveTo(ultra_monster[i]->real_body_x - ultra_monster[i]->real_body_width / 2, ultra_monster[i]->real_body_y - ultra_monster[i]->real_body_height / 2);
                ultra_monster[i]->real_body.setWidth(0);   //攻击矩形(碰撞检测)
                ultra_monster[i]->real_body.setHeight(0);
                ultra_monster[i]->attack_range.setWidth(0);
                ultra_monster[i]->attack_range.setHeight(0);
            }
            if (ultra_monster[i]->GetKind() == 5 && ultra_monster[i]->GetStrong() == 0) {
                ultra_monster[i]->BeAttackedAnimation();
                if (ultra_monster[i]->count_attack >= 4) {
                    ultra_monster[i]->SetHP(ultra_monster[i]->GetHP() - 30);
                    timeID5[i] = startTimer(2000);
                    ultra_monster[i]->SetStrong(1);
                    if (ultra_monster[i]->GetLay() != 1) {
                        ultra_monster[i]->SetKind(0);
                    }
                }
            }
            if (ultra_monster[i]->GetKind() == 8) {
                ultra_monster[i]->AttackAnimation();
                hero_one.SetKind(8);
                ultra_monster[i]->x_speed_left = 15;
                ultra_monster[i]->x_speed_right = 15;
                if (ultra_monster[i]->count_attack >= 15) {
                    hero_one.SetHP(hero_one.GetHP() - 20);
                    ultra_monster[i]->SetKind(9);
                    ultra_monster[i]->photo = QPixmap(":/image/Resource/image/zark/attacked/googuy_37.png");
                    timeID6[i] = startTimer(1000);
                }
            }
            if (ultra_monster[i]->GetKind() == 9) {
                ultra_monster[i]->SetLay(1);
            }
            if (ultra_monster[i]->GetKind() == 13) {
                hero_one.SetHP(hero_one.GetHP() - 40);
                ultra_monster[i]->SetKind(6);
            }
        }
    }
}
