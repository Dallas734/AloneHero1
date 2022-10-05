#include "Entity.h"

Entity::Entity(double x, double y)
{
	this->x = x;
	this->y = y;
	currentFrame = 0;
	dx = 0;
	dy = 0;
}

void Entity::SetSpeed(double speed)
{
	this->speed = speed;
}

double Entity::GetSpeed()
{
	return this->speed;
}

void Entity::SetCurrentFrame(int currentFrame)
{
	this->currentFrame = currentFrame;
}

int Entity::GetCurrentFrame()
{
	return this->currentFrame;
}

Sprite Entity::GetSpriteMove()
{
	return this->spriteMove;
}

Sprite Entity::GetSpriteIdle()
{
	return this->spriteIdle;
}

States Entity::Update(float time)
{
	States state = RUN;

	x += dx * time;
	y += dy * time;

	currentFrame += time * 0.005;
	if (this->currentFrame > 8) this->currentFrame -= 8;
	if (dx > 0) spriteMove.setTextureRect(IntRect(160 * int(currentFrame), 0, 160, 111));
	// if (dx < 0)

	spriteMove.setPosition(x, y);

	return state;
}

void Entity::SetSprite(String directory, States spriteName, double x, double y, double width, double height)
{
	image.loadFromFile("Images/" + directory);
	texture.loadFromImage(image);

	switch (spriteName)
	{
	case RUN:
		spriteMove.setTexture(texture);
		spriteMove.setTextureRect(IntRect(x, y, width, height));
		break;
	case DAMAGE:
		break;
	case HIT:
		break;
	case IDLE:
		spriteIdle.setTexture(texture);
		spriteIdle.setTextureRect(IntRect(x, y, width, height));
	}
}

Entity::~Entity()
{
}
