#include "Player.h"


States Player::Update(float time)
{
	States state;
	// Состояния
	if ((Keyboard::isKeyPressed(Keyboard::Right)) || (Keyboard::isKeyPressed(Keyboard::D)))
	{
		SetSprite("Run.png", RUN, 0, 0, 160, 111);
		speed = 0.1;
		dx = speed;
		spriteMove.setTextureRect(IntRect(160 * int(currentFrame), 0, 160, 111));
		x += dx * time;
		y += dy * time;
		currentFrame += time * 0.005;
		if (this->currentFrame > 8) this->currentFrame -= 8;
		dx = 0;
		speed = 0;
		spriteMove.setPosition(x, y);
		state = RUN;
	}
	else if (dx == 0)
	{
		SetSprite("Idle.png", IDLE, 0, 0, 160, 111);
		currentFrame += time * 0.005;
		if (this->currentFrame > 8) this->currentFrame -= 8;
		spriteIdle.setTextureRect(IntRect(160 * int(currentFrame), 0, 160, 111));
		if (this->currentFrame > 8) this->currentFrame -= 8;
		spriteIdle.setPosition(x, y);
		state = IDLE;
	}
	x += dx * time;
	y += dy * time;
	
	return state;
}

void Player::Move(float time)
{
	SetSprite("Run.png", RUN, 0, 0, 160, 111);
	Directions direction;
	// Управление
	if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D))))
	{
		direction = RIGHT;
		speed = 0.1;
		dx = speed;
		spriteMove.setTextureRect(IntRect(160 * int(currentFrame), 0, 160, 111));
	}

	x += dx * time;
	y += dy * time;
	currentFrame += time * 0.005;

	if (this->currentFrame > 8) this->currentFrame -= 8;

	dx = 0;
	speed = 0;
	spriteMove.setPosition(x, y);
}

int Player::Hit(double strength)
{
	return 0;
}

void Player::Damage(double strength)
{
}

void Player::Idle(float time)
{
	SetSprite("Idle.png", IDLE, 0, 0, 160, 111);

	if (this->currentFrame > 8) this->currentFrame -= 8;
	if (dx == 0)
	{
		spriteIdle.setTextureRect(IntRect(160 * int(currentFrame), 0, 160, 111));
	}
	
	currentFrame += time * 0.005;
	
	spriteIdle.setPosition(x, y);
}

double Player::GetDX()
{
	return dx;
}

void Player::SetDX(double dx)
{
	this->dx = dx;
}
