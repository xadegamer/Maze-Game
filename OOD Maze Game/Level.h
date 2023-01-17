#pragma once
#include<vector>

#include "GameObject.h"
#include "cMaze.h"
#include "Player.h"
#include "Enemy.h"
#include "Collectable.h"
#include "Coin.h"
#include "HealthKit.h"
#include "PowerUp.h"

class Level
{
    enum  GameMode {EscapeMode = 0, CollectorMode = 1, EliminationMode = 2};
    enum Direction { UP = 72, Down = 80, Right = 77, Left = 75, Quit = 27};

    enum Colors
    {
        Black = 0,
        Blue = 1,
        Green = 2,
        Cyan = 3,
        Red = 4,
        Magenta = 5,
        Yellow = 6,
        White = 7,
        Gray = 8,
        Bright_Blue = 9,
        Bright_Green = 10,
        Bright_Cyan = 11,
        Bright_Red = 12,
        Bright_Magenta = 13,
        Bright_Yellow = 14,
        Bright_White = 15
    };

protected:

    GameMode gameMode;

    int levelNum{ 0 };

    clock_t levelTimer{ clock() };
    double levelDuration{ 0 };

    bool levelFailed{};

	int maxEnemy { 0 };
	int maxCoin { 0 };
    int maxHealthkit{ 0 };
    int maxPowerUp{ 0 };

    cMaze maze;
    GameObject exitDoor;

	std::vector<Enemy*> enemies;
	std::vector<Collectable*> collectables;
	Player* player = nullptr;
public:



	Level();
	~Level();

    void SelectGameMode();

	void Load();

    void LevelComplected();

    bool LevelFailed();

    void Refresh();

	void SpawnPlayer();
    void RespawnPlayer();
    Player* GetPlayer();

	void SpawnCollectables();
    void SpawnPowerUps(int amount);
	void SpawnEnemies();
	void SpawnDoor();

	void EnemiesPatrol();

    bool AllCoinCollected();

    bool CheckCollison(Character& character, GameObject* collideObject);
    bool HandleMovement(int input, Character& character);

    void ManageLevelTime();

    void GoToPos(short a, short b);

    void DisplayUI();

    void UpdateScoreUI();
    void UpdateHealthUI();

    void ChangeTextColour(int newColour);
};

