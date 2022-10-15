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
		double speed; // ��������
		double dx, dy; // ���������
		double x, y; // ����������
		double width, height; // ������ � ������
		double currentFrame; // ������� ����
		int health; // ��������
		double strength; // ����
		bool onGround;

		String directory; // ��� ����������, ��� �������� ��������
		Sprite spriteMove; // ������ ��������
		Sprite spriteIdle; // ������ ���������� ���������
		Sprite spriteHit; // ������ �����
		Sprite spriteJump;
		Sprite spriteFall;
		States state;
		Image image; // �������� ��� �������� ��������
		Texture texture; // �������� ��� �������� ��������
		Directions direction; // ����������� ��������
		
	public:
		Entity(double x, double y, double width, double height, double speed, int health, double strength);
		~Entity() {};
		virtual void Update(float time, RenderWindow& window, Level* level) = 0; // ������� ����������� ����������
		States Hit(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, double strength, Directions direction, RenderWindow& window); // ����
		void Damage(float time, double width, double height, int frames, double strength, Directions direction); // ��������� �����
		States Move(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level); // ��������
		States Idle(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level);
		void SetSpeed(double speed); // ���������� ��������
		double GetSpeed(); // �������� �������� ��������
		Sprite GetSprite(States spriteName); // ���������� ������
		void SetSprite(String fileName, States spriteName, double x, double y, double width, double height);
		States GetState();
		FloatRect getRect();
		virtual void CheckCollisionWithMap(double dx, double dy, Level* level, float time) = 0;
};

