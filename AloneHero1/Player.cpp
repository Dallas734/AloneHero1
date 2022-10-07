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
		return Move(time, RIGHT);
	}
	else if ((Keyboard::isKeyPressed(Keyboard::Left)) || (Keyboard::isKeyPressed(Keyboard::A)))
	{
		direction = LEFT;
		return Move(time, LEFT);
	}
	else if (speed == 0)
	{
		return Idle(time, direction);
	}
	x += dx * time;
	y += dy * time;

}

States Player::Move(float time, Directions direction)
{
	SetSprite("Run.png", RUN, 0, 0, 160, 111);
	speed = 0.1;
	if (direction == RIGHT)
	{
		dx = speed;
		spriteMove.setOrigin({ 0, 0 });
		spriteMove.setScale(1, 1);
	}
	else if (direction == LEFT)
	{
		dx = -speed;
		spriteMove.setOrigin({ spriteMove.getLocalBounds().width, 0 });
		spriteMove.setScale(-1, 1);
	}
	spriteMove.setTextureRect(IntRect(160 * int(currentFrame), 0, 160, 111));
	x += dx * time;
	y += dy * time;
	currentFrame += time * 0.005;
	if (this->currentFrame > 8) this->currentFrame -= 8;
	speed = 0;
	spriteMove.setPosition(x, y);
	
	return RUN;
}

int Player::Hit(double strength)
{
	return 0;
}

void Player::Damage(double strength)
{
}

States Player::Idle(float time, Directions direction)
{
	SetSprite("Idle.png", IDLE, 0, 0, 160, 111);
	currentFrame += time * 0.005;
	if (this->currentFrame > 8) this->currentFrame -= 8;
	// Доделать поворот!
	if (direction == RIGHT)
	{
		spriteIdle.setTextureRect(IntRect(160 * int(currentFrame), 0, 160, 111));
		spriteIdle.setOrigin({ 0, 0 });
		spriteIdle.setScale(1, 1);
		spriteIdle.setPosition(x, y);
	}
	else if (direction == LEFT)
	{
		spriteIdle.setTextureRect(IntRect(160 * int(currentFrame), 0, 160, 111));
		spriteIdle.setOrigin({ spriteIdle.getLocalBounds().width, 0 });
		spriteIdle.setScale(-1, 1);
		spriteIdle.setPosition(x, y);
	}
	
	return IDLE;
}