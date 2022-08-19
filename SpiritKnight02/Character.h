#pragma once
#include <vector>
#include <string>
#include <QPainter>
using namespace std;

class Picture {
public:
	//void Animation(vector <const char*> motion);
public:
	vector <const char*> advance;//前进
	vector <const char*> draw_back;//后退
	vector <const char*> attack_right;//普通右攻击
	vector <const char*> attack_left;//普通左攻击
	vector <const char*> skill_one;//技能1
	const char* stand_right;
	const char* stand_left;
};//存储每个基本动作多张图片的相对路径

class Character {
public:
	int kind;
	int attack;
	int count_left;
	int count_right;
	int count_attack;
	int x_speed_right;
	int x_speed_left;
	QPixmap photo;
	Character();
	void WalkLeft();
	void WalkRight();
	void WalkTop();
	void WalkDown();
	void Attack();
	int GetX();
	int GetY();
	int GetDirection();
	void SetDirection(int direction);
	void SetX(int x);
	void SetY(int y);
	const char* GetStandRight();
	const char* GetStandLeft();
protected:
	double health_point;
	double magic_point;
	double experience;
	int x;
	int y;
	int y_speed;
	int level;
	int direction;
	Picture picture;
};

class Hero : public Character {
public:
	Hero();
	void Show();
};

class LittleMonster: public Character {
public:

};

class MiddleMonster : public Character {
public:

};

class UltraMonster : public Character {
public:

};