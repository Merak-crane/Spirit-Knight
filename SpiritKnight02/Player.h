#pragma once
#include <QString>
class Player
{
public:
	Player(QString username, QString email, QString power, int level) :username(username),
		email(email), power(power), level(level) {};
	Player();
	~Player();
	QString GetUsername();
	int GetLevel();
	int GetHP();
	int GetMP();
	int GetEXP();

private:
	QString username;
	QString email;
	QString power;
	int level;
	int hp;
	int mp;
	int exp;
};
