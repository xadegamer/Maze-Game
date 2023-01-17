#include "Coin.h"

Coin::Coin()
{
}

Coin::Coin(int _amount, int _colour)
{
	symbol = char(17);
	colour = _colour;
	value = _amount;
}
