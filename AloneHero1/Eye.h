#pragma once
#include "Enemy.h"

class Eye : public Enemy
{
	Eye(double x, double y, double speed, int health, double strength) : Enemy(x, y, speed, health, strength) 
	{
		this->directory = "Enemies/Eye/";
	};
	~Eye() {};
	void Shoot();
};

