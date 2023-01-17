#pragma once

#include<Windows.h>
#include<iostream>
#include<stdio.h>
#include<time.h>
#include<vector>
#include<chrono>
#include<string>

using std::string;
using std::vector;

void Cls()
{
	char fill = ' ';
	COORD tl = { 0,0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, fill, cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
}

int DisplayMenu(string title, vector<string> options)
{
	int playerInput = 0;

	do
	{
		std::cout << title << std::endl;

		for (size_t i = 0; i < options.size(); i++)
		{
			std::cout << std::to_string(i + 1) + ":" + options[i] << std::endl;
		}

		std::cin >> playerInput;
		Cls();
		std::cin.clear();
		std::cin.ignore(256, '\n');

		if (playerInput == 0 || playerInput > options.size())
			std::cout << "You entered wrong input" << std::endl;

	} while (!std::cin.good() || playerInput == 0 || playerInput > options.size());

	return playerInput;
}


