#include "SupportItem.h"

SupportItem::SupportItem(double x, double y, double width, double height, int regenerationUnits, String fileName)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->regenerationUnits = regenerationUnits;
	this->fileName = fileName;
	this->image.loadFromFile("Images/SupportItems/" + fileName);
	this->texture.loadFromImage(image);
	this->sprite.setTextureRect(IntRect(x, y, width, height));
}
