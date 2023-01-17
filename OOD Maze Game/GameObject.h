#pragma once
#include<iostream>

#include "cVector2.h"

class GameObject
{
protected:
	char symbol{};
	int colour{};
	cVector2 position;

public:

	char GetSymbol();
	virtual int GetColour();

	void SetSymbol(char _symbol);
	void SetColour(int _colour);

	cVector2 GetPostion();
	void SetPostion(cVector2 newPos);
};
