#pragma once
#include <vector>
#include <string>
using namespace std;

class Picture {
public:
	//void Animation(vector <const char*> motion);
public:
	vector <const char*> advance;//前进
	vector <const char*> draw_back;//后退
	vector <const char*> attack;//普通攻击
	vector <const char*> skill_one;//技能1
	const char* stand;
};//存储每个基本动作多张图片的相对路径

class Character {
public:
	void WalkLeft();
	void WalkRight();
	void WalkTop();
	void WalkDown();
	int GetX();
	int GetY();
	void SetX(int x);
	void SetY(int y);
	const char* GetStand();
protected:
	double health_point;
	double magic_point;
	double experience;
	int x;
	int y;
	int x_speed;
	int y_speed;
	int level;
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