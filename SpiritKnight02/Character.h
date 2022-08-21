#pragma once
#include <vector>
#include <string>
#include <QPainter>
#include <QTimer>
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
	QRect attack_range;
	QRect real_body;
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
	void Die();
	void PathCreator(QString a, QString b, int c, int count, vector <QString> &picture);
	QString FrameAnimation(vector <QString> picture, int& count);
	int GetX();
	int GetY();
	int GetStrong();
	int GetKind();
	int GetDirection();
	double GetHP();
	double GetMP();
	double GetHPMAX();
	double GetMPMAX();
	void SetDirection(int direction);
	void SetX(int x);
	void SetY(int y);
	void SetKind(int kind);
	void SetStrong(int strong);
	void SetHP(double health_point);
	void SetMP(double magic_point);
protected:
	int attack_range_x;
	int attack_range_y;
	double health_point_max;
	double magic_point_max;
	double health_point;
	double magic_point;
	double experience;
	int kind;
	int x;
	int y;
	int y_speed;
	int level;
	int strong;
	int direction;
	Skill running;
	Skill first_skill;
	Skill second_skill;
	Skill attack;
	Skill die;
};

class LittleMonster;

class Hero : public Character {
private:
public:
	Hero();
	void Show();
	void BeAttacked(LittleMonster mirror);
	void BeAttackedAnimation();
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