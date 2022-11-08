#pragma once
#include "Enemy.h"

class Mushroom : public Enemy
{
	public:
		Mushroom(double x, double y, double speed, int health, double strength) : Enemy(x, y, speed, health, strength)
		{
			this->directory = "Enemies/Mushroom/";
			this->xBeginSprite = 59;
			this->yBeginSprite = 58;
			this->width = 29;
			this->widthOfHit = 40;
			this->height = 38;
			this->bufWidth = 122;
			this->countFramesOfMove = 8;
			this->countFramesOfIdle = 4;
			this->countFramesOfHit = 8;
			this->countFramesOfDamage = 4;
			this->countFramesOfDeath = 4;
			this->bufOfHit = 114;
			this->heightOfHit = 46;
			this->xBeginSpriteHit = 40;
			this->yBeginSpriteHit = 62;
		};
		~Mushroom() {};
		void Grab();
};