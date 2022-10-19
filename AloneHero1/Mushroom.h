#pragma once
#include "Enemy.h"

class Mushroom : public Enemy
{
	Mushroom(double x, double y, double speed, int health, double strength) : Enemy(x, y, speed, health, strength)
	{
		this->directory = "Enemies/Mushroom/";
	};
	~Mushroom() {};

};

