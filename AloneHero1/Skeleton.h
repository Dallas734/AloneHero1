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
			this->countFrames[RUN] = 4;
			this->countFrames[IDLE] = 4;
			this->countFrames[HIT] = 8;
			this->countFrames[DAMAGE] = 4;
			this->countFrames[DEATH] = 4;
			this->bufOfHit = 40;
			this->heightOfHit = 61;
			this->xBeginSpriteHit = 49;
			this->yBeginSpriteHit = 42;
		};
		~Skeleton() {};
		void Defense();
};

