#include "Enemy.h"
#include "Character.h"

Enemy::Enemy()
{

}

Enemy::Enemy(int health, int weapon, int armor)
	: Character(health, weapon, armor)
{

}

Enemy::~Enemy()
{

}