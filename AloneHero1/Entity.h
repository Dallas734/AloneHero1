#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

enum Directions
{
	LEFT = 1,
	RIGHT = 2
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
		Image image; // �����������
		Texture texture; // ��������
		Sprite sprite; // ������
		int health; // ��������
		double strength; // ����

	public:
		Entity(String F, double x, double y, double width, double height);
		virtual void Move(float time) = 0;
		virtual int Hit(double strength) = 0; 
		virtual void Damage(double strength) = 0;
		virtual void Walk() = 0;
		virtual void Update(float time) = 0;
		void SetDirection(int direction);
		int GetDirection();
		void SetSpeed(int speed);
		double GetSpeed();
		Sprite GetSprite();
		~Entity();
};

