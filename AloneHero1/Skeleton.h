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
			this->widthOfHit = 111;
			this->height = 54;
			this->bufWidth = 102;
			this->countFramesOfMove = 4;
			this->countFramesOfIdle = 4;
			this->countFramesOfHit = 8;
			this->countFramesOfDamage = 4;
			this->countFramesOfDeath = 4;
			this->bufOfHit = 40;
			this->heightOfHit = 61;
			this->xBeginSpriteHit = 49;
			this->yBeginSpriteHit = 42;
		};
		~Skeleton() {};
		void Defense();
};

