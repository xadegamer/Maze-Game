#pragma once

#include "Character.h"

#include <windows.h>
#include <time.h>  

class Enemy : public Character
{
	clock_t timer{ clock() };
	double speed{ 0 };
	int damage {0};

	bool canMove {false};

public:
	Enemy();
	Enemy(int _colour, double speed);

	int GetDamage();
	bool CanMove();
	void ToggleMove(bool status);
};

