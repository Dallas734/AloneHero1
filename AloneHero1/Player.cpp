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
		dy = -0.1; // Высота прыжка
		onGround = false;
	}

	if (onGround)
	{
		dy = 0;
		//CheckCollisionWithMap(0, dy, level, time);
		return IDLE;
	}
	else
	{
		y += dy * time;
		dy += 0.0001 * time;
		//CheckCollisionWithMap(0, dy, level, time);
	}

	//CheckCollisionWithMap(0, dy, level);
	dx = 0;
	
	//spriteJump.setTextureRect(IntRect(xBeginSprite * int(currentFrame), yBeginSprite, width, height));
	spriteJump.setTextureRect(IntRect(xBeginSprite + (width + bufWidth) * int(currentFrame), yBeginSprite, width, height));
	
	spriteJump.setPosition(x, y);
	/*window.clear();
	window.draw(GetSprite(JUMP));
	window.display();*/
	
	return JUMP;
}

States Player::Fall(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level)
{
	SetSprite("Fall.png", FALL, xBeginSprite, yBeginSprite, width, height);
	currentFrame += time * 0.005;
	if (this->currentFrame > frames) this->currentFrame -= frames;

	if (direction == RIGHT)
	{
		spriteFall.setOrigin({ 0, 0 });
		spriteFall.setScale(1, 1);
		this->state = FALL;
	}
	else if (direction == LEFT)
	{
		spriteFall.setOrigin({ spriteFall.getLocalBounds().width, 0 });
		spriteFall.setScale(-1, 1);
		this->state = FALL;
	}

	//CheckCollisionWithMap(0, dy, level, time);
	//level->CheckCollision(0, dy, this);
	if (onGround)
	{
		this->dy = 0;
		//CheckCollisionWithMap(0, dy, level, time);
		return IDLE;
	}
	else
	{
		this->y += dy * time;
		this->dy += 0.0001 * time;
		//CheckCollisionWithMap(0, dy, level, time);
	}

	//spriteFall.setTextureRect(IntRect(width * int(currentFrame), yBeginSprite, width, height));
	spriteFall.setTextureRect(IntRect(xBeginSprite + (width + bufWidth) * int(currentFrame), yBeginSprite, width, height));
	spriteFall.setPosition(x, y);

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

	// Уровень земли и падение
	if (dy == 0 && state != IDLE && state != DAMAGE)
	{
		state = FALL;
		onGround = false;
		dy += 0.0001 * time;
	}
	//dy += 0.0001 * time; // Раскоментировав, будет больше притяжение.
	y += dy * time; 
	//CheckCollisionWithMap(0, dy, level, time);
	level->CheckCollision(0, dy, this);

	// Состояния
	if (Keyboard::isKeyPressed(Keyboard::D)/* && onGround*/)
	{	
		if (state == IDLE)
		{
			direction = RIGHT;
			state = RUN;
			Move(time, xBeginSprite, yBeginSprite, this->width, this->height, 8, direction, window, level);
			//ViewOnPlayer(x, y, level);
			level->ViewOnPlayer(this);
		}
		if (state == JUMP)
		{
			dx = speed;
			x += dx * time;
			//CheckCollisionWithMap(dx, 0, level, time);
			level->CheckCollision(dx, 0, this);
			spriteJump.setOrigin({ 0, 0 });
			spriteJump.setScale(1, 1);
			dx = 0;
		}
		
	}
	else if (Keyboard::isKeyPressed(Keyboard::A)/* && onGround*/)
	{
		if (state == IDLE)
		{
			direction = LEFT;
			state = RUN;
			Move(time, xBeginSprite, yBeginSprite, this->width, this->height, 8, direction, window, level);
			// ViewOnPlayer(x, y, level);
			level->ViewOnPlayer(this);
		}
		if (state == JUMP)
		{
			dx = -speed;
			x += dx * time;
			//CheckCollisionWithMap(dx, 0, level, time);
			level->CheckCollision(dx, 0, this);
			spriteJump.setOrigin({ spriteJump.getLocalBounds().width, 0 });
			spriteJump.setScale(-1, 1);
			dx = 0;
		}
		
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right) && onGround)
	{
		direction = RIGHT;
		state = HIT;
		Hit(time, xBeginSprite, yBeginSprite, widthOfHit, this->height, 4, this->strength, this->bufOfHit, direction, window, level);
		// ViewOnPlayer(x, y, level);
		level->ViewOnPlayer(this);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left) && onGround)
	{
		direction = LEFT;
		state = HIT;
		Hit(time, xBeginSprite, yBeginSprite, widthOfHit, this->height, 4, this->strength, this->bufOfHit, direction, window, level);
		// ViewOnPlayer(x, y, level);
		level->ViewOnPlayer(this);
	}
	else if (state == IDLE)
	{
		state = IDLE;
		Idle(time, xBeginSprite, yBeginSprite, this->width, this->height, 8, direction, window, level);
		// ViewOnPlayer(x, y, level);
		level->ViewOnPlayer(this);
	}

	if (state == FALL)
	{
		state = Fall(time, xBeginSprite, yBeginSprite, this->width, this->height, 2, direction, window, level);
		// ViewOnPlayer(x, y, level);
		level->ViewOnPlayer(this);
	}
	
	if (state == DAMAGE)
	{
		state = DAMAGE;
		Damage(time, xBeginSprite, yBeginSprite, this->width, this->height, 4, this->strength, direction, window, level);
		// ViewOnPlayer(x, y, level);
		level->ViewOnPlayer(this);
	}

	if (((Keyboard::isKeyPressed(Keyboard::Space) && onGround) || (!onGround && state == JUMP)) && state != HIT && state != DAMAGE)
	{
		state = JUMP;
		Jump(time, xBeginSprite, yBeginSprite, this->width, this->height, 2, direction, window, level);
		// ViewOnPlayer(x, y, level);
		level->ViewOnPlayer(this);
	}

}




