#include "MyMainWindow.h"
#include "config.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QPainter>
#include "stdio.h"
#include "start.h"
#include "SetUp.h"
#include "time.h"
#include <QKeyEvent>
#include <QMessageBox>
MyMainWindow::MyMainWindow(int mode, Player* local, int mapchoose, QWidget *parent)
    : QMainWindow(parent)
{  
    hero_one.SetLevel(local->GetLevel());
    hero_one.StatusUpdate();
    this->local = local;
    if (mapchoose != 0) {
        this->map_choose = mapchoose;
        hero_one.SetHP(local->GetHP());
        hero_one.SetMP(local->GetMP());
        hero_one.SetLevel(local->GetLevel());
        hero_one.SetExp(local->GetEXP());
    }
    close_num = 3;
    srand((unsigned)time(NULL));
    QDesktopWidget w;
    int DeskWidth = w.width() / 2;
    int DeskHeight = w.height() / 2;//获取设备的分辨率
    this->setFixedSize(DeskWidth, DeskHeight);//设置窗口大小
    this->setWindowTitle(QString::fromUtf16(u"英灵骑士"));//设置窗口标题
    this->setWindowIcon(QIcon(":/icon/Resource/icon/htmlogo.png"));//设置窗口logo
    map_time.setInterval(GAME_RATE);
    map_time.start();
   /* QMediaPlayer* player = new QMediaPlayer;*/
    connect(&map_time, &QTimer::timeout, [=]() {
        update();
        if (close_num != 2) {
            UpdateOne(mode);
        }
        else {
            //this->close();
        }
    });
    if (mode == 1 && mapchoose == 0) {
        map_choose = 1;
        /*battle1 = new QSound(":/new/prefix1/Resource/sound/BGMmap.wav", this);
        battle1->play();
        battle1->setLoops(-1);*/
    }
    else if(mode == 2 && mapchoose == 0)
    {
        map_choose = -1;
    }
    if (mode == 3 && mapchoose == 0) {
        map_choose = 1;
        int sorcerer_one_num = 3;
        sorcerer_one.resize(sorcerer_one_num);
        sorcerer_one_survive.resize(sorcerer_one_num);
        sorcerer_one_time.resize(sorcerer_one_num);
        for (int i = 1; i < sorcerer_one.size(); i++) {
        sorcerer_one[i] = new SorcererOne();
        sorcerer_one_survive[i] = true;
        }
    }
    int little_monster_num = 3;
    little_monster.resize(little_monster_num);
    little_monster_survive.resize(little_monster_num);
    little_monster_time.resize(little_monster_num);
    for (int i = 1; i < little_monster.size(); i++) {
        little_monster[i] = new LittleMonster(0);
        little_monster_survive[i] = false;
    }
    int little_monster2_num = 3;
    little_monster2.resize(little_monster_num);
    little_monster2_survive.resize(little_monster_num);
    little_monster2_time.resize(little_monster_num);
    for (int i = 1; i < little_monster2.size(); i++) {
        little_monster2[i] = new LittleMonster(1);
        little_monster2_survive[i] = true;
    }
    int middle_monster_num = 2;
    middle_monster.resize(middle_monster_num);
    middle_monster_survive.resize(middle_monster_num);
    middle_monster_time_one.resize(middle_monster_num);
    middle_monster_time_two.resize(middle_monster_num);
    for (int i = 1; i < middle_monster.size(); i++) {
        middle_monster[i] = new MiddleMonster();
        middle_monster_survive[i] = false;
    }
    int ultra_monster_num = 2;
    ultra_monster.resize(ultra_monster_num);
    ultra_monster_survive.resize(ultra_monster_num);
    ultra_monster_time_one.resize(ultra_monster_num);
    ultra_monster_time_two.resize(ultra_monster_num);
    for (int i = 1; i < ultra_monster.size(); i++) {
        ultra_monster[i] = new UltraMonster();
        ultra_monster_survive[i] = false;
    }
    died = new QLabel(this);
    died->setObjectName("died");
    hp = new QLabel(this);
    hp->setObjectName("HP");
    mp = new QLabel(this);
    mp->setObjectName("MP");
    exp = new QLabel(this);
    exp->setObjectName("EXP");
    user_information_label = new QLabel(this);
    user_information_label->setObjectName("user_information_label");
    set_up_btn = new QPushButton(this);
    set_up_btn->resize(240, 80);
    set_up_btn->move(1000, 50);
    QPixmap p1 = QPixmap(":/ui/Resource/image/ui/setup.png");
    set_up_btn->setIcon(p1);
    set_up_btn->setIconSize(QSize(240, 80));
    set_up_btn->setFlat(true);
    connect(set_up_btn, &QPushButton::clicked, [=]() {
        SetUp* set = new SetUp(hero_one, local, mode, map_choose, this);
        set->show();
        });
}

MyMainWindow::~MyMainWindow()
{
}

void MyMainWindow::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);
    if ( map_choose == 1) {
        painter->drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/background/battleback1.png"));
    }
    else if (map_choose < 0) {
        painter->drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/background/battleback4.png"));
    }
    else if ( map_choose == 2) {
        painter->drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/background/battleback2.png"));
    }
    else if (map_choose == 3) {
        painter->drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/background/battleback3.png"));
    }
    painter->drawRect(hero_one.attack_range);
    painter->drawRect(hero_one.real_body);
    if ( hero_one.GetKind() == 0 && hero_one.GetDirection() == 1) {
        QImage image(":/image/Resource/image/main_character/running3/zero4_5.png");
        QImage mirroredImage = image.mirrored(true, false);
        hero_one.photo = QPixmap::fromImage(mirroredImage);
    }
    else if ( hero_one.GetKind() == 0 && hero_one.GetDirection() == 0) {
        hero_one.photo = QPixmap(":/image/Resource/image/main_character/running3/zero4_5.png");
    }
    painter->drawPixmap(hero_one.GetX(), hero_one.GetY(), hero_one.image_width, hero_one.image_height, hero_one.photo);
    painter->drawPixmap(0, 0, 500, 150, QPixmap(":/image/Resource/image/main_character/hp.png"));
    hp->setGeometry(155, 110, hero_one.GetHP() * 320 / hero_one.GetHPMAX(), 10);
    mp->setGeometry(155, 122, hero_one.GetMP() * 320 / hero_one.GetMPMAX(), 10);
    exp->setGeometry(155, 134, hero_one.GetExp() * 320 / hero_one.GetExpmax(), 10);
    user_information_label->setGeometry(175, 45, 200, 80);
    QString information = QString("%1 Lv. %2").arg(local->GetUsername()).arg(hero_one.GetLevel());
    user_information_label->setText(information);
    painter->drawPixmap(hero_one.GetX(), hero_one.GetY(), hero_one.image_width, hero_one.image_height, hero_one.photo);

    for (int i = 1; i < little_monster.size(); i++) {
        if (little_monster_survive[i] == true) {
            if (little_monster[i]->GetKind() == 0 && little_monster[i]->GetDirection() == 1) {
                QImage image(":/image/Resource/image/little_monter/attack1/panther_47.png");
                QImage mirroredImage = image.mirrored(true, false);
                little_monster[i]->photo = QPixmap::fromImage(mirroredImage);
            }
            else if (little_monster[i]->GetKind() == 0 && little_monster[i]->GetDirection() == 0) {
                little_monster[i]->photo = QPixmap(":/image/Resource/image/little_monter/attack1/panther_47.png");
            }
            if (little_monster[i]->GetHP() <= 0) {
                little_monster[i]->SetHP(0);
                little_monster[i]->SetKind(6);
            }
            if (little_monster[i]->GetKind() != 6) {
                painter->drawRect(little_monster[i]->real_body);
                painter->setBrush(Qt::red);
                painter->drawPixmap(little_monster[i]->GetX(), little_monster[i]->GetY(), little_monster[i]->image_width, little_monster[i]->image_height, little_monster[i]->photo);
                painter->drawRect(little_monster[i]->real_body_x - 30, little_monster[i]->real_body_y + 65, 80 * (double(little_monster[i]->GetHP()) / little_monster[i]->GetHPMAX()), 15);
                painter->setBrush(Qt::blue);
                painter->drawRect(little_monster[i]->real_body_x - 30, little_monster[i]->real_body_y + 50, 80 * (double(little_monster[i]->GetMP()) / little_monster[i]->GetMPMAX()), 10);
                painter->setBrush(QBrush(Qt::NoBrush));
                painter->drawRect(little_monster[i]->attack_range);
            }
        }
    }
    for (int i = 1; i < little_monster2.size(); i++) {
        if (little_monster2_survive[i] == true) {
            if (little_monster2[i]->GetKind() == 0 && little_monster2[i]->GetDirection() == 1) {
                QImage image(":/image/Resource/image/snake_L/stand/hewligg_0.png");
                QImage mirroredImage = image.mirrored(true, false);
                little_monster2[i]->photo = QPixmap::fromImage(mirroredImage);
            }
            else if (little_monster2[i]->GetKind() == 0 && little_monster2[i]->GetDirection() == 0) {
                little_monster2[i]->photo = QPixmap(":/image/Resource/image/snake_L/stand/hewligg_0.png");
            }
            if (little_monster2[i]->GetHP() <= 0) {
                little_monster2[i]->SetHP(0);
                little_monster2[i]->SetKind(6);
            }
            if (little_monster2[i]->GetKind() != 6) {
                painter->drawRect(little_monster2[i]->real_body);
                painter->setBrush(Qt::red);
                painter->drawPixmap(little_monster2[i]->GetX(), little_monster2[i]->GetY(), little_monster2[i]->image_width, little_monster2[i]->image_height, little_monster2[i]->photo);
                painter->drawRect(little_monster2[i]->real_body_x - 30, little_monster2[i]->real_body_y + 65, 80 * (double(little_monster2[i]->GetHP()) / little_monster2[i]->GetHPMAX()), 15);
                painter->setBrush(Qt::blue);
                painter->drawRect(little_monster2[i]->real_body_x - 30, little_monster2[i]->real_body_y + 50, 80 * (double(little_monster2[i]->GetMP()) / little_monster2[i]->GetMPMAX()), 10);
                painter->setBrush(QBrush(Qt::NoBrush));
                painter->drawRect(little_monster2[i]->attack_range);
            }
        }
    }
    for (int i = 1; i < sorcerer_one.size(); i++) {
        for (int m = 1; m < sorcerer_one[i]->bullet_collector.size(); m++) {
            if (sorcerer_one_survive[i] == true) {
                if (sorcerer_one[i]->GetDirection() == 0) {
                    QImage image(":/image/Resource/image/bomber/bullet/foxtar_90.png");
                    QImage mirroredImage = image.mirrored(true, false);
                    sorcerer_one[i]->bullet_collector[m]->photo = QPixmap::fromImage(mirroredImage);
                }
                else if (sorcerer_one[i]->GetDirection() == 1) {
                    sorcerer_one[i]->bullet_collector[m]->photo = QPixmap(":/image/Resource/image/bomber/bullet/foxtar_90.png");
                }
            }
            //painter->drawRect(sorcerer_one[i]->bullet_collector[m]);
            /*painter->setBrush(Qt::red);*/
            painter->drawPixmap(sorcerer_one[i]->bullet_collector[m]->GetX(), sorcerer_one[i]->bullet_collector[m]->GetY(), sorcerer_one[i]->bullet_collector[m]->image_width, sorcerer_one[i]->bullet_collector[m]->image_height, sorcerer_one[i]->bullet_collector[m]->photo);
            painter->drawRect(sorcerer_one[i]->bullet_collector[m]->attack_range);
            /*painter->drawRect(little_monster[i]->real_body_x - 30, little_monster[i]->real_body_y + 65, 80 * (double(little_monster[i]->GetHP()) / little_monster[i]->GetHPMAX()), 15);
            painter->setBrush(Qt::blue);
            painter->drawRect(little_monster[i]->real_body_x - 30, little_monster[i]->real_body_y + 50, 80 * (double(little_monster[i]->GetMP()) / little_monster[i]->GetMPMAX()), 10);
            painter->setBrush(QBrush(Qt::NoBrush));
            painter->drawRect(little_monster[i]->attack_range);*/

        }
    }
    for (int i = 1; i < sorcerer_one.size(); i++) {
        if (sorcerer_one_survive[i] == true) {
            if (sorcerer_one[i]->GetKind() == 0 && sorcerer_one[i]->GetDirection() == 1) {
                QImage image(":/image/Resource/image/bomber/stand/bomber_14.png");
                QImage mirroredImage = image.mirrored(true, false);
                sorcerer_one[i]->photo = QPixmap::fromImage(mirroredImage);
            }
            else if (sorcerer_one[i]->GetKind() == 0 && sorcerer_one[i]->GetDirection() == 0) {
                sorcerer_one[i]->photo = QPixmap(":/image/Resource/image/bomber/stand/bomber_14.png");
            }
            if (sorcerer_one[i]->GetHP() <= 0) {
                sorcerer_one[i]->SetHP(0);
                sorcerer_one[i]->SetKind(6);
            }
            if (sorcerer_one[i]->GetKind() != 6) {
                painter->drawRect(sorcerer_one[i]->real_body);
                painter->setBrush(Qt::red);
                painter->drawPixmap(sorcerer_one[i]->GetX(), sorcerer_one[i]->GetY(), sorcerer_one[i]->image_width, sorcerer_one[i]->image_height, sorcerer_one[i]->photo);
                painter->drawRect(sorcerer_one[i]->real_body_x - 30, sorcerer_one[i]->real_body_y + 65, 80 * (double(sorcerer_one[i]->GetHP()) / sorcerer_one[i]->GetHPMAX()), 15);
                painter->setBrush(Qt::blue);
                painter->drawRect(sorcerer_one[i]->real_body_x - 30, sorcerer_one[i]->real_body_y + 50, 80 * (double(sorcerer_one[i]->GetMP()) / sorcerer_one[i]->GetMPMAX()), 10);
                painter->setBrush(QBrush(Qt::NoBrush));
                painter->drawRect(sorcerer_one[i]->attack_range);
            }
        }
    }
    for (int i = 1; i < middle_monster.size(); i++) {
        if (middle_monster_survive[i] == true) {
            if (middle_monster[i]->GetKind() == 0 && middle_monster[i]->GetDirection() == 1) {
                QImage image(":/image/Resource/image/firemonkey/dash/firemonkey_0.png");
                QImage mirroredImage = image.mirrored(true, false);
                middle_monster[i]->photo = QPixmap::fromImage(mirroredImage);
            }
            else if (middle_monster[i]->GetKind() == 0 && middle_monster[i]->GetDirection() == 0) {
                middle_monster[i]->photo = QPixmap(":/image/Resource/image/firemonkey/dash/firemonkey_0.png");
            }
            if (middle_monster[i]->GetHP() <= 0) {
                middle_monster[i]->SetHP(0);
                middle_monster[i]->SetKind(6);
                qDebug() << middle_monster[i]->GetKind();
            }
            if (middle_monster[i]->GetKind() != 6) {
                painter->drawRect(middle_monster[i]->real_body);
                painter->setBrush(Qt::red);
                painter->drawPixmap(middle_monster[i]->GetX(), middle_monster[i]->GetY(), middle_monster[i]->image_width, middle_monster[i]->image_height, middle_monster[i]->photo);
                painter->drawRect(middle_monster[i]->real_body_x - 30, middle_monster[i]->real_body_y + 65, 80 * (double(middle_monster[i]->GetHP()) / middle_monster[i]->GetHPMAX()), 15);
                painter->setBrush(Qt::blue);
                painter->drawRect(middle_monster[i]->real_body_x - 30, middle_monster[i]->real_body_y + 50, 80 * (double(middle_monster[i]->GetMP()) / middle_monster[i]->GetMPMAX()), 10);
                painter->setBrush(QBrush(Qt::NoBrush));
                painter->drawRect(middle_monster[i]->attack_range);
            }
        }
    }
    for (int i = 1; i < ultra_monster.size(); i++) {
        if (ultra_monster_survive[i] == true) {
            if (ultra_monster[i]->GetKind() == 0 && ultra_monster[i]->GetDirection() == 1) {
                QImage image(":/image/Resource/image/zark/move/googuy_18.png");
                QImage mirroredImage = image.mirrored(true, false);
                ultra_monster[i]->photo = QPixmap::fromImage(mirroredImage);
            }
            else if (ultra_monster[i]->GetKind() == 0 && ultra_monster[i]->GetDirection() == 0) {
                ultra_monster[i]->photo = QPixmap(":/image/Resource/image/zark/move/googuy_18.png");
            }
            if (ultra_monster[i]->GetHP() <= 0) {
                ultra_monster[i]->SetHP(0);
              /*  ultra_monster[i]->SetKind(6);*/
                qDebug() << ultra_monster[i]->GetKind();
            }
            if (ultra_monster[i]->GetKind() != 6) {
                painter->drawRect(ultra_monster[i]->real_body);
                painter->setBrush(Qt::red);
                painter->drawPixmap(ultra_monster[i]->GetX(), ultra_monster[i]->GetY(), ultra_monster[i]->image_width, ultra_monster[i]->image_height, ultra_monster[i]->photo);
                painter->drawRect(ultra_monster[i]->real_body_x, ultra_monster[i]->real_body_y + 65, 240 * (double(ultra_monster[i]->GetHP()) / ultra_monster[i]->GetHPMAX()), 15);
                painter->setBrush(Qt::blue);
                painter->drawRect(ultra_monster[i]->real_body_x, ultra_monster[i]->real_body_y + 50, 80 * (double(ultra_monster[i]->GetMP()) / ultra_monster[i]->GetMPMAX()), 10);
                painter->setBrush(QBrush(Qt::NoBrush));
                painter->drawRect(ultra_monster[i]->attack_range);
            }
        }
    }
    if (hero_one.GetHP() <= 0) {
        hero_one.SetHP(0);
        painter->drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/background/you_died.png"));
        died->setGeometry(450, 650, 400, 50);
        died->setText("点击Esc返回选择界面");
    }
    delete painter;
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
    case Qt::Key_Escape:
        if (hero_one.GetHP() == 0) {
            this->close();
        }
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
    //if (tmp == timeID1) {
    //    close_num = 2;
    //    qDebug() << "o";
    //}
    if (tmp == timeID1) {
        hero_one.SetStrong(0);
    }
    for (int i = 1; i < sorcerer_one_survive.size(); i++) {
        if (tmp == sorcerer_one_time[i] && sorcerer_one_survive[i] == true) {
            sorcerer_one[i]->SetStrong(0);
        }
    }
    for (int i = 1; i < little_monster_survive.size(); i++) {
        if (tmp == little_monster_time[i] && little_monster_survive[i] == true) {
            little_monster[i]->SetStrong(0);
        }
    }
    for (int i = 1; i < little_monster2_survive.size(); i++) {
        if (tmp == little_monster2_time[i] && little_monster2_survive[i] == true) {
            little_monster2[i]->SetStrong(0);
        }
    }
    for (int i = 1; i < middle_monster_survive.size(); i++) {
        if (tmp == middle_monster_time_one[i] && middle_monster_survive[i] == true) {
            middle_monster[i]->SetStrong(0);
        }
    }
    for (int i = 1; i < middle_monster_survive.size(); i++) {
        if (tmp == middle_monster_time_two[i] && middle_monster_survive[i] == true) {
            middle_monster[i]->SetKind(0);
        }
    }
    for (int i = 1; i < ultra_monster.size(); i++) {
        if (tmp == ultra_monster_time_one[i] && ultra_monster_survive[i] == true) {
            ultra_monster[i]->SetStrong(0);
        }
    }
    for (int i = 1; i < ultra_monster.size(); i++) {
        if (tmp == ultra_monster_time_two[i] && ultra_monster_survive[i] == true && ultra_monster[i]->life == 2) {
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
void MyMainWindow::UpdateOne(int mode) {
    if (hero_one.GetHP() == 0 ) {
        hero_one.SetStrong(1);
        hero_one.SetKind(6);
    }
    if (hero_one.GetExp() >= hero_one.GetExpmax()) {
        hero_one.SetLevel(hero_one.GetLevel() + 1);
        hero_one.SetExp(hero_one.GetExp() - 1000);
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
        if (hero_one.count_attack > 11) {
            hero_one.SetStrong(1);
            timeID1 = startTimer(2000);
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
    for (int i = 1; i < little_monster.size(); i++) {
        if (little_monster_survive[i] == true) {
            little_monster[i]->Move(hero_one);
            if (hero_one.GetStrong() == 0) {
                if (little_monster[i]->attack_range.intersects(hero_one.real_body)) {
                    hero_one.SetHP(hero_one.GetHP() - 1);
                    hero_one.SetKind(5);
                }
            }
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
                hero_one.SetExp(hero_one.GetExp() + 10);
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
                    little_monster[i]->SetHP(little_monster[i]->GetHP() - 100);
                    little_monster_time[i] = startTimer(1000);
                    little_monster[i]->SetStrong(1);
                    little_monster[i]->SetKind(0);
                }
            }
        }
    }
    for (int i = 1; i < little_monster2.size(); i++) {
        if (little_monster2_survive[i] == true) {
            if (hero_one.GetStrong()==0) {
                if (little_monster2[i]->attack_range.intersects(hero_one.real_body)) {
                    hero_one.SetHP(hero_one.GetHP() - 0.5);
                    hero_one.SetKind(5);
                }
            }
            little_monster2[i]->Move(hero_one);
            if (little_monster2[i]->GetStrong() == 0) {
                little_monster2[i]->BeAttacked(hero_one);
            }
            if (little_monster2[i]->GetHP() == 0) {
                little_monster2[i]->SetStrong(1);
                little_monster2[i]->SetKind(6);
            }
            if (little_monster2[i]->GetKind() == 6) {
                little_monster2[i]->Die();
                little_monster2_survive[i] = false;
                hero_one.SetExp(hero_one.GetExp() + 500);
                delete little_monster2[i];
            }
            if (little_monster2[i]->GetKind() != 4) {
                little_monster2[i]->attack_range.setWidth(0);
                little_monster2[i]->attack_range.setHeight(0);
            }
            if (little_monster2[i]->GetKind() != 7) {
                little_monster2[i]->real_body.moveTo(little_monster2[i]->real_body_x - little_monster2[i]->real_body_width / 2, little_monster2[i]->real_body_y - little_monster2[i]->real_body_height / 2);
                little_monster2[i]->real_body.setWidth(little_monster2[i]->real_body_width);   //攻击矩形(碰撞检测)
                little_monster2[i]->real_body.setHeight(little_monster2[i]->real_body_height);
            }
            else {
                little_monster2[i]->real_body.moveTo(little_monster2[i]->real_body_x - little_monster2[i]->real_body_width / 2, little_monster2[i]->real_body_y - little_monster2[i]->real_body_height / 2);
                little_monster2[i]->real_body.setWidth(0);   //攻击矩形(碰撞检测)
                little_monster2[i]->real_body.setHeight(0);
                little_monster2[i]->attack_range.setWidth(0);
                little_monster2[i]->attack_range.setHeight(0);
            }
            if (little_monster2[i]->GetKind() == 5 && little_monster2[i]->GetStrong() == 0) {
                little_monster2[i]->BeAttackedAnimation();
                if (little_monster2[i]->count_attack >= 2) {
                    little_monster2[i]->SetHP(little_monster2[i]->GetHP() - 100);
                    little_monster2_time[i] = startTimer(1000);
                    little_monster2[i]->SetStrong(1);
                    little_monster2[i]->SetKind(0);
                }
            }
        }
    }
    for (int i = 1; i < middle_monster_survive.size(); i++) {
        if (middle_monster_survive[i] == true) {
            if (hero_one.GetStrong() == 0) {
                if (middle_monster[i]->attack_range.intersects(hero_one.real_body)) {
                    hero_one.SetHP(hero_one.GetHP() - 3);
                    hero_one.SetKind(5);
                }
            }
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
                hero_one.SetExp(hero_one.GetExp() + 20);
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
                    middle_monster[i]->SetHP(middle_monster[i]->GetHP() - 200);
                    middle_monster_time_one[i] = startTimer(1000);
                    middle_monster[i]->SetStrong(1);
                    if (middle_monster[i]->GetLay() != 1) {
                        middle_monster[i]->SetKind(0);
                    }
                }
            }
            if (middle_monster[i]->GetKind() == 8) {
                middle_monster[i]->AttackAnimation();
                middle_monster[i]->x_speed_left = 5;
                middle_monster[i]->x_speed_right = 5;
                if (middle_monster[i]->count_attack >= 9) {
                    middle_monster[i]->SetKind(9);
                    middle_monster[i]->photo = QPixmap(":/image/Resource/image/firemonkey/die/firemonkey_63.png");
                    middle_monster_time_two[i] = startTimer(500);
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
                if (ultra_monster[i]->life == 2) {
                    ultra_monster[i]->SetKind(12);
                    ultra_monster[i]->life--;
                    ultra_monster[i]->SetHP(15);
                }
                else
                {
                    ultra_monster[i]->SetKind(6);
                }
                ultra_monster[i]->SetLay(0);
            }
            qDebug() << ultra_monster[i]->GetKind();
            if (ultra_monster[i]->GetKind() == 6) {
                ultra_monster[i]->Die();
                ultra_monster_survive[i] = false;
                hero_one.SetExp(hero_one.GetExp() + 100);
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
                    ultra_monster_time_one[i] = startTimer(2000);
                    ultra_monster[i]->SetStrong(1);
                    if (ultra_monster[i]->GetLay() != 1 && ultra_monster[i]->life == 2) {
                        ultra_monster[i]->SetKind(0);
                    }
                }
            }
            if (ultra_monster[i]->GetKind() == 8) {
                ultra_monster[i]->AttackAnimation();
                hero_one.SetKind(8);
                ultra_monster[i]->x_speed_left = 15;
                ultra_monster[i]->x_speed_right = 15;
                ultra_monster[i]->y_speed = 10;
                if (ultra_monster[i]->count_attack >= 15) {
                    hero_one.SetHP(hero_one.GetHP() - 20);
                    ultra_monster[i]->SetHP(ultra_monster[i]->GetHP() + 10);
                    ultra_monster[i]->SetKind(9);
                    ultra_monster[i]->photo = QPixmap(":/image/Resource/image/zark/attacked/googuy_37.png");
                    ultra_monster_time_two[i] = startTimer(1000);
                }
            }
            if (ultra_monster[i]->GetKind() == 9) {
                ultra_monster[i]->SetLay(1);
            }
            if (ultra_monster[i]->GetKind() == 12) {
                ultra_monster[i]->Attack2Animation();
                if (ultra_monster[i]->count_attack >= 8) {
                    ultra_monster[i]->x_speed_left = 30;
                    ultra_monster[i]->x_speed_right = 30;
                    ultra_monster[i]->y_speed = 20;
                    ultra_monster[i]->SetKind(13);
                }
            }
            if (ultra_monster[i]->GetKind() == 14) {
                ultra_monster[i]->life++;
                ultra_monster[i]->SetHP(50);
                ultra_monster[i]->AttackAnimation();
                hero_one.SetKind(8);
                ultra_monster[i]->x_speed_left = 15;
                ultra_monster[i]->x_speed_right = 15;
                ultra_monster[i]->y_speed = 10;
                if (ultra_monster[i]->count_attack >= 15) {
                    hero_one.SetHP(hero_one.GetHP() - 20);
                    ultra_monster[i]->SetKind(9);
                    ultra_monster[i]->photo = QPixmap(":/image/Resource/image/zark/attacked/googuy_37.png");
                    ultra_monster_time_two[i] = startTimer(1000);
                }
            }
        }
    }
    for (int i = 1; i < sorcerer_one.size(); i++) {
        if (sorcerer_one_survive[i] == true) {
            sorcerer_one[i]->Move(hero_one);
            if (sorcerer_one[i]->GetStrong() == 0) {
                sorcerer_one[i]->BeAttacked(hero_one);
            }
            if (sorcerer_one[i]->GetHP() == 0) {
                sorcerer_one[i]->SetStrong(1);
                sorcerer_one[i]->SetKind(6);
            }
            if (sorcerer_one[i]->GetKind() == 6) {
                sorcerer_one[i]->Die();
                sorcerer_one_survive[i] = false;
                hero_one.SetExp(hero_one.GetExp() + 30);
                delete sorcerer_one[i];
            }
            if (sorcerer_one[i]->GetKind() != 4) {
                sorcerer_one[i]->attack_range.setWidth(0);
                sorcerer_one[i]->attack_range.setHeight(0);
            }
            if (sorcerer_one[i]->GetKind() != 7) {
                sorcerer_one[i]->real_body.moveTo(sorcerer_one[i]->real_body_x - sorcerer_one[i]->real_body_width / 2, sorcerer_one[i]->real_body_y - sorcerer_one[i]->real_body_height / 2);
                sorcerer_one[i]->real_body.setWidth(sorcerer_one[i]->real_body_width);   //攻击矩形(碰撞检测)
                sorcerer_one[i]->real_body.setHeight(sorcerer_one[i]->real_body_height);
            }
            else {
                sorcerer_one[i]->real_body.moveTo(sorcerer_one[i]->real_body_x - sorcerer_one[i]->real_body_width / 2, sorcerer_one[i]->real_body_y - sorcerer_one[i]->real_body_height / 2);
                sorcerer_one[i]->real_body.setWidth(0);   //攻击矩形(碰撞检测)
                sorcerer_one[i]->real_body.setHeight(0);
                sorcerer_one[i]->attack_range.setWidth(0);
                sorcerer_one[i]->attack_range.setHeight(0);
            }
            if (sorcerer_one[i]->GetKind() == 5 && sorcerer_one[i]->GetStrong() == 0) {
                sorcerer_one[i]->BeAttackedAnimation();
                if (sorcerer_one[i]->count_attack >= 2) {
                    sorcerer_one[i]->SetHP(sorcerer_one[i]->GetHP() - 30);
                    sorcerer_one_time[i] = startTimer(1000);
                    sorcerer_one[i]->SetStrong(1);
                    sorcerer_one[i]->SetKind(0);
                }
            }
        }
    }
    for (int i = 1; i < sorcerer_one.size(); i++) {
        for (int m = 1; m < sorcerer_one[i]->bullet_collector.size(); m++) {
            if (hero_one.GetStrong() == 0) {
                if (sorcerer_one[i]->bullet_collector[m]->attack_range.intersects(hero_one.real_body)) {
                    hero_one.SetHP(hero_one.GetHP() - 1);
                    hero_one.SetKind(5);
                }
            }
        }
    }
    int little_monster_num;
    int middle_monster_num;
    int ultra_monster_num;
    if (mode == 1 && (map_choose == 1 || map_choose == 2 || map_choose == 3)) {
        int little_dead_num = 0;
        for (int i = 1; i < little_monster_survive.size(); i++)
        {
            if (little_monster_survive[i] == false) {
                little_dead_num++;
            }
        }
        if (little_dead_num == little_monster_survive.size() - 1 && map_choose == 1) {
            map_choose++;
            if (map_choose == 2) {
                little_monster_num = 6;
                little_monster.resize(little_monster_num);
                little_monster_survive.resize(little_monster_num);
                little_monster_time.resize(little_monster_num);
                for (int i = 1; i < little_monster_num; i++) {
                    little_monster[i] = new LittleMonster(0);
                    little_monster_survive[i] = true;
                }
            }
        }
        if (little_dead_num == little_monster_survive.size() - 1 && map_choose == 2) {
            int middle_dead_num = 0;
            for (int i = 1; i < middle_monster_survive.size(); i++)
            {
                if (middle_monster_survive[i] == false) {
                    middle_dead_num++;
                }
            }
            if (middle_dead_num == middle_monster_survive.size() - 1)
            {
                middle_monster.resize(middle_monster_num);
                middle_monster_survive.resize(middle_monster_num);
                middle_monster_time_one.resize(middle_monster_num);
                middle_monster_time_two.resize(middle_monster_num);
                for (int i = 1; i < middle_monster_num; i++) {
                    middle_monster[i] = new MiddleMonster();
                    middle_monster_survive[i] = true;
                }
                little_monster_num = 6;
                little_monster.resize(little_monster_num);
                little_monster_survive.resize(little_monster_num);
                little_monster_time.resize(little_monster_num);
                for (int i = 1; i < little_monster_num; i++) {
                    little_monster[i] = new LittleMonster(1);
                    little_monster_survive[i] = true;
                }
                qDebug() << "好的";
            }
        }
    }
    if (mode == 2) {
        int little_dead_num = 0;
        for (int i = 1; i < little_monster_survive.size(); i++)
        {
            if (little_monster_survive[i] == false) {
                little_dead_num++;
            }
        }
        int middle_dead_num = 0;
        for (int i = 1; i < middle_monster_survive.size(); i++)
        {
            if (middle_monster_survive[i] == false) {
                middle_dead_num++;
            }
        }
        int ultra_dead_num = 0;
        for (int i = 1; i < ultra_monster_survive.size(); i++)
        {
            if (ultra_monster_survive[i] == false) {
                ultra_dead_num++;
            }
        }
        if (little_dead_num == little_monster_survive.size() - 1 && middle_dead_num == middle_monster_survive.size() - 1 && ultra_dead_num == ultra_monster_survive.size() - 1) {
            little_monster_num = map_choose * (-1) * 3;
            little_monster.resize(little_monster_num);
            little_monster_survive.resize(little_monster_num);
            little_monster_time.resize(little_monster_num);
            for (int i = 1; i < little_monster_num; i++) {
                little_monster[i] = new LittleMonster(1);
                little_monster_survive[i] = true;
            }
            if (map_choose < -9) {
                middle_monster_num = map_choose * (-1) * 2;
                middle_monster.resize(middle_monster_num);
                middle_monster_survive.resize(middle_monster_num);
                middle_monster_time_one.resize(middle_monster_num);
                middle_monster_time_two.resize(middle_monster_num);
                for (int i = 1; i < middle_monster_num; i++) {
                    middle_monster[i] = new MiddleMonster();
                    middle_monster_survive[i] = true;
                }
            }
            if (map_choose < -2) {
                ultra_monster_num = map_choose * (-1);
                ultra_monster.resize(ultra_monster_num);
                ultra_monster_survive.resize(ultra_monster_num);
                ultra_monster_time_one.resize(ultra_monster_num);
                ultra_monster_time_two.resize(ultra_monster_num);
                for (int i = 1; i < ultra_monster_num; i++) {
                    ultra_monster[i] = new UltraMonster();
                    ultra_monster_survive[i] = true;
                }
            }
            map_choose--;
        }
    }
}