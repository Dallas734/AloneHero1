#include "GreenPotion.h"

void GreenPotion::Improve(Player player)
{
	player.SpeedUp(this->regenerationUnits);
}
