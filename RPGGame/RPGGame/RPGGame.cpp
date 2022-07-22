// RPGGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Character.h"
#include "Enemy.h"
#include "Player.h"

void PlayGame();
void Encounter(Player player, Enemy enemy);
void Round(Player player, Enemy enemy);

int main()
{
	PlayGame();
}

void PlayGame()
{
	int playerHP = 100;
	int enemyHP = 100;
	std::string playerName = "";
	
}

void Encounter(Player player, Enemy enemy)
{
	int numRounds = 5;

	for (int i = 0; i < numRounds; i++)
	{
		Round(player, enemy);
	}
}

void Round(Player player, Enemy enemy)
{

}
