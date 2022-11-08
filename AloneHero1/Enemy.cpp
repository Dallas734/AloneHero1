#include "Enemy.h"
#include "Level.h"

void Enemy::Update(float time, RenderWindow& window, Level* level)
{
	y += dy * time;
	level->CheckCollision(0, dy, this);

	if (state == FALL)
	{
		state = Fall(time, xBeginSprite, yBeginSprite, width, height, this->countFrames[IDLE], direction, window, level);
	}

	if (state == RUN)
	{
		Move(time, xBeginSprite, yBeginSprite, width, height, this->countFrames[RUN], direction, window, level);
		level->CheckCollision(0, dy, this);
	}

	if (state == HIT)
	{
		Hit(time, xBeginSpriteHit, yBeginSpriteHit, widthOfHit, heightOfHit, this->countFrames[HIT], bufOfHit, direction, window, level);
		level->CheckCollision(dx, 0, this);
	}

	if (state == DAMAGE)
	{
		Damage(time, xBeginSprite, yBeginSprite, width, height, countFrames[DAMAGE], this->damage, direction, window, level);
	}

	if (this->health <= 0)
	{
		Death(time, xBeginSprite, yBeginSprite, width, height, countFrames[DEATH], direction, window, level);
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
