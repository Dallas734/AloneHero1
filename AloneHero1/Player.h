#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "levelfwd.h"// Forward declaration класса агрегата.

const double BUF_OF_PLAYER_HIT = 47;
//class Level;
class Player : public Entity
{
	private:
		View view;
		sf::Vector2i sizeOfView;
	public:
		Player(double x, double y) : Entity(x, y, 0.1, 100, 100)
		{
			this->directory = "Player/";
			this->state = FALL;
			this->width = 42;
			this->height = 56;
			this->bufWidth = 118;
			this->sizeOfView.x = 600;
			this->sizeOfView.y = 400;
		};
		~Player() {};
		void HelthUP(int regenerationUnits);
		void StrengthUP();
		void SpeedUp(double improveUnits);
		void Update(float time, RenderWindow& window, Level* level) override;
		void ViewOnPlayer(double x, double y, Level* level);
		View GetPlayerView();
		void CheckCollisionWithMap(double dx, double dy, Level* level, float time) override;
	private:
		States Jump(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level);
		States Fall(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level) override;

};

