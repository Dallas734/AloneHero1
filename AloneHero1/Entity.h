#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

enum Directions
{
	LEFT = 1,
	RIGHT = 2
 };

enum States
{
	RUN,
	HIT,
	DAMAGE,
	IDLE
};

class Entity
{
	protected:
		double speed; // Скорость
		double dx, dy; // Ускорение
		double x, y; // Координаты
		double width, height; // Ширина и высота
		double currentFrame;

		String file; // Имя файла с расширением
		Sprite spriteMove; // Спрайт
		Sprite spriteIdle;
		Image image;
		Texture texture;
		int health; // Здоровье
		double strength; // Сила
		
	public:
		Entity(double x, double y);
		virtual States Update(float time) = 0;
		virtual int Hit(double strength) = 0; 
		virtual void Damage(double strength) = 0;
		void SetSpeed(double speed);
		double GetSpeed();
		void SetCurrentFrame(int currentFrame);
		int GetCurrentFrame();
		Sprite GetSpriteMove();
		Sprite GetSpriteIdle();
		void SetSprite(String fileName, States spriteName, double x, double y, double width, double height);

		~Entity();
};

