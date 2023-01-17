#pragma once
#include "Collectable.h"

class Coin : public Collectable
{
public:
	Coin();
	Coin(int _amount, int _colour);
};

