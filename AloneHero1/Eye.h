#pragma once
#include "Enemy.h"

class Eye : public Enemy
{
	Eye(double x, double y, double width, double height, double speed, int health, double strength) : Enemy(x, y, width, height, speed, health, strength) 
	{
		this->directory = "Enemies/Eye/";
	};
	~Eye() {};
	void Shoot();
};

