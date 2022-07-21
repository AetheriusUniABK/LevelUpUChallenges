#pragma once

#include <iostream>
#include "Character.h"

// inheritance = "is a" relationship
// aka do the Player : Character thing

class Player : public Character
{
	bool m_HasKey;

public:

	Player()
	{

	}

	Player(float health, int x, int y)
		: Character(health, x, y)
		, m_HasKey(false)
	{

	}

	~Player()
	{

	}

	// override ignores the Draw defined in Character
	void Draw() override
	{
		std::cout << "@" << std::endl;
	}

	void UseHealth(float health)
	{
		m_Health += health;
		if (!m_IsAlive)
		{
			m_IsAlive = true;
		}
	}

	void PickupKey()
	{
		m_HasKey = true;
	}
};

