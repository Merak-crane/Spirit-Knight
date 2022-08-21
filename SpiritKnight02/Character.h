#pragma once
#include <vector>
#include <string>
#include <QPainter>
using namespace std;

class Skill {
public:
	vector<QString> skill_picture;
	int count;
private:
	double range_x;
	double range_y;
};

class Character {
public:
	Skill attack;
	QRect attack_range;
	int attacknum;
	int count_left;
	int count_right;
	int count_top;
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
	void PathCreator(QString a, QString b, int c, int count, vector <QString> &picture);
	QString FrameAnimation(vector <QString> picture, int& count);
	int GetX();
	int GetY();
	int GetKind();
	int GetDirection();
	void SetDirection(int direction);
	void SetX(int x);
	void SetY(int y);
	void SetKind(int kind);
protected:
	int attack_range_x;
	int attack_range_y;
	double health_point;
	double magic_point;
	double experience;
	int kind;
	int x;
	int y;
	int y_speed;
	int level;
	int direction;
	Skill running;
	Skill first_skill;
	Skill second_skill;
};

class Hero : public Character {
private:
public:
	Hero();
	void Show();
	void h_attack();
	void h_beattacked();
};

class LittleMonster: public Character {
public:
	LittleMonster();
	void Move(Hero player);
	void Attack();
};

class MiddleMonster : public Character {
public:

};

class UltraMonster : public Character {
public:

};