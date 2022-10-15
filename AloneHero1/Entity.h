#pragma once

#include <SFML/Graphics.hpp>
#include "levelfwd.h"

using namespace sf;

enum States
{
	RUN,
	HIT,
	DAMAGE,
	IDLE,
	JUMP,
	FALL
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
		double currentFrame; // Текущий кадр
		int health; // Здоровье
		double strength; // Сила
		bool onGround;

		String directory; // Имя директории, где хранятся анимации
		Sprite spriteMove; // Спрайт движения
		Sprite spriteIdle; // Спрайт статичного состояния
		Sprite spriteHit; // Спрайт удара
		Sprite spriteJump;
		Sprite spriteFall;
		States state;
		Image image; // Картинка для создания спрайтов
		Texture texture; // Текстура для создания спрайтов
		Directions direction; // Направление движения
		
	public:
		Entity(double x, double y, double width, double height, double speed, int health, double strength);
		~Entity() {};
		virtual void Update(float time, RenderWindow& window, Level* level) = 0; // Функция покадрового обновления
		States Hit(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, double strength, Directions direction, RenderWindow& window); // Удар
		void Damage(float time, double width, double height, int frames, double strength, Directions direction); // Получение урона
		States Move(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level); // Движение
		States Idle(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level);
		void SetSpeed(double speed); // Установить скорость
		double GetSpeed(); // Получить значение скорости
		Sprite GetSprite(States spriteName); // Возвращает спрайт
		void SetSprite(String fileName, States spriteName, double x, double y, double width, double height);
		States GetState();
		FloatRect getRect();
		virtual void CheckCollisionWithMap(double dx, double dy, Level* level, float time) = 0;
};

