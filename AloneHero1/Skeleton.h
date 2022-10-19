#pragma once
#include "Enemy.h"


class Skeleton : public Enemy
{
	public:
		Skeleton(double x, double y, double speed, int health, double strength) : Enemy(x, y, speed, health, strength) 
		{
			this->directory = "Enemies/Skeleton/";
			this->xBeginSprite = 57;
			this->yBeginSprite = 49;
			this->width = 49;
			this->height = 52;
			this->bufWidth = 102;
			this->countFramesOfMove = 4;
			this->countFramesOfIdle = 4;
		};
		~Skeleton() {};
		void Defense();
};

