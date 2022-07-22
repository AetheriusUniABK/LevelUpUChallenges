#include "Player.h"
#include "Character.h"

Player::Player()
{

}

Player::Player(std::string name, int health, int weapon, int armor)
	: Character(health, weapon, armor)
	, m_name(name)
{

}

Player::~Player()
{

}

void Player::Rest()
{
	m_health += 20;
}
