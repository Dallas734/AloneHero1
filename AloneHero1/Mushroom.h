#pragma once
#include "Enemy.h"

class Mushroom : public Enemy
{
	Mushroom(double x, double y, double width, double height, double speed, int health, double strength) : Enemy(x, y, width, height, speed, health, strength)
	{
		this->directory = "Enemies/Mushroom/";
	};
	~Mushroom() {};

};

