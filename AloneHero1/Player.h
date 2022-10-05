#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Player : public Entity
{
	public:
		Player(double x, double y) : Entity(x, y) {}
		~Player() {};
		void Jump();
		void HelthUP();
		void StrengthUP();
		States Update(float time) override;
		States Move(float time, Directions direction) override;
		int Hit(double strength) override;
		void Damage(double strength) override;
		States Idle(float time) override;
};

