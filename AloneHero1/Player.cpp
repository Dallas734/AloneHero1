#include "Player.h"


States Player::Jump(bool& keyPressed, float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window)
{
	SetSprite("Jump.png", JUMP, xBeginSprite, yBeginSprite, width, height);
	currentFrame += time * 0.01;
	if (this->currentFrame > frames) this->currentFrame -= frames;

	if (onGround)
	{
		dy = -10;
		onGround = false;
		this->state = JUMP;
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
	x += dx * time;
	y += dy * time;
	dx = 0;
	dy = 0;
	spriteJump.setTextureRect(IntRect(width /** int(currentFrame)*/, yBeginSprite, width, height));
	spriteJump.setPosition(x, y);
	window.clear();
	window.draw(GetSprite(JUMP));
	window.display();
	
	return JUMP;
}

void Player::Control()
{

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
	if (!onGround || state == JUMP)
	{
		dy += 0.0001 * time;
		y += dy * time;
		x += dx * time;
		// onGround = true;
	}
	//onGround = false;
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

	if (Keyboard::isKeyPressed(Keyboard::Space) && onGround)
	{
		state = JUMP;
		Jump(keyPressed, time, 0, 0, this->width, this->height, 2, direction, window);
	}

	/*switch (state)
	{
	case RUN:
		SetSprite("Run.png", RUN, 0, 0, width, height);
		currentFrame += time * 0.01;
		if (this->currentFrame > 8) this->currentFrame -= 8;
		switch (direction)
		{
		case RIGHT:
			dx = speed;
			spriteMove.setOrigin({ 0, 0 });
			spriteMove.setScale(1, 1);
			break;
		case LEFT:
			dx = -speed;
			spriteMove.setOrigin({ spriteMove.getLocalBounds().width, 0 });
			spriteMove.setScale(-1, 1);
			break;
		}
		spriteMove.setTextureRect(IntRect(width * int(currentFrame), 0, width, height));
		window.clear();
		spriteMove.setPosition(x, y);
		window.draw(GetSprite(RUN));
		window.display();
		break;
	case HIT:
		SetSprite("Hit1.png", HIT, 0, 0, width, height);
		currentFrame += time * 0.01;
		if (this->currentFrame > 4) this->currentFrame -= 4;
		switch (direction)
		{
		case RIGHT:
			spriteHit.setOrigin({ 0, 0 });
			spriteHit.setScale(1, 1);
			break;
		case LEFT:
			spriteHit.setOrigin({ spriteHit.getLocalBounds().width, 0 });
			spriteHit.setScale(-1, 1);
			break;
		}
		spriteHit.setTextureRect(IntRect(width * int(currentFrame), 0, width, height));
		spriteHit.setPosition(x, y);
		window.clear();
		window.draw(GetSprite(HIT));
		window.display();
		break;
	case IDLE:
		SetSprite("Idle.png", IDLE, 0, 0, width, height);
		currentFrame += time * 0.005;
		if (this->currentFrame > 8) this->currentFrame -= 8;
		switch (direction)
		{
		case RIGHT:
			spriteIdle.setOrigin({ 0, 0 });
			spriteIdle.setScale(1, 1);
			break;
		case LEFT:
			spriteIdle.setOrigin({ spriteIdle.getLocalBounds().width, 0 });
			spriteIdle.setScale(-1, 1);
		}
		spriteIdle.setTextureRect(IntRect(width* int(currentFrame), yBeginSprite, width, height));
		spriteIdle.setPosition(x, y);
		window.clear();
		window.draw(GetSprite(IDLE));
		window.display();
		break;
	case JUMP:

	}*/
}

