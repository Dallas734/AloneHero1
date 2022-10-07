#include "RedPotion.h"

void RedPotion::Improve(Player player)
{
	player.HelthUP(this->regenerationUnits);
}
