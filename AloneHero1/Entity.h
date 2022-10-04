#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

enum Directions
{
	LEFT = 1,
	RIGHT = 2
 };

enum Sprites
{
	MOVE,
	HIT,
	DAMAGE
};

class Entity
{
	protected:
		double speed; // ��������
		double dx, dy; // ���������
		double x, y; // ����������
		double width, height; // ������ � ������
		int direction; // ����������� ��������
		String file; // ��� ����� � �����������
		Sprite spriteMove; // ������
		Image image;
		Texture texture;
		int health; // ��������
		double strength; // ����
		double currentFrame;

	public:
		Entity(double x, double y);
		virtual void Move(float time, String F, double x, double y, double width, double height) = 0;
		virtual int Hit(double strength) = 0; 
		virtual void Damage(double strength) = 0;
		void SetDirection(int direction);
		int GetDirection();
		void SetSpeed(int speed);
		double GetSpeed();
		void SetCurrentFrame(int currentFrame);
		int GetCurrentFrame();
		Sprite GetSprite();
		void SetSprite(String fileName, Sprites spriteName, double x, double y, double width, double height);

		~Entity();
};

