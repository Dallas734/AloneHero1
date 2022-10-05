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
		Entity(double x, double y);
		~Entity() {};
		virtual States Update(float time) = 0; // ������� ����������� ����������
		virtual int Hit(double strength) = 0; // ����
		virtual void Damage(double strength) = 0; // ��������� �����
		virtual States Move(float time, Directions direction) = 0; // ��������
		virtual States Idle(float time) = 0;
		void SetSpeed(double speed); // ���������� ��������
		double GetSpeed(); // �������� �������� ��������
		Sprite GetSprite(States spriteName); // ���������� ������
		void SetSprite(String fileName, States spriteName, double x, double y, double width, double height);

};

