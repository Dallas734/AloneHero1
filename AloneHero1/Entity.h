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
		double bufWidth; // �������� ������ ��� ��������� �������� 
		double bufOfHit;
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
		Sprite spriteDamage;
		States state;
		Image image; // �������� ��� �������� ��������
		Texture texture; // �������� ��� �������� ��������
		Directions direction; // ����������� ��������
		
	public:
		Entity(double x, double y, double speed, int health, double strength);
		~Entity() {};
		virtual void Update(float time, RenderWindow& window, Level* level) = 0; // ������� ����������� ����������
		virtual States Fall(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level) = 0;
		void SetSpeed(double speed); // ���������� ��������
		double GetSpeed(); // �������� �������� ��������
		Sprite GetSprite(States spriteName); // ���������� ������
		void SetSprite(String fileName, States spriteName, double x, double y, double width, double height);
		States GetState();
		FloatRect getRect();
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

	protected:
		States Hit(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, double strength, double bufOfHit, Directions direction, RenderWindow& window, Level* level); // ����
		void Damage(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, double strength, Directions direction, RenderWindow& window, Level* level); // ��������� �����
		States Move(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level); // ��������
		States Idle(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level);
		virtual void CheckCollisionWithMap(double dx, double dy, Level* level, float time) = 0;
};

