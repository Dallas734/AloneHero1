#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Player : public Entity
{
	public:
		Player(String F, double x, double y, double width, double height) : Entity(F, x, y, width, height) {}
		~Player() {};
		void Jump();
		void HelthUP();
		void StrengthUP();
		void Move(float time) override;
		int Hit(double strength) override;
		void Damage(double strength) override;
		void Walk() override;
		void Update(float time) override;
};

