#include "Character.h"
BulletOne::BulletOne(int x, int y, int direction) {
	photo = QPixmap(":/image/Resource/image/little_monter/beattack/panther_38.png");//×Óµ¯ÕÕÆ¬Â·¾¶
	this->x = x;
	this->y = y;
	x_speed = 50;
	real_body_width = 59 * size_factor;
	real_body_height = 44 * size_factor;
	real_body_x = x + image_width / 2;
	real_body_y = y + image_height / 2;
	attack_range_x = 1000;
	attack_range_y = 40;
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

void BulletOne::Disappear() {
	attack_range.moveTo(real_body_x - attack_range_x / 2, real_body_y - attack_range_y / 2);
	attack_range.setWidth(attack_range_x);   //¹¥»÷¾ØÐÎ(Åö×²¼ì²â)
	attack_range.setHeight(attack_range_y);
	if (x > 1280 || x < 0) {
		delete this;
	}
}