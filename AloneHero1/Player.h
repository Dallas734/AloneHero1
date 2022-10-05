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
		void Move(float time);
		int Hit(double strength) override;
		void Damage(double strength) override;
		void Idle(float time);
		double GetDX();
		void SetDX(double dx);
		
};

