#include "Tutorial.h"
#include "StartInterface.h"
#include <QKeyEvent>
Tutorial::Tutorial(Player* local, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    this->local = local;
    Long = new ProfessorLong;
    hero_one.SetLevel(local->GetLevel());
    hero_one.StatusUpdate();
    int DeskWidth = 1280;
    int DeskHeight = 800;//获取设备的分辨率
    this->setFixedSize(DeskWidth, DeskHeight);//设置窗口大小
    this->setWindowTitle("Mega Man E");//设置窗口标题
    this->setWindowIcon(QIcon(":/icon/Resource/icon/htmlogo.png"));//设置窗口logo
    tutorial = new QLabel(this);
    tutorial->setObjectName("tutorial");
    hp = new QLabel(this);
    hp->setObjectName("HP");
    mp = new QLabel(this);
    mp->setObjectName("MP");
    exp = new QLabel(this);
    exp->setObjectName("EXP");
    user_information_label = new QLabel(this);
    user_information_label->setObjectName("user_information_label");
    map_time.setInterval(GAME_RATE);
    map_time.start();
    tutorial->setGeometry(Long->GetX(), Long->GetY(), 800, 50);
    tutorial->setText("I'm your teacher Professor Long, please press A to move left");

    returnbtn_tutorial->resize(240, 80);
    returnbtn_tutorial->move(1000, 650);
    QPixmap p12 = QPixmap(":/ui/Resource/image/ui/returnback.png");
    returnbtn_tutorial->setIcon(p12);
    returnbtn_tutorial->setIconSize(QSize(240, 80));
    returnbtn_tutorial->setFlat(true);

    connect(returnbtn_tutorial, &QPushButton::clicked, this, &Tutorial::ReturnBack);
    /* QMediaPlayer* player = new QMediaPlayer;*/
    connect(&map_time, &QTimer::timeout, [=]() {
        update();
        UpdateOne();
        });
}

void Tutorial::paintEvent(QPaintEvent* event) {
    QPainter* painter = new QPainter(this);
    if (hero_one.GetKind() == 0 && hero_one.GetDirection() == 1) {
        QImage image(":/image/Resource/image/main_character/running3/zero4_5.png");
        QImage mirroredImage = image.mirrored(true, false);
        hero_one.photo = QPixmap::fromImage(mirroredImage);
    }
    else if (hero_one.GetKind() == 0 && hero_one.GetDirection() == 0) {
        hero_one.photo = QPixmap(":/image/Resource/image/main_character/running3/zero4_5.png");
    }
    painter->drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/background/battleback10.png"));
    painter->drawPixmap(hero_one.GetX(), hero_one.GetY(), hero_one.image_width, hero_one.image_height, hero_one.photo);
    painter->drawPixmap(Long->GetX(), Long->GetY(), Long->image_width, Long->image_height, Long->photo);
    painter->drawPixmap(0, 0, 500, 150, QPixmap(":/image/Resource/image/main_character/hp.png"));
    hp->setGeometry(155, 110, hero_one.GetHP() * 320 / hero_one.GetHPMAX(), 10);
    mp->setGeometry(155, 122, hero_one.GetMP() * 320 / hero_one.GetMPMAX(), 10);
    exp->setGeometry(155, 134, hero_one.GetExp() * 320 / hero_one.GetExpmax(), 10);
    user_information_label->setGeometry(175, 45, 300, 80);
    QString information = QString("%1 Lv. %2").arg(local->GetUsername()).arg(hero_one.GetLevel());
    user_information_label->setText(information);
    delete painter;
}

void Tutorial::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_A://向左跑
        hero_one.SetDirection(1);//设置人物朝向
        hero_one.SetKind(1);;//设置人物状态
        tutorial->setGeometry(Long->GetX(), Long->GetY(), 400, 50);
        tutorial->setText("Press D to move right");
        break;
    case Qt::Key_D:
        hero_one.SetDirection(0);
        hero_one.SetKind(1);
        tutorial->setText("Press W to move");
        break;
    case Qt::Key_W:
        hero_one.SetKind(2);
        tutorial->setText("Press S to move");
        break;
    case Qt::Key_S:
        hero_one.SetKind(3);
        tutorial->setText("Press J to attack");
        break;
    case Qt::Key_J:
        hero_one.attacknum = 1;
        hero_one.SetKind(4);
        tutorial->setGeometry(Long->GetX(), Long->GetY(), 800, 50);
        tutorial->setText("I'm your teacher Professor Long, please press A to move left");
        break;
    default:
        break;
    }
}

void Tutorial::keyReleaseEvent(QKeyEvent* event) {
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

void Tutorial::UpdateOne() {
    if (hero_one.GetHP() == 0) {
        hero_one.SetStrong(1);
        hero_one.SetKind(6);
    }
    if (hero_one.GetExp() >= hero_one.GetExpmax()) {
        hero_one.SetLevel(hero_one.GetLevel() + 1);
        hero_one.SetExp(hero_one.GetExp() - 1000);
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
    if (hero_one.GetKind() == 6) {
        hero_one.Die();
    }
}

void Tutorial::ReturnBack() {
    StartInterface* intro = new StartInterface(local);
    intro->show();
    this->close();
}

Tutorial::~Tutorial()
{}
