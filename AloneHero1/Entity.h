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
		double speed; // ��������
		double dx, dy; // ���������
		double x, y; // ����������
		double width, height; // ������ � ������
		double currentFrame;

		String directory; // ��� ����������, ��� �������� ��������
		Sprite spriteMove; // ������ ��������
		Sprite spriteIdle; // ������ ���������� ���������
		Image image; // �������� ��� �������� ��������
		Texture texture; // �������� ��� �������� ��������
		int health; // ��������
		double strength; // ����
		
	public:
		Entity(double x, double y, double width, double height, double speed, int health, double strength);
		~Entity() {};
		virtual States Update(float time) = 0; // ������� ����������� ����������
		int Hit(float time, double width, double height, int frames, double strength, Directions direction); // ����
		void Damage(float time, double width, double height, int frames, double strength, Directions direction); // ��������� �����
		States Move(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction); // ��������
		States Idle(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction);
		void SetSpeed(double speed); // ���������� ��������
		double GetSpeed(); // �������� �������� ��������
		Sprite GetSprite(States spriteName); // ���������� ������
		void SetSprite(String fileName, States spriteName, double x, double y, double width, double height);

};

