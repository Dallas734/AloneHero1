#include "Entity.h"

Entity::Entity(String F, double x, double y, double width, double height)
{
	file = F;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	image.loadFromFile("Images/" + F);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(width, height, width, height)); // Задаем спрайту один прямоугольник для вывода.
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

Sprite Entity::GetSprite()
{
	return this->sprite;
}

Entity::~Entity()
{
}
