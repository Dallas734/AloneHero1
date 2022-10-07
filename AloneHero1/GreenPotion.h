#pragma once
#include "SupportItem.h"

class GreenPotion : public SupportItem
{
	public:
		GreenPotion(double x, double y, double width, double height, int improveUnits, String directory) : SupportItem(x, y, width, height, improveUnits, directory) {};
		void Improve(Player player) override;
};

