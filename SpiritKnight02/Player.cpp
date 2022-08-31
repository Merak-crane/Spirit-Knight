#include "Player.h"
Player::Player(){
	level = 1;
	exp = 100;
}

Player::~Player()
{
}

QString Player::GetUsername() {
	return username;
}

int Player::GetLevel() {
	return level;
}

int Player::GetHP() {
	return hp;
}

int Player::GetMP() {
	return mp;
}

int Player::GetEXP() {
	return exp;
}