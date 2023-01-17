#pragma once
#include "Level.h"

#include <fstream>


class Game
{
private:
	int highscore{};
	int lastScore{};

	Level level;

public:

	Game();

	void LoadScore();

	void SaveScore(int score);

	void StartMenu();

	void InstructionMenu();

	void Update();

	void GameOver();
};

