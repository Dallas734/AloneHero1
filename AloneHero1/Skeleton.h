#pragma once
#include "Entity.h"

class Skeleton : public Entity
{
	public:
		States Update(float time) override;
		// ������ Move, Idle... ����� �� Entity
		// Defense()
};

