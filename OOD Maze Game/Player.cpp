#include "Player.h"

#include <conio.h>

Player::Player()
{
}

Player::Player(int _colour)
{
	symbol = char(2);

	powerUpColour = 13;
	colour = _colour;

	maxHealth = health = 3;

	powerUpTimer = clock();
	powerUpDuration = 5000;
}


void Player::AddScore(int _amount)
{
    score += _amount;
}

void Player::Heal(int healthAmount)
{
	health += healthAmount;
	if (health > maxHealth) health = maxHealth;
}

void Player::TakeDamage(int damage)
{
	health -= damage;
	if (health < 0) health = 0;
}

int Player::GetHealth()
{
	return health;
}

bool Player::IsDead()
{
	return health == 0;
}

void Player::ActivatePowerUp(double _powerUpDuration)
{
	powerUpDuration = _powerUpDuration;
	powerUpTimer = clock();
	powerUp = true;
}

bool Player::PowerUpActive()
{  
	return powerUp;
}

void Player::ManagePowerUp()
{
	if (powerUp)
	{
		if (powerUpTimer + powerUpDuration < clock())
		{
			powerUp = false;
		}
	}
}

void Player::TurnOffPowerUp()
{
	powerUp = false;
}

int Player::GetPowerUpDuration()
{
	return (int)((powerUpTimer + powerUpDuration) - clock()) / CLOCKS_PER_SEC;
}

int Player::GetColour()
{
	if (powerUp) return  powerUpColour;
	else return  colour;
}

int Player::GetScore()
{
	return score;
}

void Player::ResetStats()
{
	maxHealth = health = 3;
	powerUp = false;
}
