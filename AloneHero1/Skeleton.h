#pragma once
#include "Enemy.h"


class Skeleton : public Enemy
{
	public:
		Skeleton(double x, double y, double width, double height, double speed, int health, double strength) : Enemy(x, y, width, height, speed, health, strength) 
		{
			this->directory = "Enemies/Skeleton/";
		};
		~Skeleton() {};
		void Defense();
};

