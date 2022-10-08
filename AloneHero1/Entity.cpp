#include "Entity.h"

Entity::Entity(double x, double y, double width, double height, double speed, int health, double strength)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->speed = speed;
	this->health = health;
	this->strength = strength;
	this->currentFrame = 0;
	this->dx = 0;
	this->dy = 0;
}

States Entity::Hit(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, double strength, Directions direction)
{
	SetSprite("Hit1.png", HIT, xBeginSprite, yBeginSprite, width, height);
	currentFrame += time * 0.01;
	if (this->currentFrame > frames) this->currentFrame -= frames;

	if (direction == RIGHT)
	{
		spriteHit.setOrigin({ 0, 0 });
		spriteHit.setScale(1, 1);
	}
	else if (direction == LEFT)
	{
		spriteHit.setOrigin({ spriteHit.getLocalBounds().width, 0 });
		spriteHit.setScale(-1, 1);
	}
	spriteHit.setTextureRect(IntRect(width * int(currentFrame), yBeginSprite, width, height));
	spriteHit.setPosition(x, y);

	return HIT;
}

void Entity::Damage(float time, double width, double height, int frames, double strength, Directions direction)
{
}

States Entity::Move(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction)
{
	SetSprite("Run.png", RUN, xBeginSprite, yBeginSprite, width, height);
	speed = this->speed; // PLAYER_SPEED
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
	spriteMove.setTextureRect(IntRect(width * int(currentFrame), yBeginSprite, width, height));
	x += dx * time;
	y += dy * time;
	currentFrame += time * 0.005;
	if (this->currentFrame > frames) this->currentFrame -= frames;
	dx = 0;
	dy = 0;
	spriteMove.setPosition(x, y);

	return RUN;
}

States Entity::Idle(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction)
{
	SetSprite("Idle.png", IDLE, xBeginSprite, yBeginSprite, width, height);
	currentFrame += time * 0.005;
	if (this->currentFrame > frames) this->currentFrame -= frames;

	if (direction == RIGHT)
	{
		spriteIdle.setOrigin({ 0, 0 });
		spriteIdle.setScale(1, 1);
	}
	else if (direction == LEFT)
	{
		spriteIdle.setOrigin({ spriteIdle.getLocalBounds().width, 0 });
		spriteIdle.setScale(-1, 1);
	}

	spriteIdle.setTextureRect(IntRect(width * int(currentFrame), yBeginSprite, width, height));
	spriteIdle.setPosition(x, y);

	return IDLE;
}

void Entity::SetSpeed(double speed)
{
	this->speed = speed;
}

double Entity::GetSpeed()
{
	return this->speed;
}


Sprite Entity::GetSprite(States spriteName)
{
	switch (spriteName)
	{
	case RUN:
		return spriteMove;
		break;
	case DAMAGE:
		break;
	case HIT:
		return spriteHit;
		break;
	case IDLE:
		return spriteIdle;
		break;
	}
}

void Entity::SetSprite(String fileName, States spriteName, double xBeginSprite, double yBeginSprite, double width, double height)
{
	image.loadFromFile("Images/" + this->directory + fileName);
	//image.loadFromFile("Images/Player/" + fileName);
	texture.loadFromImage(image);

	switch (spriteName)
	{
	case RUN:
		spriteMove.setTexture(texture);
		spriteMove.setTextureRect(IntRect(xBeginSprite, yBeginSprite, width, height));
		break;
	case DAMAGE:
		break;
	case HIT:
		spriteHit.setTexture(texture);
		spriteHit.setTextureRect(IntRect(xBeginSprite, yBeginSprite, width, height));
		break;
	case IDLE:
		spriteIdle.setTexture(texture);
		spriteIdle.setTextureRect(IntRect(xBeginSprite, yBeginSprite, width, height));
	}
}
