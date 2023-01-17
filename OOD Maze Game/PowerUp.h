#pragma once
#include "Collectable.h"

class PowerUp : public Collectable
{
private:
	double duration{};

public:
	PowerUp();
	PowerUp(int _colour);
	double GetDuration();
};

