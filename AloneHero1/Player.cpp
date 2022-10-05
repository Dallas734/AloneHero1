#include "Player.h"


States Player::Update(float time)
{
	// Состояния
	if ((Keyboard::isKeyPressed(Keyboard::Right)) || (Keyboard::isKeyPressed(Keyboard::D)))
	{
		return Move(time, RIGHT);
	}
	else if ((Keyboard::isKeyPressed(Keyboard::Left)) || (Keyboard::isKeyPressed(Keyboard::A)))
	{
		return Move(time, LEFT);
	}
	else if (speed == 0)
	{
		return Idle(time);
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

States Player::Idle(float time)
{
	SetSprite("Idle.png", IDLE, 0, 0, 160, 111);
	currentFrame += time * 0.005;
	if (this->currentFrame > 8) this->currentFrame -= 8;
	spriteIdle.setTextureRect(IntRect(160 * int(currentFrame), 0, 160, 111));
	if (this->currentFrame > 8) this->currentFrame -= 8;
	spriteIdle.setPosition(x, y);
	
	return IDLE;
}