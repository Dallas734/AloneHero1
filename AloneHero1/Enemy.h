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
		double bufOfHit;

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
		void CheckCollisionWithMap(double dx, double dy, Level* level, float time) override;
		States Fall(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level) override;
	
};

