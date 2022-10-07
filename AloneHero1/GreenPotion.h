#pragma once
#include "SupportItem.h"

class GreenPotion : public SupportItem
{
	public:
		GreenPotion(double x, double y, double width, double height, int improveUnits, String fileName) : SupportItem(x, y, width, height, improveUnits, fileName) {};
		void Improve(Player player) override;
};

