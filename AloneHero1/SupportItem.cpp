#include "SupportItem.h"

void SupportItem::Update(float time, RenderWindow& window)
{
	image.loadFromFile(fileName);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(xBeginSprite, yBeginSprite, width, height));

	double beginY = y;

	if (y <= beginY + 10 && up)
	{
		y += 0.0001 * time;
	}
	else up = false;

	if (y >= beginY - 10 && up == false)
	{
		y += -0.0001 * time;
	}
	else up = true;

	sprite.setPosition(this->x, this->y);
}

bool SupportItem::GetUsed()
{
	return this->used;;
}
