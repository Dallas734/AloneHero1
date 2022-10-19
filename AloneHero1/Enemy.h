#pragma once
#include "Entity.h"
#include "levelfwd.h"

class Enemy : public Entity
{
	public:
		Enemy(double x, double y, double width, double height, double speed, int health, double strength) : Entity(x, y, width, height, speed, health, strength)
		{
			this->directory = "Enemies/";
			this->state = RUN;
		};
	
		~Enemy() {};
		void Update(float time, RenderWindow& window, Level* level) override;
	
};

