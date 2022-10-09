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
		void Control();
		void HelthUP(int regenerationUnits);
		void StrengthUP();
		void SpeedUp(double improveUnits);
		void Update(float time, RenderWindow& window) override;
		/*States Move(float time, double width, double height, int frames, Directions direction) override;
		int Hit(float time, double width, double height, int frames, double strength, Directions direction) override;
		void Damage(float time, double width, double height, int frames, double strength, Directions direction) override;
		States Idle(float time, double width, double height, int frames, Directions direction) override;*/
};

