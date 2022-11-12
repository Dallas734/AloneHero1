#pragma once
#include "SupportItem.h"

class RedPotion : public SupportItem
{
	public:
		RedPotion(double x, double y, int improveUnits) : SupportItem(x, y, improveUnits)
		{
			this->xBeginSprite = 8;
			this->yBeginSprite = 231;
			this->width = 20;
			this->height = 22;
		};
		//void Improve(Player& player) override;
		~RedPotion() {};
};

