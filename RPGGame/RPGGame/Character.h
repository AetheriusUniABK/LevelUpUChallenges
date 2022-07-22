#pragma once
class Character
{
public:

	int m_health = 0;
	int m_weapon = 0;
	int m_armor = 0;

	Character();
	Character(int health, int weapon, int armor);
	~Character();
};

