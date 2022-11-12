#include "Enemy.h"
#include "Level.h"

void Enemy::Update(float time, RenderWindow& window, Level* level)
{
	Message* message;

	y += dy * time;
	message = new Message(RUN_C, 0, this, this->x, this->y, 0, this->dy);
	level->GetMessage(*message);

	if (state == FALL)
	{
		state = Fall(time, xBeginSprite, yBeginSprite, width, height, this->countFrames[IDLE], direction, window, level);
	}

	if (state == RUN)
	{
		Move(time, xBeginSprite, yBeginSprite, width, height, this->countFrames[RUN], direction, window, level);
		message = new Message(RUN_C, 0, this, this->x, this->y, 0, this->dy);
		level->GetMessage(*message);
	}

	if (state == HIT)
	{
		Hit(time, xBeginSpriteHit, yBeginSpriteHit, widthOfHit, heightOfHit, this->countFrames[HIT], bufOfHit, direction, window, level);
		message = new Message(HIT_C, 0, this, this->x, this->y, this->dx, 0);
		level->GetMessage(*message);
	}

	if (state == DAMAGE)
	{
		Damage(time, xBeginSprite, yBeginSprite, width, height, countFrames[DAMAGE], this->damage, direction);
	}

	if (this->health <= 0)
	{
		Death(time, xBeginSprite, yBeginSprite, width, height, countFrames[DEATH], direction, window, level);
	}
}

void Enemy::GetMessage(Message& message)
{
	if (message.code == DAMAGE_C)
	{
		collisionWithPlayer = true;
		state = DAMAGE;
		damage = message.units;
	}
	else if (message.code == RUN_C)
	{
		collisionWithPlayer = false;
		state = RUN;
	}
	else if (message.code == HIT_C)
	{
		collisionWithPlayer = true;
		state = HIT;
	}
	else if (message.code == FALL_C)
	{
		this->y = message.y;
		this->dy = message.dy;
		state = RUN;
		onGround = true;
	}
	else if (message.code == JUMP_C)
	{
		this->y = message.y;
	}
	else if (message.code == CHANGE_X)
	{
		this->x = message.x;
	}
	else if (message.code == ENEMY_BARIER)
	{
		if (direction == RIGHT) direction = LEFT;
		else direction = RIGHT;
	}
}

States Enemy::Fall(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level)
{
	SetSprite("Idle.png", IDLE, xBeginSprite, yBeginSprite, width, height);
	currentFrame += time * 0.005;
	if (this->currentFrame > frames) this->currentFrame -= frames;

	if (direction == RIGHT)
	{
		sprites[IDLE].setOrigin({ 0, 0 });
		sprites[IDLE].setScale(1, 1);
		this->state = FALL;
	}
	else if (direction == LEFT)
	{
		sprites[IDLE].setOrigin({ sprites[IDLE].getLocalBounds().width, 0 });
		sprites[IDLE].setScale(-1, 1);
		this->state = FALL;
	}

	if (onGround)
	{
		dy = 0;
		return IDLE;
	}
	else
	{
		y += dy * time;
		dy += 0.0001 * time;
	}

	sprites[IDLE].setTextureRect(IntRect(xBeginSprite + (width + bufWidth) * int(currentFrame), yBeginSprite, width, height));
	sprites[IDLE].setPosition(x, y);

	return FALL;
}
