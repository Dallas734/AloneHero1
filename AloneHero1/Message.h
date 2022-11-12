#pragma once
#include "Codes.h"
#include "entityfwd.h"

struct Message
{
	Codes code;
	int units;
	double x;
	double y;
	double dx;
	double dy;
	Entity* sender;

	Message(Codes code, int units, Entity* sender)
	{
		this->code = code;
		this->units = units;
		this->sender = sender;
	}

	Message(Codes code, int units, Entity* sender, double x, double y, double dx, double dy)
	{
		this->code = code;
		this->units = units;
		this->sender = sender;
		this->x = x;
		this->y = y;
		this->dx = dx;
		this->dy = dy;
	}
};