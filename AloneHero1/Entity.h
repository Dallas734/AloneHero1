#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

enum Directions
{
	LEFT = 1,
	RIGHT = 2
 };

enum Sprites
{
	MOVE,
	HIT,
	DAMAGE
};

class Entity
{
	protected:
		double speed; // Скорость
		double dx, dy; // Ускорение
		double x, y; // Координаты
		double width, height; // Ширина и высота
		int direction; // Направление движения
		String file; // Имя файла с расширением
		Sprite spriteMove; // Спрайт
		Image image;
		Texture texture;
		int health; // Здоровье
		double strength; // Сила
		double currentFrame;

	public:
		Entity(double x, double y);
		virtual void Move(float time, String F, double x, double y, double width, double height) = 0;
		virtual int Hit(double strength) = 0; 
		virtual void Damage(double strength) = 0;
		void SetDirection(int direction);
		int GetDirection();
		void SetSpeed(int speed);
		double GetSpeed();
		void SetCurrentFrame(int currentFrame);
		int GetCurrentFrame();
		Sprite GetSprite();
		void SetSprite(String fileName, Sprites spriteName, double x, double y, double width, double height);

		~Entity();
};

