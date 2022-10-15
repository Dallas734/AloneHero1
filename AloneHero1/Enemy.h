#pragma once
#include "Entity.h"

class Enemy : public Entity
{
	public:
		Enemy(double x, double y, double width, double height, double speed, int health, double strength) : Entity(x, y, width, height, speed, health, strength) {};
		~Enemy() {};
		void Update(float time, RenderWindow& window, Level* level) override;
	
};

