#include "Entity.h"

Entity::Entity(double x, double y)
{
	this->x = x;
	this->y = y;
	currentFrame = 0;
	dx = 0;
	dy = 0;
	speed = 0;
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
		break;
	case IDLE:
		return spriteIdle;
		break;
	}
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
