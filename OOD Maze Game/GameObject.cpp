#include "GameObject.h"

char GameObject::GetSymbol()
{
    return symbol;
}

int GameObject::GetColour()
{
    return colour;
}

void GameObject::SetSymbol(char _symbol)
{
    symbol = _symbol;
}

void GameObject::SetColour(int _colour)
{
    colour = _colour;
}

cVector2 GameObject::GetPostion()
{
    return position;
}

void GameObject::SetPostion(cVector2 newPos)
{
    position = newPos;
}

