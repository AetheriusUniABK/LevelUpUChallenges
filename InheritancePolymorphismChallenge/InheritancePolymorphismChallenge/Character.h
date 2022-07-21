#pragma once

#include "Point.h"
#include <iostream>

// composition = "has a" relationship
// aka use a pointer to a thing that something has

class Character
{
protected:
	float m_Health;
	bool m_IsAlive;
	Point* m_pPoint;

public:

	Character()
	{

	}

	Character(float health, int x, int y)
		: m_pPoint(new Point(x, y))
		, m_Health(health)
		, m_IsAlive(false)
	{

	}

	~Character()
	{
		delete m_pPoint;
		m_pPoint = nullptr;
	}

	void Move(int x, int y)
	{
		m_pPoint->x += x;
		m_pPoint->y += y;
	}

	void TakeDamage(float damage)
	{
		if (m_IsAlive)
		{
			m_Health -= damage;
			if (m_Health <= 0)
			{
				m_Health = 0;
				m_IsAlive = false;
			}
		}
	}

	// virtual means this is like the default action when doing Draw
	/*virtual void Draw()
	{
		std::cout << "I'm not sure how to draw myself" << std::endl;
	}*/

	// opting to make Draw a pure virtual AKA must be overriden
	virtual void Draw() = 0;
};

