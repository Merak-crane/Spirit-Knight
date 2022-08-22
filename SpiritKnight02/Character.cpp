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
        num++;
    }
}

void Character::Attack() {
    if (attacknum == 1) {
        if (direction == 0) {
            attack_range.moveTo(x,y);
            attack_range.setWidth(attack_range_x);   //¹¥»÷¾ØÐÎ(Åö×²¼ì²â)
            attack_range.setHeight(attack_range_y);
            photo = QPixmap(FrameAnimation(attack.skill_picture, count_attack));
        }
        else {
            attack_range.moveTo(x - attack_range_x, y);
            attack_range.setWidth(attack_range_x);   //¹¥»÷¾ØÐÎ(Åö×²¼ì²â)
            attack_range.setHeight(attack_range_y);
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

void Character::Die() {
    photo = die.skill_picture[10];
}

void Hero::BeAttackedAnimation() {
    if (direction == 0) {
        photo = QPixmap(FrameAnimation(die.skill_picture, count_attack));
    }
    else {
        QImage image(FrameAnimation(die.skill_picture, count_attack));
        QImage mirroredImage = image.mirrored(true, false);
        photo = QPixmap::fromImage(mirroredImage);
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


int Character::GetX() {
    return x;
}

int Character::GetY() {
    return y;
}

int Character::GetKind() {
    return kind;
}

int Character::GetStrong() {
    return strong;
}

int Character::GetDirection() {
    return direction;
}

double Character::GetMP() {
    return magic_point;
}

double Character::GetHP() {
    return health_point;
}

double Character::GetMPMAX() {
    return magic_point_max;
}

double Character::GetHPMAX() {
    return health_point_max;
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

void Character::SetStrong(int strong) {
    this->strong = strong;
}

void Character::SetDirection(int direction) {
    this->direction = direction;
}

void Character::SetMP(double magic_point) {
    this->magic_point = magic_point;
}

void Character::SetHP(double health_point) {
    this->health_point = health_point;
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
    strong = 0;
    real_body.moveTo(x, y);
    real_body.setWidth(50);   //¹¥»÷¾ØÐÎ(Åö×²¼ì²â)
    real_body.setHeight(50);
    attack_range_x = 110;
    attack_range_y = 100;
    health_point_max = 200;
    magic_point_max = 200;
    health_point = 100;
    magic_point = 100;
    photo = QPixmap(":/image/Resource/image/main_character/running3/zero4_5.png");
    PathCreator(":/image/Resource/image/main_character/running3/zero4_", ".png", 5, 13, running.skill_picture);
    PathCreator(":/image/Resource/image/main_character/slice1/zero2_", ".png", 18, 11, attack.skill_picture);
    PathCreator(":/image/Resource/image/main_character/die/zero1_", ".png", 16, 11, die.skill_picture);
}
void Hero::Show() {

}
void Hero::BeAttacked(LittleMonster mirror) {
    if (mirror.attack_range.intersects(real_body)) {
        kind = 5;
    }
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
    attack_range_x = 40;
    attack_range_y = 40;
    photo = QPixmap(":/image/Resource/image/little_monter/attack1/panther_47.png");
    PathCreator(":/image/Resource/image/little_monter/run1/panther_", ".png", 11, 6, running.skill_picture);
    PathCreator(":/image/Resource/image/little_monter/attack1/panther_", ".png", 47, 10, attack.skill_picture);
}

void LittleMonster::Move(Hero player) {
    if (x < player.GetX() + attack_range_x && x > player.GetX() - attack_range_x && y < player.GetY() + attack_range_y && y > player.GetY() - attack_range_y)
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
        attack_range.moveTo(x, y);
        attack_range.setWidth(attack_range_x);   //¹¥»÷¾ØÐÎ(Åö×²¼ì²â)
        attack_range.setHeight(attack_range_y);
        photo = QPixmap(FrameAnimation(attack.skill_picture, count_attack));
    }
    else {
        attack_range.moveTo(x - attack_range_x, y);
        attack_range.setWidth(attack_range_x);   //¹¥»÷¾ØÐÎ(Åö×²¼ì²â)
        attack_range.setHeight(attack_range_y);
        QImage image(FrameAnimation(attack.skill_picture, count_attack));
        QImage mirroredImage = image.mirrored(true, false);
        photo = QPixmap::fromImage(mirroredImage);
    }
}