// InheritancePolymorphismChallenge.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Character.h"
#include "Player.h"
#include "Enemy.h"

int main()
{
    /*
    Character character;
    Player player;
    Enemy enemy;

    character.Draw();
    player.Draw();
    enemy.Draw();
    */

    constexpr int numberOfCharacter = 20;
    constexpr int numberOfPlayers = 2;
    constexpr int numberOfEnemies = numberOfCharacter - numberOfPlayers;

    Character* pCharacterArray[numberOfCharacter];

    // Create Players
    for (int i = 0; i < numberOfPlayers; ++i)
    {
        pCharacterArray[i] = new Player();
    }

    // Create Enemies
    for (int i = 0; i < numberOfEnemies; ++i)
    {
        pCharacterArray[i+numberOfPlayers] = new Enemy();
    }

    // draw each of the players and enemies
    // when using pointers use -> instead of .
    for (int i = 0; i < numberOfCharacter; ++i)
    {
        pCharacterArray[i]->Draw();
    }

    // freeing up memory
    for (int i = 0; i < numberOfCharacter; ++i)
    {
        delete pCharacterArray[i];
        pCharacterArray[i] = nullptr;
    }
}

