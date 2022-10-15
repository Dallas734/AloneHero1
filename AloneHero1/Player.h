#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "levelfwd.h"// Forward declaration класса агрегата.


//class Level;
class Player : public Entity
{
	private:
		View view;
	public:
		Player(double x, double y) : Entity(x, y, 160, 111, 0.1, 100, 100)
		{
			this->directory = "Player/";
			this->state = FALL;
		};
		~Player() {};
		States Jump(bool& keyPressed, float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level);
		States Fall(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level);
		void HelthUP(int regenerationUnits);
		void StrengthUP();
		void SpeedUp(double improveUnits);
		void Update(float time, RenderWindow& window, Level* level) override;
		void ViewOnPlayer(double x, double y);
		View GetPlayerView();
		void CheckCollisionWithMap(double dx, double dy, Level* level, float time) override;
};

