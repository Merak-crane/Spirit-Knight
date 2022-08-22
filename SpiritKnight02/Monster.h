#pragma once
#include "Character.h"
class LittleMonster : public Character {
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