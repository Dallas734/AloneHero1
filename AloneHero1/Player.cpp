#include "Player.h"


States Player::Jump(bool& keyPressed, float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window)
{
	this->state = JUMP;
	SetSprite("Jump.png", JUMP, xBeginSprite, yBeginSprite, width, height);
	currentFrame += time * 0.01;
	if (this->currentFrame > frames) this->currentFrame -= frames;

	if (onGround)
	{
		dy = -0.1; // Высота прыжка
		onGround = false;
	}

	if (direction == RIGHT)
	{
		dx = speed;
		x += dx * time;
		spriteJump.setOrigin({ 0, 0 });
		spriteJump.setScale(1, 1);
	}
	else if (direction == LEFT)
	{
		dx = -speed;
		x += dx * time;
		spriteJump.setOrigin({ spriteJump.getLocalBounds().width, 0 });
		spriteJump.setScale(-1, 1);
	}

	y += dy * time;
	dx = 0;

	spriteJump.setTextureRect(IntRect(width * int(currentFrame), yBeginSprite, width, height));
	spriteJump.setPosition(x, y);
	window.clear();
	window.draw(GetSprite(JUMP));
	window.display();
	
	return JUMP;
}

void Player::HelthUP(int regenerationUnits)
{
	this->health += regenerationUnits;
}

void Player::SpeedUp(double improveUnits)
{
	this->speed += improveUnits;
}

void Player::Update(float time, RenderWindow& window)
{
	bool checkIdle = true;
	bool keyPressed = false;

	// Уровень земли и падение
	int ground = 300;
	if (!onGround)
	{
		dy += 0.0001 * time;
	}
	y += dy * time;
	if (y > ground)
	{
		y = ground;
		dy = 0;
		onGround = true;
	}

	// Состояния
	if (Keyboard::isKeyPressed(Keyboard::D) && onGround)
	{
		direction = RIGHT;
		state = RUN;
		Move(time, 0, 0, this->width, this->height, 8, direction, window);
	}
	else if (Keyboard::isKeyPressed(Keyboard::A) && onGround)
	{
		direction = LEFT;
		state = RUN;
		Move(time, 0, 0, this->width, this->height, 8, direction, window);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		direction = RIGHT;
		state = HIT;
		Hit(time, 0, 0, this->width, this->height, 4, this->strength, direction, window);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left) /*&& dy == 0 && onGround*/)
	{
		direction = LEFT;
		state = HIT;
		Hit(time, 0, 0, this->width, this->height, 4, this->strength, direction, window);
	}
	else if ((dy == 0 || state == IDLE)/* && onGround*/)
	{
		state = IDLE;
		Idle(time, 0, 0, this->width, this->height, 8, direction, window);
	}
	
	if ((Keyboard::isKeyPressed(Keyboard::Space) && onGround) || (!onGround && state == JUMP))
	{
		state = JUMP;
		Jump(keyPressed, time, 0, 0, this->width, this->height, 2, direction, window);
	}

}

