#pragma once

#include <SFML/Graphics.hpp>
#include "levelfwd.h"
#include "map"

using namespace sf;
using namespace std;

enum States
{
	RUN,
	HIT,
	DAMAGE,
	IDLE,
	JUMP,
	FALL,
	DEATH
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
		double bufWidth; // Буферная ширина для вырезания спрайтов 
		double bufOfHit;
		double currentFrame; // Текущий кадр
		int health; // Здоровье
		double strength; // Сила
		double damage; // Полученный урон
		bool onGround;

		double xBeginSprite;
		double yBeginSprite;
		double widthOfHit;
		double heightOfHit;
		map <States, int> countFrames;
		double xBeginSpriteHit;
		double yBeginSpriteHit;

		String directory; // Имя директории, где хранятся анимации
		map <States, Sprite> sprites; // Спрайты
		States state;
		Image image; // Картинка для создания спрайтов
		Texture texture; // Текстура для создания спрайтов
		Directions direction; // Направление движения
		
	public:
		Entity(double x, double y, double speed, int health, double strength);
		~Entity() {};
		virtual void Update(float time, RenderWindow& window, Level* level) = 0; // Функция покадрового обновления
		virtual States Fall(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level) = 0;
		void SetSpeed(double speed); // Установить скорость
		double GetSpeed(); // Получить значение скорости
		Sprite GetSprite(States spriteName); // Возвращает спрайт
		void SetSprite(String fileName, States spriteName, double x, double y, double width, double height);
		States GetState();
		FloatRect getRect();
		FloatRect getHitRect();
		double GetDX();
		double GetDY();
		double GetX();
		double GetY();
		void SetX(double x);
		void SetY(double y);
		void SetDX(double dx);
		void SetDY(double dy);
		void SetState(States state);
		bool GetOnGround();
		void SetOnground(bool onGround);
		Directions GetDirection();
		void SetDirection(Directions direction);
		double GetWidth();
		double GetHeight();
		void SetDamage(double damage);
		double GetStrength();

	protected:
		States Hit(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, double bufOfHit, Directions direction, RenderWindow& window, Level* level); // Удар
		States Damage(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, double damage, Directions direction, RenderWindow& window, Level* level); // Получение урона
		States Move(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level); // Движение
		States Idle(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level); // Бездействие
		States Death(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level); // Смерть
};

