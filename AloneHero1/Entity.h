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
		Entity(double x, double y, double width, double height, double speed, int health, double strength);
		~Entity() {};
		virtual States Update(float time) = 0; // Функция покадрового обновления
		int Hit(float time, double width, double height, int frames, double strength, Directions direction); // Удар
		void Damage(float time, double width, double height, int frames, double strength, Directions direction); // Получение урона
		States Move(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction); // Движение
		States Idle(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction);
		void SetSpeed(double speed); // Установить скорость
		double GetSpeed(); // Получить значение скорости
		Sprite GetSprite(States spriteName); // Возвращает спрайт
		void SetSprite(String fileName, States spriteName, double x, double y, double width, double height);

};

