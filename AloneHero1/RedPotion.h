#pragma once
#include "SupportItem.h"

class RedPotion : public SupportItem
{
	public:
		RedPotion(double x, double y, double width, double height, int regenerationUnits, String directory) : SupportItem(x, y, width, height, regenerationUnits, directory) {};
		void Improve(Player player) override;
};

