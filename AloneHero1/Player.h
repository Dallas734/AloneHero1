#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Player : public Entity
{
	public:
		Player(double x, double y) : Entity(x, y, 160, 111, 0.1, 100, 100)
		{
			this->directory = "Player/";
		};
		~Player() {};
		void Jump();
		void HelthUP(int regenerationUnits);
		void StrengthUP();
		void SpeedUp(double improveUnits);
		States Update(float time) override;

		/*States Move(float time, double width, double height, int frames, Directions direction) override;
		int Hit(float time, double width, double height, int frames, double strength, Directions direction) override;
		void Damage(float time, double width, double height, int frames, double strength, Directions direction) override;
		States Idle(float time, double width, double height, int frames, Directions direction) override;*/
};

