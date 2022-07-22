#pragma once
#include "Character.h"

class Enemy : public Character
{
	// enemies have health, weapon, armor
	// possible to not have weapon or armor

public:

	Enemy();
	Enemy(int health, int weapon, int armor);
	~Enemy();
};

