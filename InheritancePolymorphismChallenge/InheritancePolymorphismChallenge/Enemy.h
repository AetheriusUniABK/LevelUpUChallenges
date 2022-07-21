#pragma once

#include <iostream>
#include "Character.h"

class Enemy : public Character
{
	float m_Strength;

public:

	Enemy()
	{

	}

	Enemy(float health, int x, int y, float strength)
		: Character(health, x, y)
		, m_Strength(strength)
	{

	}

	~Enemy()
	{

	}

	void Draw() override
	{
		std::cout << "*" << std::endl;
	}
};

