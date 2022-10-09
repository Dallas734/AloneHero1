#include "Player.h"


States Player::Jump(float time, bool onGround, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window)
{
	SetSprite("Jump.png", JUMP, xBeginSprite, yBeginSprite, width, height);
	currentFrame += time * 0.01;
	if (this->currentFrame > frames) this->currentFrame -= frames;

	if (onGround && (state == RUN || state == IDLE))
	{
		dy = -5;
		onGround = false;
		this->state = JUMP;
	}

	/*if (direction == RIGHT)
	{
		dx = speed;
		spriteJump.setOrigin({ 0, 0 });
		spriteJump.setScale(1, 1);
	}
	else if (direction == LEFT)
	{
		dx = -speed;
		spriteJump.setOrigin({ spriteJump.getLocalBounds().width, 0 });
		spriteJump.setScale(-1, 1);
	}*/
	x += dx * time;
	y += dy * time;
	//dx = 0;
	dy = 0;
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

	// Уровень земли и падение
	int ground = 300;
	if (!onGround)
	{
		dy = dy + 0.0005 * time;
	}
	y += dy * time;
	onGround = false;
	if (y > ground)
	{
		y = ground;
		dy = 0;
		onGround = true;
	}

	// Состояния
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		direction = RIGHT;
		Move(time, 0, 0, this->width, this->height, 8, direction, window);
	}
	else if (Keyboard::isKeyPressed(Keyboard::A))
	{
		direction = LEFT;
		Move(time, 0, 0, this->width, this->height, 8, direction, window);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		direction = RIGHT;
		Hit(time, 0, 0, this->width, this->height, 4, this->strength, direction, window);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		direction = LEFT;
		Hit(time, 0, 0, this->width, this->height, 4, this->strength, direction, window);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		Jump(time, onGround, 0, 0, this->width, this->height, 2, direction, window);
	}
	else if (sf::Event::KeyReleased || state == IDLE)
	{
		Idle(time, 0, 0, this->width, this->height, 8, direction, window);
	}

}

