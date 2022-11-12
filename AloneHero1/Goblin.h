#pragma once
#include "Enemy.h"

class Goblin : public Enemy
{
	public:
		Goblin(double x, double y, double speed, double health, double strength) : Enemy(x, y, speed, health, strength)
		{
			this->directory = "Enemies/Goblin/";
			this->xBeginSprite = 53;
			this->yBeginSprite = 59;
			this->width = 45;
			this->widthOfHit = 50;
			this->height = 43;
			this->bufWidth = 105;
			this->countFrames[RUN] = 8;
			this->countFrames[IDLE] = 4;
			this->countFrames[HIT] = 8;
			this->countFrames[DAMAGE] = 4;
			this->countFrames[DEATH] = 4;
			this->bufOfHit = 72;
			this->heightOfHit = 53;
			this->xBeginSpriteHit = 55;
			this->yBeginSpriteHit = 52;
		};
		~Goblin() {};
		void Poision();
};

