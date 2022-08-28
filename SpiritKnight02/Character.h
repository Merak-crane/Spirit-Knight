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
	int image_width;
	int image_height;
	int real_body_width;
	int real_body_height;
	double size_factor;
	int attacknum;
	int count_left;
	int count_right;
	int count_top;
	int count_attack;
	int x_speed_right;
	int x_speed_left;
	int real_body_x;
	int real_body_y;
	int y_speed;
	QPixmap photo;
	Character();
	void WalkLeft();
	void WalkRight();
	void WalkTop();
	void WalkDown();
	void Attack();
	void Attack2();
	void Die();
	void PathCreator(QString a, QString b, int c, int count, vector <QString> &picture);
	QString FrameAnimation(vector <QString> picture, int& count);
	int GetX();
	int GetY();
	int GetStrong();
	int GetKind();
	bool GetLay();
	int GetDirection();
	double GetHP();
	double GetMP();
	double GetHPMAX();
	double GetMPMAX();
	void SetDirection(int direction);
	void SetX(int x);
	void SetY(int y);
	void SetKind(int kind);
	void SetLay(bool lay);
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
	bool lay = 0;
	int x;
	int y;
	int level;
	int strong;
	int direction;
	Skill running;
	Skill first_skill;
	Skill second_skill;
	Skill attack;
	Skill be_attack;
	Skill die;
};

class LittleMonster;

class Hero : public Character {
private:
public:
	Hero();
	void Show();
	void BeAttacked(LittleMonster* monster[], bool monster_survive[]);
	void BeAttackedAnimation();
};

class LittleMonster: public Character {
public:
	LittleMonster();
	void Move(Hero player);
	void Attack();
	void BeAttacked(Hero hero);
	void BeAttackedAnimation();
};

class MiddleMonster : public Character {
private:
	Skill attack_two;
public:
	MiddleMonster();
	void Move(Hero player);
	void Attack();
	void BeAttacked(Hero hero);
	void BeAttackedAnimation();
	void AttackAnimation();
};

class UltraMonster : public Character {
public:
private:
	Skill attack_two;
public:
	UltraMonster();
	void Move(Hero player);
	void Attack();
	void Attack2();
	void BeAttacked(Hero hero);
	void BeAttackedAnimation();
	void AttackAnimation();
};