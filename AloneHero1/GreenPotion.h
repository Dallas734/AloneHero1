#pragma once
#include "SupportItem.h"

class GreenPotion : public SupportItem
{
	public:
		GreenPotion(double x, double y, int improveUnits) : SupportItem(x, y, improveUnits)
		{
			this->xBeginSprite = 102;
			this->yBeginSprite = 231;
			this->width = 20;
			this->height = 22;
		};
		~GreenPotion() {};
		//void Improve(Player& player) override;
};

