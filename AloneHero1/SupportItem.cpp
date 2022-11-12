#include "SupportItem.h"

void SupportItem::Update(float time, RenderWindow& window)
{
	image.loadFromFile(fileName);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(xBeginSprite, yBeginSprite, width, height));

	if (y <= beginY + 10 && up == false)
	{
		y += 0.01 * time;
	}
	else if (y >= beginY + 10) up = true;

	if (y >= beginY - 10 && up == true)
	{
		y += -0.01 * time;
	}
	else if (y <= beginY - 10) up = false;

	sprite.setPosition(this->x, this->y);
}

bool SupportItem::GetUsed()
{
	return this->used;;
}

Sprite SupportItem::GetSprite()
{
	return this->sprite;
}
