#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(int _colour, double _speed)
{
	symbol = char(4);
	colour = _colour;

	damage = 1;

	speed = _speed;

	timer = clock();
	canMove = false;
}

int Enemy::GetDamage()
{
	return damage;
}

bool Enemy::CanMove()
{
	if (canMove == false)
	{
		if (timer + speed < clock())
		{
			canMove = true;
			timer = clock();
		}
	}
	return  canMove;
}

void Enemy::ToggleMove(bool status)
{
	canMove = status;
}

