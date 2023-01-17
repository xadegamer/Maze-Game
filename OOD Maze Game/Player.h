#pragma once
#include "Character.h"

#include <windows.h>
#include <time.h>  

class Player : public Character
{
private:
	int maxHealth{ 0 };
	int health{ 0 };

	int score{ 0 };

	bool powerUp = { false};

	int powerUpColour{0};
	clock_t powerUpTimer {clock()};
	double powerUpDuration{ 0 };

public:
	Player();
	Player(int _colour);

	void AddScore(int _amount);

	int GetHealth();
	void Heal(int healthAmount);
	void TakeDamage(int damage);
	bool IsDead();

	void ActivatePowerUp(double _powerUpDuration);
	bool PowerUpActive();
	void ManagePowerUp();
	void TurnOffPowerUp();
	int GetPowerUpDuration();

	int GetColour();
	int GetScore();

	void ResetStats();
};

