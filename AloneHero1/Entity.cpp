#include "Entity.h"

Entity::Entity(String F, double x, double y, double width, double height)
{
	file = F;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	image.loadFromFile("Images/" + F);
}

Entity::~Entity()
{
}
