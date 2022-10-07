#pragma once
#include "Entity.h"

class Skeleton : public Entity
{
	public:
		States Update(float time) override;
		// Методы Move, Idle... будут от Entity
		// Defense()
};

