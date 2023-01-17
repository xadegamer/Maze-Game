#pragma once
#include "GameObject.h"

class Character : public GameObject
{

public:
	Character();

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
};

