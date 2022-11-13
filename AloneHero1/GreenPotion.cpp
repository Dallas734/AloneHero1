#include "GreenPotion.h"

void GreenPotion::Improve(Entity& entity)
{
	Message* message = new Message(SPEED_UP, improveUnits, nullptr);
	entity.GetMessage(*message);
	used = true;
}
