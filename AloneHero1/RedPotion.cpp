#include "RedPotion.h"

void RedPotion::Improve(Entity& entity)
{
	Message* message = new Message(HEALTH_UP, improveUnits, nullptr);
	entity.GetMessage(*message);
	used = true;
}