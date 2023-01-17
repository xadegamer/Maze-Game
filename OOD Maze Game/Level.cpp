#include "Level.h"

#include <stdlib.h> 
#include <conio.h>
#include <time.h>  

Level::Level()
{
	levelNum = 1;
	maxEnemy = 3;
	maxCoin = 3;
	maxHealthkit = 3;
	maxPowerUp = 3;

	levelFailed = false;

	srand(time(NULL));
}

Level::~Level()
{
	Refresh();
}

void Level::SelectGameMode()
{
	levelTimer = clock();
	levelDuration = 120000;

	//Changes Gamemode
	switch (gameMode)
	{
	case Level::EscapeMode:
		gameMode = GameMode::CollectorMode;
		break;
	case Level::CollectorMode:
		gameMode = GameMode::EliminationMode;
		break;
	case Level::EliminationMode:
		gameMode = GameMode::EscapeMode;
		break;
	}
}

void Level::Load()
{
	SelectGameMode();

	maze.create(-1, 25, 25);
	maze.print();

	SpawnCollectables();
	SpawnPowerUps(maxPowerUp);
	SpawnEnemies();

	if(gameMode == GameMode::EscapeMode) SpawnDoor();

	SpawnPlayer();

	DisplayUI();
}

void Level::LevelComplected()
{
	levelNum++;
	while (!enemies.empty()) delete enemies.back(), enemies.pop_back();
	while (!collectables.empty()) delete collectables.back(), collectables.pop_back();
	Load();
}

bool Level::LevelFailed()
{
	return levelFailed;
}

void Level::Refresh()
{
	levelNum = 1;
	levelFailed = false;

	delete player;
	player = nullptr;
	while (!enemies.empty()) delete enemies.back(), enemies.pop_back();
	while (!collectables.empty()) delete collectables.back(), collectables.pop_back();
}

void Level::SpawnPlayer()
{
	if (player == nullptr) player = new Player(Bright_Blue);

	player->TurnOffPowerUp();

	player->SetPostion(maze.GetStartPosition());
	maze.PrintInPosition(player);
}

void Level::RespawnPlayer()
{
	maze.RemoveFromPosition(player->GetPostion());
	SpawnPlayer();
}

Player* Level::GetPlayer()
{
	return player;
}

void Level::SpawnCollectables()
{
	for (int i = 0; i < maxCoin; i++)
	{
		Coin* coin1 = new Coin(50,Bright_Yellow);

		coin1->SetPostion(maze.GetRandomEmptyPosition());
		maze.PrintInPosition(coin1);
		collectables.push_back(coin1);
	}

	for (int i = 0; i < maxHealthkit; i++)
	{
		HealthKit* healthkit = new HealthKit(1, Bright_Green);

		healthkit->SetPostion(maze.GetRandomEmptyPosition());
		maze.PrintInPosition(healthkit);
		collectables.push_back(healthkit);
	}
}

void Level::SpawnPowerUps(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		PowerUp* powerUp = new PowerUp(Bright_Magenta);

		powerUp->SetPostion(maze.GetRandomEmptyPosition());
		maze.PrintInPosition(powerUp);
		collectables.push_back(powerUp);
	}
}

void Level::SpawnEnemies()
{
	for (int i = 0; i < maxEnemy; i++)
	{
		//Give enemies random speed
		int randomNum = rand() % 500 + 500;

		Enemy* enemy1 = new Enemy (Bright_Red, randomNum);
		enemy1->SetPostion(maze.GetRandomEndPointPosition());
		maze.PrintInPosition(enemy1);
		enemies.push_back(enemy1);
	}
}

void Level::SpawnDoor()
{
	exitDoor.SetPostion(maze.GetExitPosition());
	exitDoor.SetSymbol(maze.getExitChar());
	exitDoor.SetColour(Bright_Cyan);
	maze.PrintInPosition(&exitDoor);
}


void Level::EnemiesPatrol()
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->CanMove())
		{
			//Get a random number between 0 and 3
			int input = rand() % 4;

			switch (input)
			{
			case 0:
				if(HandleMovement(Right, *enemies[i])) enemies[i]->ToggleMove(false);
				else enemies[i]->ToggleMove(true);
				break;
			case 1:
				if (HandleMovement(Left, *enemies[i])) enemies[i]->ToggleMove(false);
				else enemies[i]->ToggleMove(true);
				break;
			case 2:
				if (HandleMovement(UP, *enemies[i])) enemies[i]->ToggleMove(false);
				else enemies[i]->ToggleMove(true);
				break;
			case 3:
				if (HandleMovement(Down, *enemies[i])) enemies[i]->ToggleMove(false);
				else enemies[i]->ToggleMove(true);
				break;
			default:
				break;
			}
		}
	}
}

bool Level::AllCoinCollected()
{
	for (int i = 0; i < collectables.size(); i++)
	{
		Coin* coin = dynamic_cast<Coin*>(collectables[i]);
		if (coin != nullptr) return false;
	} return true;
}

bool Level::CheckCollison(Character& character, GameObject* collideObjectP)
{
	if (collideObjectP == nullptr) return true;
	
	Player* player = dynamic_cast<Player*>(&character);

	//Handles player collision to objects
	if (player != nullptr)
	{
		//Handles player collision with exitPoint
		if (collideObjectP->GetSymbol() == maze.getExitChar())
		{
			LevelComplected();
			return false;
		}

		//Handles player collision with collectabables
		Collectable* collectable = dynamic_cast<Collectable*>(collideObjectP);
		if (collectable != nullptr)
		{
			Coin* coin = dynamic_cast<Coin*>(collideObjectP);
			if (coin != nullptr)
			{
				player->AddScore(coin->GetValue());
				UpdateScoreUI();
			}
			else
			{
				HealthKit* healthkit = dynamic_cast<HealthKit*>(collideObjectP);
				if (healthkit != nullptr) player->Heal(healthkit->GetValue());
				else
				{
					PowerUp* powerUp = dynamic_cast<PowerUp*>(collideObjectP);
					if (powerUp != nullptr)
					{
						player->ActivatePowerUp(powerUp->GetDuration());
						SpawnPowerUps(1);
					}
				}
			}

			delete collectable;
			collectables.erase(std::remove(collectables.begin(), collectables.end(), collectable), collectables.end());
			collectable = nullptr;

			//Checking game mode contidion
			if (gameMode == GameMode::CollectorMode && AllCoinCollected())
			{
				LevelComplected();
				return false;
			}
			else return true;
		}

		//Handles player collision with enemy
		Enemy* enemy = dynamic_cast<Enemy*>(collideObjectP);
		if (enemy != nullptr)
		{
			if (player->PowerUpActive())
			{
				player->AddScore(100);
				UpdateScoreUI();

				delete enemy;
				enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
				enemy = nullptr;

				if (gameMode == GameMode::EliminationMode && enemies.size() == 0)
				{
					LevelComplected();
					return false;
				}

				return true;
			}
			else
			{
				player->TakeDamage(enemy->GetDamage());

				UpdateHealthUI();

				if (player->IsDead())
				{
					levelFailed = true;
					return false;
				}

				RespawnPlayer();
			}
			return false;
		}

		return true;
	}

	//Handles enemies collision to objects
	Enemy* enemy = dynamic_cast<Enemy*>(&character);

	if (enemy != nullptr)
	{
		Player* player = dynamic_cast<Player*>(collideObjectP);
		if (player != nullptr)
		{
			if (!player->PowerUpActive())
			{
				player->TakeDamage(enemy->GetDamage());

				UpdateHealthUI();

				if (player->IsDead())
				{
					levelFailed = true;
					return false;
				}
				RespawnPlayer();
				return true;
			}

			return false;
		}

		Enemy* enemy = dynamic_cast<Enemy*>(collideObjectP);
		if (enemy != nullptr) return false;

		Collectable* collectable = dynamic_cast<Collectable*>(collideObjectP);
		if (collectable != nullptr)	return false;

		if (collideObjectP->GetSymbol() == maze.getExitChar()) return false;
	}

	return true;
}

//Handles player and enemies movement
bool Level::HandleMovement(int input, Character& character)
{
	switch (input)
	{
	case UP:

		if (maze.GetUpCell(character.GetPostion()).display == maze.getWallChar()) return false;

		if (CheckCollison(character, maze.GetUpCell(character.GetPostion()).objectInCell))
		{
			maze.RemoveFromPosition(character.GetPostion());

			character.MoveUp();

			maze.PrintInPosition(&character);

			return true;
		}

		return false;

		break;
	case Down:

		if (maze.GetDownCell(character.GetPostion()).display == maze.getWallChar()) return false;

		if (CheckCollison(character, maze.GetDownCell(character.GetPostion()).objectInCell))
		{
			maze.RemoveFromPosition(character.GetPostion());

			character.MoveDown();

			maze.PrintInPosition(&character);

			return true;
		}

		return false;

		break;
	case Right:

		if (maze.GetRightCell(character.GetPostion()).display == maze.getWallChar()) return false;

		if (CheckCollison(character, maze.GetRightCell(character.GetPostion()).objectInCell))
		{
			maze.RemoveFromPosition(character.GetPostion());

			character.MoveRight();

			maze.PrintInPosition(&character);

			return true;
		}

		return false;

		break;
	case Left:

		if (maze.GetLeftCell(character.GetPostion()).display == maze.getWallChar()) return false;

		if (CheckCollison(character, maze.GetLeftCell(character.GetPostion()).objectInCell))
		{
			maze.RemoveFromPosition(character.GetPostion());

			character.MoveLeft();

			maze.PrintInPosition(&character);

			return true;
		}

		return false;

		break;
	case Quit:
		levelFailed = true;
		break;
	default:
		break;
	}
}

void Level::ManageLevelTime()
{
	if (levelTimer + levelDuration < clock())
	{
		levelFailed = true;
	}
	else
	{
		GoToPos(30, 10);
		ChangeTextColour(Bright_Red);
		std::cout << "Time remaining : " <<(int)( (levelTimer + levelDuration) - clock())/ CLOCKS_PER_SEC << "s ";
		ChangeTextColour(White);

		player->ManagePowerUp();

		if (player->PowerUpActive())
		{
			GoToPos(30, 13);
			std::cout << "Power Up : " << player->GetPowerUpDuration() << "s ";
		}
		else
		{
			GoToPos(30, 13);
			std::cout << "Power Up : Off ";
		}
	}
}

void Level::GoToPos(short a, short b)
{
	COORD pos = { a,b };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Level::DisplayUI()
{
	GoToPos(30, 2);
	ChangeTextColour(Bright_Blue);
	std::cout << "Player: " << char(2);

	GoToPos(30, 3);
	ChangeTextColour(Bright_Red);
	std::cout << "Enemies: " << char(4);

	GoToPos(30, 4);
	ChangeTextColour(Bright_Yellow);
	std::cout << "Coins: " << char(17);

	GoToPos(30, 5);
	ChangeTextColour(Bright_Magenta);
	std::cout << "PowerUps: " << char(6);

	GoToPos(30, 6);
	ChangeTextColour(Bright_Green);
	std::cout << "Health Kits: " << char(3);

	GoToPos(30, 7);
	ChangeTextColour(Bright_Cyan);
	std::cout << "Exit: " << maze.getExitChar();

	GoToPos(30, 20);
	ChangeTextColour(Red);
	std::cout << "Press ESC to Quit";

	ChangeTextColour(White);


	switch (gameMode)
	{
	case Level::EscapeMode:
		GoToPos(30, 9);
		std::cout << "Level: " << levelNum << " - Find the Exit";
		break;
	case Level::CollectorMode:
		GoToPos(30, 9);
		std::cout << "Level: " << levelNum << " - Collect all the coins";
		break;
	case Level::EliminationMode:
		GoToPos(30, 9);
		std::cout << "Level: " << levelNum << " - Eliminate all enemies";
		break;
	default:
		break;
	}

	UpdateScoreUI();
	UpdateHealthUI();
}

void Level::UpdateScoreUI()
{
	GoToPos(30, 12);
	std::cout << "Score: " << player->GetScore();
}

void Level::UpdateHealthUI()
{
	GoToPos(30, 11);
	std::cout << "Health: " << player->GetHealth();
}

void Level::ChangeTextColour(int newColour)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hOut, &info);
	SetConsoleTextAttribute(hOut, newColour);
}
