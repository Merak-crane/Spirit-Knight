#include "Character.h"
#include <QPainter>
#include <QDebug>
#include <cmath>

Character::Character() {
    count_left = 0;
    count_right = 0;
    count_attack = 0;
}

void Character::WalkLeft() {
    x -= x_speed_left;
    QImage image(FrameAnimation(running.skill_picture, count_left));
    QImage mirroredImage = image.mirrored(true, false);
    photo = QPixmap::fromImage(mirroredImage);
}


void Character::WalkRight() {
    x += x_speed_right;
    photo = QPixmap(FrameAnimation(running.skill_picture, count_right));
}

QString Character::FrameAnimation(vector <QString> picture, int& count) {
    count++;
    if (count > picture.size() - 1) count = 1;
    return picture[count];
}

void Character::PathCreator(QString a, QString b, int start, int count, vector <QString> &picture) {
    int p = count + 1;
    picture.resize(p);
    picture[0] = "0";
    int num = 1;
    QString c;
    QString d;
    for (int i = start; num < count; i++)
    {
        d = QString::number(i, 10);
        picture[num] = a + d + b;
        qDebug() << picture[num];
        num++;
    }
}

void Character::Attack() {
    if (attacknum == 1) {
        if (direction == 0) {
            photo = QPixmap(FrameAnimation(attack.skill_picture, count_attack));
        }
        else {
            QImage image(FrameAnimation(attack.skill_picture, count_attack));
            QImage mirroredImage = image.mirrored(true, false);
            photo = QPixmap::fromImage(mirroredImage);
        }
    }
    //if (attacknum == 2) {
    //    if (direction == 0) {
    //        photo = QPixmap(FrameAnimation(first_skill.skill_picture, count_attack));
    //    }
    //    else {
    //        QImage image(FrameAnimation(second_skill.skill_picture, count_attack));
    //        QImage mirroredImage = image.mirrored(true, false);
    //        photo = QPixmap::fromImage(mirroredImage);
    //    }
    //}
}

void Character::WalkTop() {
    y -= y_speed;
    if (direction == 0) {
        photo = QPixmap(FrameAnimation(running.skill_picture, count_top));
    }
    else {
        QImage image(FrameAnimation(running.skill_picture, count_top));
        QImage mirroredImage = image.mirrored(true, false);
        photo = QPixmap::fromImage(mirroredImage);
    }
}

void Character::WalkDown() {
    y += y_speed;
    if (direction == 0) {
        photo = QPixmap(FrameAnimation(running.skill_picture, count_top));
    }
    else {
        QImage image(FrameAnimation(running.skill_picture, count_top));
        QImage mirroredImage = image.mirrored(true, false);
        photo = QPixmap::fromImage(mirroredImage);
    }
}

int Character::GetX() {
    return x;
}

int Character::GetY() {
    return y;
}

int Character::GetKind() {
    return kind;
}

int Character::GetDirection() {
    return direction;
}

void Character::SetX(int X) {
    this->x = x;
}

void Character::SetY(int y) {
    this->y = y;
}

void Character::SetKind(int kind) {
    this->kind = kind;
}

void Character::SetDirection(int direction) {
    this->direction = direction;
}

Hero::Hero() {
    x = 500;
    y = 500;
    x_speed_left = 50;
    x_speed_right = 50;
    y_speed = 40;
    kind = 0;
    count_attack = 0;
    count_left = 0;
    count_right = 0;
    count_top = 0;
    photo = QPixmap(":/image/Resource/image/main_character/running3/zero4_5.png");
    PathCreator(":/image/Resource/image/main_character/running3/zero4_", ".png", 5, 13, running.skill_picture);
    PathCreator(":/image/Resource/image/main_character/slice1/zero2_", ".png", 18, 11, attack.skill_picture);
}
void Hero::Show() {
    
}

LittleMonster::LittleMonster() {
    x = 400;
    y = 400;
    x_speed_left = 5;
    x_speed_right = 5;
    y_speed = 10;
    count_attack = 0;
    count_left = 0;
    count_right = 0;
    count_top = 0;
    direction = 0;
    attack_range = 40;
    photo = QPixmap(":/image/Resource/image/main_character/running3/zero4_5.png");
    PathCreator(":/image/Resource/image/main_character/running3/zero4_", ".png", 5, 13, running.skill_picture);
    PathCreator(":/image/Resource/image/main_character/slice1/zero2_", ".png", 18, 11, attack.skill_picture);
}

void LittleMonster::Move(Hero player) {
    if (x < player.GetX() + attack_range && x > player.GetX() - attack_range && y < player.GetY() + 20 && y > player.GetY() - 20)
    {
        if (x <= player.GetX()) direction = 0;
        else { direction = 1; }
        SetKind(4);
        Attack();
    }
    else {
        SetKind(1);
        if (y <= player.GetY()) {
            WalkDown();
        }
        if (y > player.GetY()) {
            WalkTop();
        }
        if (x >= player.GetX()) {
            WalkLeft();
        }
        if (x < player.GetX()) {
            WalkRight();
        }
    }
}

void LittleMonster::Attack() {
    if (direction == 0) {
        photo = QPixmap(FrameAnimation(attack.skill_picture, count_attack));
    }
    else {
        QImage image(FrameAnimation(attack.skill_picture, count_attack));
        QImage mirroredImage = image.mirrored(true, false);
        photo = QPixmap::fromImage(mirroredImage);
    }
}