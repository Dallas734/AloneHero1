#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "levelfwd.h"// Forward declaration ?????? ????????.


//class Level;
class Player : public Entity
{
	public:
		Player(double x, double y) : Entity(x, y, 0.1, 100, 100)
		{
			this->directory = "Player/";
			this->state = FALL;
			this->width = 42;
			this->height = 56;
			this->bufWidth = 118;
			this->bufOfHit = 47;
			this->xBeginSprite = 56;
			this->yBeginSprite = 44;
			this->widthOfHit = 109;
			this->countFrames[RUN] = 8;
			this->countFrames[IDLE] = 8;
			this->countFrames[HIT] = 4;
			this->countFrames[DAMAGE] = 4;
			this->countFrames[JUMP] = 2;
			this->countFrames[FALL] = 2;
			this->countFrames[DEATH] = 6;
		};
		~Player() {};
		void HelthUP(int regenerationUnits);
		void StrengthUP();
		void SpeedUp(double improveUnits);
		void Update(float time, RenderWindow& window, Level* level) override;
		void GetMessage(Message& message) override;
	private:
		States Jump(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level);
		States Fall(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level) override;

};

