#include "Character.h"
#include<QDebug>
BulletOne::BulletOne(int x, int y, int direction) {
	photo = QPixmap(":/image/Resource/image/bomber/bullet/foxtar_90.png");//×Óµ¯ÕÕÆ¬Â·¾¶
	this->x = x;
	this->y = y - 30;
	this->direction = direction;
	x_speed = 30;
	image_height = 50;
	image_width = 50;
	real_body_width = 59 * size_factor;
	real_body_height = 44 * size_factor;
	real_body_x = this->x + image_width / 2;
	real_body_y = this->y + image_height / 2;
	attack_range_x = 40;
	attack_range_y = 40;
}

int Bullet::GetX() {
	return x;
}

int Bullet::GetY() {
	return y;
}

void Bullet::BulletUpdate(int x, int y, int direction) {
	this->x = x;
	this->y = y;
	this->direction = direction;
}

void BulletOne::Move() {
	if (direction == 0) {
		x += x_speed;
	}
	else
	{
		x -= x_speed;
	}
}

bool BulletOne::Disappear() {
	attack_range.moveTo(x + 10 - attack_range_x / 2, y + 20 - attack_range_y / 2);
	attack_range.setWidth(attack_range_x);   //¹¥»÷¾ØÐÎ(Åö×²¼ì²â)
	attack_range.setHeight(attack_range_y);
	if (x > 1280 || x < 0) {
		//delete this;
		return true;
	}
}