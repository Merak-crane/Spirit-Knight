#include "Character.h"
#include <QPainter>
#include <QDebug>
#include <cmath>
//void Picture::Animation(vector <char *> motion) {
//    int count = 0;
//    if (count > 8) count = 1;
//    switch (count) {
//    case 1:
//        photo = QPixmap(motion[1]);
//        break;
//    case 3:
//        photo = QPixmap(motion[2]);
//        break;
//    case 5:
//        photo = QPixmap(motion[3]);
//        break;
//    case 7:
//        photo = QPixmap(motion[4]);
//        break;
//    default:
//        break;
//    }
//}

Character::Character() {
    count_left = 0;
    count_right = 0;
    count_attack = 0;
}

const char* Character::GetStandRight() {
    return picture.stand_right;
}

const char* Character::GetStandLeft() {
    return picture.stand_left;
}
void Character::WalkLeft() {
    x -= x_speed_left;
    if (x_speed_left < 500) {
        x_speed_left = 10*log(3*count_left + 1) / log(2);
    }
    count_left++;
    qDebug() << x_speed_left;
    if (count_left > 8) count_left = 1;
    switch (count_left) {
    case 1:
        photo = QPixmap(picture.draw_back[1]);
        break;
    case 3:
        photo = QPixmap(picture.draw_back[2]);
        break;
    case 5:
        photo = QPixmap(picture.draw_back[3]);
        break;
    case 7:
        photo = QPixmap(picture.draw_back[4]);
        break;
    default:
        break;
    }
}


void Character::WalkRight() {
    x += x_speed_right;
    if (x_speed_right < 500) {
        x_speed_right = 10 * log(3 * count_right + 1) / log(2);
    }
    count_right++;
    if (count_right > 8) count_right = 1;
    switch (count_right) {
    case 1:
        photo = QPixmap(picture.advance[1]);
        break;
    case 3:
        photo = QPixmap(picture.advance[2]);
        break;
    case 5:
        photo = QPixmap(picture.advance[3]);
        break;
    case 7:
        photo = QPixmap(picture.advance[4]);
        break;
    default:
        break;
    }
}

void Character::Attack() {
    if (attack == 1) {
        count_attack++;
        qDebug() << count_attack;
        if (count_attack > 11) count_attack = 1;
        switch (count_attack) {
        case 1:
            if (direction == 0) photo = QPixmap(":/image/Resource/image/2att01.png");
            if (direction == 1) photo = QPixmap(":/image/Resource/image/2att01left.png");
            break;
        case 2:
            if (direction == 0) photo = QPixmap(":/image/Resource/image/2att02.png");
            if (direction == 1) photo = QPixmap(":/image/Resource/image/2att02left.png");
            break;
        case 3:
            if (direction == 0) photo = QPixmap(":/image/Resource/image/2att03.png");
            if (direction == 1) photo = QPixmap(":/image/Resource/image/2att03left.png");
            break;
        case 4:
            if (direction == 0) photo = QPixmap(":/image/Resource/image/2att04.png");
            if (direction == 1) photo = QPixmap(":/image/Resource/image/2att04left.png");
            break;
        case 6:
            if (direction == 0) photo = QPixmap(":/image/Resource/image/2att05.png");
            if (direction == 1) photo = QPixmap(":/image/Resource/image/2att05left.png");
            break;
        case 8:
            if (direction == 0) photo = QPixmap(":/image/Resource/image/2att06.png");
            if (direction == 1) photo = QPixmap(":/image/Resource/image/2att06left.png");
            break;
        case 9:
            if (direction == 0) photo = QPixmap(":/image/Resource/image/2att07.png");
            if (direction == 1) photo = QPixmap(":/image/Resource/image/2att07left.png");
            break;
        case 10:
            if (direction == 0) photo = QPixmap(":/image/Resource/image/stand01.png");
            if (direction == 1) photo = QPixmap(":/image/Resource/image/stand01left.png");
            break;
        default:
            break;
        }
    }
    //if (attack == 2) {
    //    switch (count_attack) {
    //    case 1:
    //        if (direction == 1) picture = QPixmap(":/new/prefix1/pictures/3att01.png");
    //        if (direction == 0) picture = QPixmap(":/new/prefix1/pictures/3att01left.png");
    //        break;
    //    case 2:
    //        if (direction == 1) picture = QPixmap(":/new/prefix1/pictures/3att02.png");
    //        if (direction == 0) picture = QPixmap(":/new/prefix1/pictures/3att02left.png");
    //        break;
    //    case 3:
    //        if (direction == 1) picture = QPixmap(":/new/prefix1/pictures/3att03.png");
    //        if (direction == 0) picture = QPixmap(":/new/prefix1/pictures/3att03left.png");
    //        break;
    //    case 4:
    //        if (direction == 1) picture = QPixmap(":/new/prefix1/pictures/3att04.png");
    //        if (direction == 0) picture = QPixmap(":/new/prefix1/pictures/3att04left.png");
    //        break;
    //    case 6:
    //        if (direction == 1) picture = QPixmap(":/new/prefix1/pictures/3att05.png");
    //        if (direction == 0) picture = QPixmap(":/new/prefix1/pictures/3att05left.png");
    //        break;
    //    case 8:
    //        if (direction == 1) picture = QPixmap(":/new/prefix1/pictures/3att06.png");
    //        if (direction == 0) picture = QPixmap(":/new/prefix1/pictures/3att06left.png");
    //        break;
    //    case 9:
    //        if (direction == 1) picture = QPixmap(":/new/prefix1/pictures/3att07.png");
    //        if (direction == 0) picture = QPixmap(":/new/prefix1/pictures/3att07left.png");
    //        break;
    //    case 10:
    //        if (direction == 1) picture = QPixmap(":/new/prefix1/pictures/stand01.png");
    //        if (direction == 0) picture = QPixmap(":/new/prefix1/pictures/stand01left.png");
    //        break;
    //    default:
    //        break;
    //    }
    //}
}

void Character::WalkTop() {
    y -= y_speed;
}

void Character::WalkDown() {
    y += y_speed;
}

int Character::GetX() {
    return x;
}

int Character::GetY() {
    return y;
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

void Character::SetDirection(int direction) {
    this->direction = direction;
}

Hero::Hero() {
    x = 500;
    y = 500;
    x_speed_left = 5;
    x_speed_right = 5;
    y_speed = 10;
    photo = QPixmap(":/image/Resource/image/stand01.png");
    picture.advance.resize(6);
    picture.draw_back.resize(6);
    picture.advance[0] = 0;
    picture.advance[1] = ":/image/Resource/image/forward01.png";
    picture.advance[2] = ":/image/Resource/image/forward02.png";
    picture.advance[3] = ":/image/Resource/image/forward03.png";
    picture.advance[4] = ":/image/Resource/image/forward04.png";
    picture.draw_back[1] = ":/image/Resource/image/forward01left.png";
    picture.draw_back[2] = ":/image/Resource/image/forward02left.png";
    picture.draw_back[3] = ":/image/Resource/image/forward03left.png";
    picture.draw_back[4] = ":/image/Resource/image/forward04left.png";
    picture.stand_right = ":/image/Resource/image/stand01.png";
    picture.stand_left = ":/image/Resource/image/stand01left.png";
}

void Hero::Show() {
    
}