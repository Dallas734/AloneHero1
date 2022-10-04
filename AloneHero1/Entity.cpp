#include "Entity.h"

Entity::Entity(double x, double y)
{
	this->x = x;
	this->y = y;
	this->currentFrame = 0;
}

void Entity::SetDirection(int direction)
{
	this->direction = direction;
}

int Entity::GetDirection()
{
	return this->direction;
}

void Entity::SetSpeed(int speed)
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

Sprite Entity::GetSprite()
{
	return this->spriteMove;
}

void Entity::SetSprite(String directory, Sprites spriteName, double x, double y, double width, double height)
{
	switch (spriteName)
	{
	case MOVE:
		image.loadFromFile("Images/" + directory);
		texture.loadFromImage(image);
		spriteMove.setTexture(texture);
		spriteMove.setTextureRect(IntRect(x, y, width, height));
		break;
	case DAMAGE:
		break;
	case HIT:
		break;
	}
}

Entity::~Entity()
{
}
