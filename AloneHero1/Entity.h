#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

enum States
{
	RUN,
	HIT,
	DAMAGE,
	IDLE
};

enum Directions
{
	RIGHT,
	LEFT
};

class Entity
{
	protected:
		double speed; // Скорость
		double dx, dy; // Ускорение
		double x, y; // Координаты
		double width, height; // Ширина и высота
		double currentFrame;

		String directory; // Имя директории, где хранятся анимации
		Sprite spriteMove; // Спрайт движения
		Sprite spriteIdle; // Спрайт статичного состояния
		Image image; // Картинка для создания спрайтов
		Texture texture; // Текстура для создания спрайтов
		int health; // Здоровье
		double strength; // Сила
		
	public:
		Entity(double x, double y);
		~Entity() {};
		virtual States Update(float time) = 0; // Функция покадрового обновления
		virtual int Hit(double strength) = 0; // Удар
		virtual void Damage(double strength) = 0; // Получение урона
		virtual States Move(float time, Directions direction) = 0; // Движение
		virtual States Idle(float time) = 0;
		void SetSpeed(double speed); // Установить скорость
		double GetSpeed(); // Получить значение скорости
		Sprite GetSprite(States spriteName); // Возвращает спрайт
		void SetSprite(String fileName, States spriteName, double x, double y, double width, double height);

};

