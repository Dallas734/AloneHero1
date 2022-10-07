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
	// время действия Time
	double regenerationUnits;
public:
	SupportItem(double x, double y, double width, double height, int regenerationUnits, String directory);
	~SupportItem() {};
	virtual void Improve(Player player) = 0;
};

