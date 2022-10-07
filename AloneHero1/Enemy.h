#pragma once
#include "Entity.h"

class Enemy : public Entity
{
	public:
		Enemy(double x, double y, double width, double height, double speed, int health, double strength) : Entity(x, y, width, height, speed, health, strength) {};
		~Enemy() {};
		States Update(float time) override;
		/*int Hit(float time, double width, double height, int frames, double strength, Directions direction) override;
		void Damage(float time, double width, double height, int frames, double strength, Directions direction) override;*/
		// Move() ? Может у всех одинаковый, просто добавить количество кадров
		// Idle() тоже самое, Damage(), Hit() тоже


};

