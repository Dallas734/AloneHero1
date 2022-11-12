#pragma once
#include "Entity.h"
#include "levelfwd.h"

class Enemy : public Entity
{
	public:
		bool collisionWithPlayer;
		Enemy(double x, double y, double speed, int health, double strength) : Entity(x, y, speed, health, strength)
		{
			this->directory = "Enemies/";
			this->state = FALL;
			direction = RIGHT;
		};
		~Enemy() {};
		void Update(float time, RenderWindow& window, Level* level) override;
		void GetMessage(Message& message) override;
	private:
		States Fall(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level) override;
	
};

