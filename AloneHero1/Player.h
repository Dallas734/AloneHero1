#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Player : public Entity
{
	public:
		Player(double x, double y) : Entity(x, y, 160, 111, 0.1, 100, 100)
		{
			this->directory = "Player/";
			this->state = IDLE;
		};
		~Player() {};
		States Jump(bool& keyPressed, float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window);
		void HelthUP(int regenerationUnits);
		void StrengthUP();
		void SpeedUp(double improveUnits);
		void Update(float time, RenderWindow& window) override;
		
};

