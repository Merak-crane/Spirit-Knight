#include "Character.h"
#include <QPainter>
#include <QDebug>
#include <cmath>

Character::Character() {
    count_left = 0;
    count_right = 0;
    count_attack = 0;
    size_factor = 2.5;
    image_width = static_cast<int>(size_factor * 138);
    image_height = static_cast<int>(size_factor * 107);
}

void Character::WalkLeft() {
    x -= x_speed_left;
    real_body_x -= x_speed_left;
    QImage image(FrameAnimation(running.skill_picture, count_left));
    QImage mirroredImage = image.mirrored(true, false);
    photo = QPixmap::fromImage(mirroredImage);
}


void Character::WalkRight() {
    x += x_speed_right;
    real_body_x += x_speed_left;
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
    for (int i = start; num <= count; i++)
    {
        d = QString::number(i, 10);
        picture[num] = a + d + b;
        num++;
    }
}

void Character::Attack() {
    if (attacknum == 1) {
        if (direction == 0) {
            attack_range.moveTo(real_body_x - real_body_width / 2,real_body_y - real_body_height / 2 - 50);
            attack_range.setWidth(attack_range_x + real_body_width);   //¹¥»÷¾ØÐÎ(Åö×²¼ì²â)
            attack_range.setHeight(attack_range_y + real_body_width / 2);
            photo = QPixmap(FrameAnimation(attack.skill_picture, count_attack));
        }
        else {
            attack_range.moveTo(real_body_x - real_body_width / 2 - attack_range_x, real_body_y - real_body_height / 2);
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
    real_body_y -= y_speed;
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
    real_body_y += y_speed;
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
    photo = die.skill_picture[die.skill_picture.size() - 1];
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
    real_body_width = 38 * size_factor;
    real_body_height = 41 * size_factor;
    real_body_x = x + image_width / 2;
    real_body_y = y + image_height / 2;
    x_speed_left = 50;
    x_speed_right = 50;
    y_speed = 40;
    kind = 0;
    count_attack = 0;
    count_left = 0;
    count_right = 0;
    count_top = 0;
    strong = 0;
    real_body.moveTo(real_body_x, real_body_y);
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
void Hero::BeAttacked(LittleMonster *monster[], bool monster_survive[]) {
    for (int i = 1; i < 11; i++)
    {
        if (monster_survive[i] == true) {
            if (monster[i]->GetKind() != 6) {
                if (monster[i]->attack_range.intersects(real_body)) {
                    kind = 5;
                }
            }
        }
    }
}
LittleMonster::LittleMonster() {
    x = (rand() % ( 1200 + 1)) + 0;
    y = (rand() % ( 600 + 1)) + 0;
    real_body_width = 59 * size_factor;
    real_body_height = 44 * size_factor;
    real_body_x = x + image_width/2;
    real_body_y = y + image_height/2;
    x_speed_left = 5;
    x_speed_right = 5;
    y_speed = 10;
    count_attack = 0;
    count_left = 0;
    count_right = 0;
    count_top = 0;
    direction = 0;
    kind = 0;
    strong = 0;
    health_point = 100;
    health_point_max = 100;
    attack_range_x = 100;
    attack_range_y = 100;
    photo = QPixmap(":/image/Resource/image/little_monter/attack1/panther_47.png");
    PathCreator(":/image/Resource/image/little_monter/run1/panther_", ".png", 11, 6, running.skill_picture);
    PathCreator(":/image/Resource/image/little_monter/attack1/panther_", ".png", 47, 10, attack.skill_picture);
    PathCreator(":/image/Resource/image/little_monter/beattack/panther_", ".png", 33, 9, be_attack.skill_picture);
    PathCreator(":/image/Resource/image/little_monter/beattack/panther_", ".png", 33, 9, die.skill_picture);
}

void LittleMonster::Move(Hero player) {
    if (kind != 5) {
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
}

void LittleMonster::BeAttacked(Hero hero) {
    if (hero.attack_range.intersects(real_body)) {
        kind = 5;
    }
}

void LittleMonster::Attack() {
    if (direction == 0) {
        attack_range.moveTo(real_body_x - real_body_width / 2, real_body_y - real_body_height / 2);
        attack_range.setWidth(attack_range_x + real_body_width);   //¹¥»÷¾ØÐÎ(Åö×²¼ì²â)
        attack_range.setHeight(attack_range_y + real_body_width / 2);
        photo = QPixmap(FrameAnimation(attack.skill_picture, count_attack));
    }
    else {
        attack_range.moveTo(real_body_x - real_body_width / 2 - attack_range_x, real_body_y - real_body_height / 2);
        attack_range.setWidth(attack_range_x);   //¹¥»÷¾ØÐÎ(Åö×²¼ì²â)
        attack_range.setHeight(attack_range_y);
        QImage image(FrameAnimation(attack.skill_picture, count_attack));
        QImage mirroredImage = image.mirrored(true, false);
        photo = QPixmap::fromImage(mirroredImage);
    }
}

void LittleMonster::BeAttackedAnimation() {
    if (direction == 0) {
        photo = QPixmap(FrameAnimation(be_attack.skill_picture, count_attack));
    }
    else {
        QImage image(FrameAnimation(be_attack.skill_picture, count_attack));
        QImage mirroredImage = image.mirrored(true, false);
        photo = QPixmap::fromImage(mirroredImage);
    }
}

MiddleMonster::MiddleMonster() {
    x = (rand() % (1200 + 1)) + 0;
    y = (rand() % (600 + 1)) + 0;
    real_body_width = 40 * size_factor;
    real_body_height = 37 * size_factor;
    real_body_x = x + image_width / 2;
    real_body_y = y + image_height / 2;
    x_speed_left = 5;
    x_speed_right = 5;
    y_speed = 10;
    count_attack = 0;
    count_left = 0;
    count_right = 0;
    count_top = 0;
    direction = 0;
    kind = 0;
    strong = 0;
    health_point = 100;
    health_point_max = 100;
    attack_range_x = 100;
    attack_range_y = 100;
    photo = QPixmap(":/image/Resource/image/little_monter/attack1/panther_47.png");
    PathCreator(":/image/Resource/image/firemonkey/run/firemonkey_", ".png", 16, 6, running.skill_picture);
    PathCreator(":/image/Resource/image/firemonkey/dash/firemonkey_", ".png", 31, 11, attack.skill_picture);
    PathCreator(":/image/Resource/image/firemonkey/2phace/firemonkey_", ".png", 46, 14, attack_two.skill_picture);
    PathCreator(":/image/Resource/image/firemonkey/die/firemonkey_", ".png", 60, 4, be_attack.skill_picture);
    PathCreator(":/image/Resource/image/firemonkey/die/firemonkey_", ".png", 60, 4, die.skill_picture);
}
void MiddleMonster::Move(Hero player) {
    if (kind != 5) {
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
}

void MiddleMonster::BeAttacked(Hero hero) {
    if (hero.attack_range.intersects(real_body)) {
        kind = 5;
    }
}

void MiddleMonster::Attack() {
    if (direction == 0) {
        x += x_speed_right;
        real_body_x += x_speed_right;
        attack_range.moveTo(real_body_x - real_body_width / 2, real_body_y - real_body_height / 2);
        attack_range.setWidth(attack_range_x + real_body_width);   //¹¥»÷¾ØÐÎ(Åö×²¼ì²â)
        attack_range.setHeight(attack_range_y + real_body_width / 2);
        photo = QPixmap(FrameAnimation(attack.skill_picture, count_attack));
    }
    else {
        x -= x_speed_left;
        real_body_x -= x_speed_left;
        attack_range.moveTo(real_body_x - real_body_width / 2 - attack_range_x, real_body_y - real_body_height / 2);
        attack_range.setWidth(attack_range_x);   //¹¥»÷¾ØÐÎ(Åö×²¼ì²â)
        attack_range.setHeight(attack_range_y);
        QImage image(FrameAnimation(attack.skill_picture, count_attack));
        QImage mirroredImage = image.mirrored(true, false);
        photo = QPixmap::fromImage(mirroredImage);
    }
}

void MiddleMonster::BeAttackedAnimation() {
    if (direction == 0) {
        photo = QPixmap(FrameAnimation(be_attack.skill_picture, count_attack));
    }
    else {
        QImage image(FrameAnimation(be_attack.skill_picture, count_attack));
        QImage mirroredImage = image.mirrored(true, false);
        photo = QPixmap::fromImage(mirroredImage);
    }
}