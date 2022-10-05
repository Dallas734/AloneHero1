#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

enum Directions
{
	LEFT = 1,
	RIGHT = 2
 };

enum States
{
	RUN,
	HIT,
	DAMAGE,
	IDLE
};

class Entity
{
	protected:
		double speed; // ��������
		double dx, dy; // ���������
		double x, y; // ����������
		double width, height; // ������ � ������
		double currentFrame;

		String file; // ��� ����� � �����������
		Sprite spriteMove; // ������
		Sprite spriteIdle;
		Image image;
		Texture texture;
		int health; // ��������
		double strength; // ����
		
	public:
		Entity(double x, double y);
		virtual States Update(float time) = 0;
		virtual int Hit(double strength) = 0; 
		virtual void Damage(double strength) = 0;
		void SetSpeed(double speed);
		double GetSpeed();
		void SetCurrentFrame(int currentFrame);
		int GetCurrentFrame();
		Sprite GetSpriteMove();
		Sprite GetSpriteIdle();
		void SetSprite(String fileName, States spriteName, double x, double y, double width, double height);

		~Entity();
};

