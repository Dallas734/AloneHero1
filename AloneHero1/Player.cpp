#include "Player.h"
#include "Level.h"


States Player::Jump(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level)
{
	this->state = JUMP;
	SetSprite("Jump.png", JUMP, xBeginSprite, yBeginSprite, width, height);
	currentFrame += time * 0.01;
	if (this->currentFrame > frames) this->currentFrame -= frames;

	if (onGround)
	{
		this->dy = -0.1; // ������ ������
		onGround = false;
	}

	if (onGround)
	{
		this->dy = 0;
		return IDLE;
	}
	else
	{
		this->y += dy * time;
		this->dy += 0.0001 * time;
	}

	this->dx = 0;
	
	sprites[JUMP].setTextureRect(IntRect(xBeginSprite + (width + bufWidth) * int(currentFrame), yBeginSprite, width, height));
	sprites[JUMP].setPosition(this->x, this->y);
	
	return JUMP;
}

States Player::Fall(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level)
{
	SetSprite("Fall.png", FALL, xBeginSprite, yBeginSprite, width, height);
	currentFrame += time * 0.005;
	if (this->currentFrame > frames) this->currentFrame -= frames;

	if (direction == RIGHT)
	{
		sprites[FALL].setOrigin({ 0, 0 });
		sprites[FALL].setScale(1, 1);
		this->state = FALL;
	}
	else if (direction == LEFT)
	{
		sprites[FALL].setOrigin({ sprites[FALL].getLocalBounds().width, 0 });
		sprites[FALL].setScale(-1, 1);
		this->state = FALL;
	}

	if (onGround)
	{
		this->dy = 0;
		return IDLE;
	}
	else
	{
		this->y += dy * time;
		this->dy += 0.0001 * time;
	}

	sprites[FALL].setTextureRect(IntRect(xBeginSprite + (width + bufWidth) * int(currentFrame), yBeginSprite, width, height));
	sprites[FALL].setPosition(x, y);

	return FALL;
}

void Player::HelthUP(int regenerationUnits)
{
	this->health += regenerationUnits;
}

void Player::SpeedUp(double improveUnits)
{
	this->speed += improveUnits;
}

void Player::Update(float time, RenderWindow& window, Level* level)
{
	std::cout << dy;

	// ������� ����� � �������
	if (dy == 0 && state != IDLE && state != DAMAGE)
	{
		state = FALL;
		onGround = false;
		dy += 0.0001 * time;
	}
	//dy += 0.0001 * time; // ���������������, ����� ������ ����������.
	y += dy * time; 
	//CheckCollisionWithMap(0, dy, level, time);
	level->CheckCollision(0, dy, this);

	// ���������
	if (Keyboard::isKeyPressed(Keyboard::D)/* && onGround*/)
	{	
		if (state == IDLE)
		{
			direction = RIGHT;
			state = RUN;
			Move(time, xBeginSprite, yBeginSprite, this->width, this->height, countFrames[RUN], direction, window, level);
			//ViewOnPlayer(x, y, level);
			level->ViewOnPlayer(this);
		}
		if (state == JUMP)
		{
			dx = speed;
			x += dx * time;
			//CheckCollisionWithMap(dx, 0, level, time);
			level->CheckCollision(dx, 0, this);
			sprites[JUMP].setOrigin({ 0, 0 });
			sprites[JUMP].setScale(1, 1);
			dx = 0;
		}
		
	}
	else if (Keyboard::isKeyPressed(Keyboard::A)/* && onGround*/)
	{
		if (state == IDLE)
		{
			direction = LEFT;
			state = RUN;
			Move(time, xBeginSprite, yBeginSprite, this->width, this->height, countFrames[RUN], direction, window, level);
			// ViewOnPlayer(x, y, level);
			level->ViewOnPlayer(this);
		}
		if (state == JUMP)
		{
			dx = -speed;
			x += dx * time;
			//CheckCollisionWithMap(dx, 0, level, time);
			level->CheckCollision(dx, 0, this);
			sprites[JUMP].setOrigin({ sprites[JUMP].getLocalBounds().width, 0 });
			sprites[JUMP].setScale(-1, 1);
			dx = 0;
		}
		
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right) && onGround)
	{
		direction = RIGHT;
		state = HIT;
		Hit(time, xBeginSprite, yBeginSprite, widthOfHit, this->height, countFrames[HIT], this->bufOfHit, direction, window, level);
		// ViewOnPlayer(x, y, level);
		level->CheckCollision(dx, 0, this);
		level->ViewOnPlayer(this);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left) && onGround)
	{
		direction = LEFT;
		state = HIT;
		Hit(time, xBeginSprite, yBeginSprite, widthOfHit, this->height, countFrames[HIT], this->bufOfHit, direction, window, level);
		// ViewOnPlayer(x, y, level);
		level->CheckCollision(dx, 0, this);
		level->ViewOnPlayer(this);
	}
	else if (state == IDLE)
	{
		state = IDLE;
		Idle(time, xBeginSprite, yBeginSprite, this->width, this->height, countFrames[IDLE], direction, window, level);
		// ViewOnPlayer(x, y, level);
		level->ViewOnPlayer(this);
	}

	if (state == FALL)
	{
		state = Fall(time, xBeginSprite, yBeginSprite, this->width, this->height, countFrames[FALL], direction, window, level);
		// ViewOnPlayer(x, y, level);
		level->ViewOnPlayer(this);
	}
	
	if (state == DAMAGE)
	{
		state = DAMAGE;
		Damage(time, xBeginSprite, yBeginSprite, this->width, this->height, countFrames[DAMAGE], this->damage, direction, window, level);
		// ViewOnPlayer(x, y, level);
		level->ViewOnPlayer(this);
	}

	if (((Keyboard::isKeyPressed(Keyboard::Space) && onGround) || (!onGround && state == JUMP)) && state != HIT && state != DAMAGE)
	{
		state = JUMP;
		Jump(time, xBeginSprite, yBeginSprite, this->width, this->height, countFrames[JUMP], direction, window, level);
		// ViewOnPlayer(x, y, level);
		level->ViewOnPlayer(this);
	}

	if (this->health <= 0)
	{
		//Death(time, xBeginSprite, yBeginSprite, this->width, this->height, countFramesOfDeath, direction, window, level);
		//state = DEATH;
	}
}




