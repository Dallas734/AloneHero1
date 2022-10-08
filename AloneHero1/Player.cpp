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
	// Состояния
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		direction = RIGHT;
		return Move(time, 0, 0, this->width, this->height, 8, direction);
	}
	else if (Keyboard::isKeyPressed(Keyboard::A))
	{
		direction = LEFT;
		return Move(time, 0, 0, this->width, this->height, 8, direction);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		direction = RIGHT;
		return Hit(time, 0, 0, this->width, this->height, 4, this->strength, direction);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		direction = LEFT;
		return Hit(time, 0, 0, this->width, this->height, 4, this->strength, direction);
	}
	else if (dx == 0)
	{
		return Idle(time, 0, 0, this->width, this->height, 8, direction);
	}
}

