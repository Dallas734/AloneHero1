#include "SupportItem.h"

SupportItem::SupportItem(double x, double y, double width, double height, int regenerationUnits, String directory)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->regenerationUnits = regenerationUnits;
	this->directory = directory;
	this->image.loadFromFile(directory);
	this->texture.loadFromImage(image);
	this->sprite.setTextureRect(IntRect(x, y, width, height));
}
