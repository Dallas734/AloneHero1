#include "Player.h"


void Player::HelthUP(int regenerationUnits)
{
	this->health += regenerationUnits;
}

void Player::SpeedUp(double improveUnits)
{
	this->speed += improveUnits;
}

States Player::Update(float time)
{
	Directions direction = RIGHT;
	// Состояния
	if ((Keyboard::isKeyPressed(Keyboard::Right)) || (Keyboard::isKeyPressed(Keyboard::D)))
	{
		direction = RIGHT;
		return Move(time, 0, 0, this->width, this->height, 8, RIGHT);
	}
	else if ((Keyboard::isKeyPressed(Keyboard::Left)) || (Keyboard::isKeyPressed(Keyboard::A)))
	{
		direction = LEFT;
		return Move(time, 0, 0, this->width, this->height, 8, LEFT);
	}
	else if (dx == 0)
	{
		return Idle(time, 0, 0, this->width, this->height, 8, direction);
	}
}

