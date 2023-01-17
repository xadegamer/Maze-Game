#include "Character.h"

#include <conio.h>

Character::Character()
{}

void Character::MoveUp()
{
    position.x--;
}

void Character::MoveDown()
{
    position.x++;
}

void Character::MoveLeft()
{
    position.y--;
}

void Character::MoveRight()
{
    position.y++;
}

