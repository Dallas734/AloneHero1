#include "Enemy.h"
#include "Level.h"

void Enemy::Update(float time, RenderWindow& window, Level* level)
{
	/*if (dy == 0 && state != RUN)
	{
		onGround = false;
		dy += 0.0001 * time;
	}*/

	y += dy * time;
	//CheckCollisionWithMap(0, dy, level, time);
	level->CheckCollision(0, dy, this);

	//Idle(time, xBeginSprite, yBeginSprite, width, height, countFramesOfIdle, direction, window, level);

	if (state == FALL)
	{
		state = Fall(time, xBeginSprite, yBeginSprite, width, height, countFramesOfIdle, direction, window, level);
	}

	if (state == RUN)
	{
		Move(time, xBeginSprite, yBeginSprite, width, height, countFramesOfMove, direction, window, level);
		//Hit(time, xBeginSpriteHit, yBeginSpriteHit, widthOfHit, heightOfHit, countFramesOfHit, strength, bufOfHit, direction, window, level);
		level->CheckCollision(0, dy, this);
	}

	if (state == HIT)
	{
		
		Hit(time, xBeginSpriteHit, yBeginSpriteHit, widthOfHit, heightOfHit, countFramesOfHit, strength, bufOfHit, direction, window, level);
		/*if (level->GetCollisionWithPlayer())
		{
			if (direction == RIGHT) direction = LEFT;
			else direction = RIGHT;
		}*/
		/*if (int(currentFrame) == 8)
		{
			state = RUN;
		}*/
	}


}

States Enemy::Fall(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level)
{
	SetSprite("Idle.png", IDLE, xBeginSprite, yBeginSprite, width, height);
	currentFrame += time * 0.005;
	if (this->currentFrame > frames) this->currentFrame -= frames;

	if (direction == RIGHT)
	{
		spriteIdle.setOrigin({ 0, 0 });
		spriteIdle.setScale(1, 1);
		this->state = FALL;
	}
	else if (direction == LEFT)
	{
		spriteIdle.setOrigin({ spriteIdle.getLocalBounds().width, 0 });
		spriteIdle.setScale(-1, 1);
		this->state = FALL;
	}

	//CheckCollisionWithMap(0, dy, level, time);
	level->CheckCollision(0, dy, this);

	if (onGround)
	{
		dy = 0;
		//CheckCollisionWithMap(0, dy, level, time);
		//level->CheckCollision(0, dy, this);
		return IDLE;
	}
	else
	{
		y += dy * time;
		dy += 0.0001 * time;
		//CheckCollisionWithMap(0, dy, level, time);
		//level->CheckCollision(0, dy, this);
	}

	//spriteFall.setTextureRect(IntRect(width * int(currentFrame), yBeginSprite, width, height));
	spriteIdle.setTextureRect(IntRect(xBeginSprite + (width + bufWidth) * int(currentFrame), yBeginSprite, width, height));
	spriteIdle.setPosition(x, y);

	return FALL;
}
