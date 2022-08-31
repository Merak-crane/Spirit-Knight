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
	int life = 2;
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
	int GetLevel();
	double GetHP();
	double GetMP();
	double GetHPMAX();
	double GetMPMAX();
	void SetDirection(int direction);
	void SetLevel(int level);
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
class Hero;
class Bullet
{
public:
	QPixmap photo;
	QRect attack_range;
	int image_width;
	int image_height;
	int real_body_width;
	int real_body_height;
	int real_body_x;
	int real_body_y;
	double size_factor;
protected:
	int x;
	int y;
	int direction;
	int attack_range_x;
	int attack_range_y;
	int x_speed;
};
class BulletOne : public Bullet{
private:
public:
	QPixmap photo;
	BulletOne(int x, int y, int direction);
	void Move();
	void Disappear();
};
class SorcererOne : public Character {
private:
public:
	vector<BulletOne*> bullet_collector;
	SorcererOne();
	void Move(Hero player);
	void Attack();
	void BeAttacked(Hero hero);
	void BeAttackedAnimation();
};
class Hero : public Character {
private:
	int exp;
public:
	Hero();
	void Show();
	void BeAttacked(vector<LittleMonster*> monster, vector<bool> monster_survive);
	void BeAttackedAnimation();
	void SetExp(int exp);
	int GetExp();
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
	void Attack2Animation();
};