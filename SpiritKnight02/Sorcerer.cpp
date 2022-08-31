#include "Character.h"
#include <QDebug>

SorcererOne::SorcererOne() {
    x = (rand() % (1200 + 1)) + 0;
    y = (rand() % (600 + 1)) + 0;
    real_body_width = 59 * size_factor;
    real_body_height = 44 * size_factor;
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
    attack_range_x = 1000;
    attack_range_y = 40;
    bullet_collector.resize(1);
    photo = QPixmap(":/image/Resource/image/little_monter/attack1/panther_47.png");
    PathCreator(":/image/Resource/image/little_monter/run1/panther_", ".png", 11, 6, running.skill_picture);
    PathCreator(":/image/Resource/image/little_monter/attack1/panther_", ".png", 47, 10, attack.skill_picture);
    PathCreator(":/image/Resource/image/little_monter/beattack/panther_", ".png", 33, 9, be_attack.skill_picture);
    PathCreator(":/image/Resource/image/little_monter/beattack/panther_", ".png", 33, 9, die.skill_picture);
}
void SorcererOne::Move(Hero player) {
    qDebug() << "ss";
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
    for (int i = 1; i < bullet_collector.size(); i++)
    {
        bullet_collector[i]->Disappear();
    }
}

void SorcererOne::Attack() {
    BulletOne* new_bullet = new BulletOne(x, y, direction);
    bullet_collector.push_back(new_bullet);
}

void SorcererOne::BeAttacked(Hero hero) {
    if (hero.attack_range.intersects(real_body)) {
        kind = 5;
    }
}

void SorcererOne::BeAttackedAnimation() {
    if (direction == 0) {
        photo = QPixmap(FrameAnimation(be_attack.skill_picture, count_attack));
    }
    else {
        QImage image(FrameAnimation(be_attack.skill_picture, count_attack));
        QImage mirroredImage = image.mirrored(true, false);
        photo = QPixmap::fromImage(mirroredImage);
    }
}