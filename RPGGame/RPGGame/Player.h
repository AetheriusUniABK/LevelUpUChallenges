#pragma once
#include "Character.h"
#include <iostream>

class Player : public Character
{
	// players have name, health, weapon, armor
	// health 100
	// weapons 1 sword 2 axe
	// armor 1 light 2 medium 3 heavy

public:

	// Member Variables
	//int m_health;
	int m_weapon;
	int m_armor;
	std::string m_name;

	Player();
	Player(std::string name, int health, int weapon, int armor);
	~Player();

	// Member Functions
	void Rest();

};

