#pragma once
#include "GameObject.h"

class Collectable: public GameObject
{
protected:
	int value;
public:
	int GetValue();
};

