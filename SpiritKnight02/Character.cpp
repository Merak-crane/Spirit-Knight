#include "Character.h"
#include <QPainter>
//void Picture::Animation(vector <char *> motion) {
//    int count = 0;
//    picture = QPicture();
//    if (count > 8) count = 1;
//    switch (count) {
//    case 1:
//        picture = QPixmap(motion[1]);
//        break;
//    case 3:
//        picture = QPixmap(motion[2]);
//        break;
//    case 5:
//        picture = QPixmap(motion[3]);
//        break;
//    case 7:
//        picture = QPixmap(motion[4]);
//        break;
//    default:
//        break;
//    }
//}

const char* Character::GetStand() {
    return picture.stand;
}

void Character::walkleft() {

}

int Character::GetX() {
    return x;
}

int Character::GetY() {
    return y;
}

void Character::SetX(int X) {
    this->x = x;
}

void Character::SetY(int y) {
    this->y = y;
}

Hero::Hero() {
    x = 500;
    y = 500;
    picture.advance.resize(6);
    picture.advance[0] = 0;
    picture.advance[1] = ":/image/Resource/image/forward01.png";
    picture.advance[2] = ":/image/Resource/image/forward02.png";
    picture.advance[3] = ":/image/Resource/image/forward03.png";
    picture.advance[4] = ":/image/Resource/image/forward04.png";
    picture.stand = ":/image/Resource/image/stand01.png";
}

void Hero::Show() {
    
}