#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

enum Directions
{
	LEFT = 1,
	RIGHT = 2
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
		Image image; // Изображение
		Texture texture; // Текстура
		Sprite sprite; // Спрайт
		int health; // Здоровье
		double strength; // Сила

	public:
		Entity(String F, double x, double y, double width, double height);
		virtual void Move(float time) = 0;
		virtual int Hit(double strength) = 0; 
		virtual void Damage(double strength) = 0;
		virtual void Walk() = 0;
		virtual void Update(float time) = 0;
		void SetDirection(int direction);
		int GetDirection();
		void SetSpeed(int speed);
		double GetSpeed();
		Sprite GetSprite();
		~Entity();
};

