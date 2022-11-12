#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace sf;

class SupportItem
{
protected:
	double x, y;
	Image image;
	Texture  texture;
	Sprite sprite;
	String fileName;
	double width, height;
	double xBeginSprite, yBeginSprite;
	// время действия Time
	double improveUnits;
	bool up;
	bool used;

public:
	SupportItem(double x, double y, int improveUnits)
	{
		this->x = x;
		this->y = y;
		this->improveUnits = improveUnits;
		this->fileName = "Images/Potions/PotionsPack1.png";
		up = true;
		used = false;
	};
	~SupportItem() {};
	void Update(float time, RenderWindow& window);
	//virtual void Improve(Player& player);
	bool GetUsed();

};

