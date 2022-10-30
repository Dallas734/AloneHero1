#pragma once
#include "Entity.h"
#include "levelfwd.h"

class Enemy : public Entity
{
	protected:
		int countFramesOfMove;
		int countFramesOfHit;
		int countFramesOfIdle;
		double xBeginSprite;
		double yBeginSprite;
		double xBeginSpriteHit;
		double yBeginSpriteHit;
		double bufOfHit;
		double widthOfHit;
		double heightOfHit;

	public:
		Enemy(double x, double y, double speed, int health, double strength) : Entity(x, y, speed, health, strength)
		{
			this->directory = "Enemies/";
			this->state = FALL;
			direction = RIGHT;
		};
		~Enemy() {};
		void Update(float time, RenderWindow& window, Level* level) override;
	private:
		States Fall(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level) override;
	
};

