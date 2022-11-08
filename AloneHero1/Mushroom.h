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
			this->countFrames[RUN] = 8;
			this->countFrames[IDLE] = 4;
			this->countFrames[HIT] = 8;
			this->countFrames[DAMAGE] = 4;
			this->countFrames[DEATH] = 4;
			this->bufOfHit = 114;
			this->heightOfHit = 46;
			this->xBeginSpriteHit = 40;
			this->yBeginSpriteHit = 62;
		};
		~Mushroom() {};
		void Grab();
};