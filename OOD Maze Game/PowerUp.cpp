#include "PowerUp.h"

PowerUp::PowerUp()
{
}

PowerUp::PowerUp(int _colour)
{
	symbol = char(6);
	colour = _colour;
	duration = 12000;
}

double PowerUp::GetDuration()
{
	return duration;
}
