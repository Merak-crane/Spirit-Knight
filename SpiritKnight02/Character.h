#pragma once
#include <vector>
#include <string>
#include <QPainter>
using namespace std;

class Picture {
public:
	//void Animation(vector <const char*> motion);
public:
	vector <const char*> advance;//ǰ��
	vector <const char*> draw_back;//����
	vector <const char*> attack_right;//��ͨ�ҹ���
	vector <const char*> attack_left;//��ͨ�󹥻�
	vector <const char*> skill_one;//����1
	const char* stand_right;
	const char* stand_left;
};//�洢ÿ��������������ͼƬ�����·��

class Skill {
public:
	vector<const char*> skill_picture;
private:
	double range_x;
	double range_y;
	int count;
};

class Character {
public:
	int attack;
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
	int GetX();
	int GetY();
	int GetKind();
	int GetDirection();
	void SetDirection(int direction);
	void SetX(int x);
	void SetY(int y);
	void SetKind(int kind);
	const char* GetStandRight();
	const char* GetStandLeft();
protected:
	double attack_range;
	double health_point;
	double magic_point;
	double experience;
	int kind;
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