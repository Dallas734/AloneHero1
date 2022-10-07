#pragma once
#include "SupportItem.h"

class RedPotion : public SupportItem
{
	public:
		RedPotion(double x, double y, double width, double height, int regenerationUnits, String fileName) : SupportItem(x, y, width, height, regenerationUnits, fileName) {};
		void Improve(Player player) override;
};

