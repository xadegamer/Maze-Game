#include "Game.h"

#include "UI Utility.h"

#include <conio.h>

Game::Game()
{
	StartMenu();
}

void Game::LoadScore()
{
	std::ifstream input;
	input.open("SaveData.txt");
	if (!input.bad())
	{
		std::string score;
		std::getline(input, score);
		input.close();

		highscore = stoi(score);
	}
}

void Game::SaveScore(int score)
{
	std::ofstream  output;
	output.open("SaveData.txt");	
	if (!output.bad())
	{
		output << score << std::endl;
		output.close();
	}
}

void Game::StartMenu()
{
	LoadScore();

	std::cout << "Maze Arena" << std::endl;

	std::cout << "High Score: " << highscore << std::endl;

	switch (DisplayMenu(" ", { "Start Game","Instruction", "Quit" }))
	{
	case 1:
		level.Load(); 
		Update();
		break;
	case 2:
		InstructionMenu();
		break;
	case 3:
		exit(0);
		break;
	default:
		break;
	}
}

void Game::InstructionMenu()
{
	std::cout << "Instruction" << std::endl;
	std::cout << "--------------------------" << std::endl;
	std::cout << "Advance throught the random mazes in 3 Game modes." << std::endl;
	std::cout << "Collect power ups to kill enemies (10 seconds)." << std::endl;
	std::cout << "Get the best score." << std::endl;
	std::cout << "Best of luck." << std::endl;

	switch (DisplayMenu("", { "Back", "Quit" }))
	{
	case 1:
		StartMenu();
		break;
	case 2:
		exit(0);
		break;
	default:
		break;
	}
}

void Game::Update()
{
	while (!level.LevelFailed ())
	{
		//Only checks if the player presses an input
		if (_kbhit())
		{
			level.HandleMovement(_getch(), *level.GetPlayer());
		}

		level.ManageLevelTime();

		level.EnemiesPatrol();
	}

	GameOver();
}

void Game::GameOver()
{
	lastScore = level.GetPlayer()->GetScore();
	if(lastScore > highscore) SaveScore(lastScore);
	level.Refresh();

	Cls();

	std::cout << "Game Over" << std::endl;
	std::cout << "Score: " << lastScore << std::endl;

	switch (DisplayMenu("", { "MainMenu", "Quit" }))
	{
	case 1:
		StartMenu();
		break;
	case 2:
		exit(0);
		break;
	default:
		break;
	}
}
