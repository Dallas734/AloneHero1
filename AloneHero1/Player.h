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
		void Move(float time, String F, double x, double y, double width, double height) override;
		int Hit(double strength) override;
		void Damage(double strength) override;
};

