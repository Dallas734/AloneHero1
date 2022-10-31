#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "levelfwd.h"// Forward declaration класса агрегата.

const double BUF_OF_PLAYER_HIT = 47;
//class Level;
class Player : public Entity
{
	private:
		int countFramesOfJump;
	public:
		Player(double x, double y) : Entity(x, y, 0.1, 100, 100)
		{
			this->directory = "Player/";
			this->state = FALL;
			this->width = 42;
			this->height = 56;
			this->bufWidth = 118;
			this->bufOfHit = 47;
			this->xBeginSprite = 56;
			this->yBeginSprite = 44;
			this->widthOfHit = 111;
			this->countFramesOfMove = 8;
			this->countFramesOfIdle = 8;
			this->countFramesOfHit = 4;
			this->countFramesOfDamage = 4;
			this->countFramesOfJump = 2;
			this->countFramesOfIdle = 8;

		};
		~Player() {};
		void HelthUP(int regenerationUnits);
		void StrengthUP();
		void SpeedUp(double improveUnits);
		void Update(float time, RenderWindow& window, Level* level) override;
	private:
		States Jump(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level);
		States Fall(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level) override;

};

