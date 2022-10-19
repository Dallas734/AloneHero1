#pragma once
#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "tinyxml.h"
#include "Enemy.h"
#include "Skeleton.h"
#include "Player.h"
#include "Entity.h"

struct Object
{
public:
	//int GetPropertyInt(std::string name);//номер свойства объекта в нашем списке
	//float GetPropertyFloat(std::string name);
	//std::string GetPropertyString(std::string name);

	std::string name;//объ€вили переменную name типа string
	std::string type;//а здесь переменную type типа string
	sf::Rect<float> rect;//тип Rect с нецелыми значени€ми
	std::map<std::string, std::string> properties;//создаЄм ассоциатиный массив. ключ - строковый тип, значение - строковый

	sf::Sprite sprite;//объ€вили спрайт
};

struct Layer//слои
{
public:
	int opacity;//непрозрачность сло€
	std::vector<sf::Sprite> tiles;//закидываем в вектор тайлы
};

class Level//главный класс - уровень
{
private:
	Player* player;
	std::vector<Enemy> enemies;
	int width, height, tileWidth, tileHeight;//в tmx файле width height в начале,затем размер тайла
	int firstTileID;//получаем айди первого тайла
	std::string fileNameTMX;
	sf::Rect<float> drawingBounds;//размер части карты которую рисуем
	sf::Texture tilesetImage;//текстура карты
	std::vector<Object> objects;//массив типа ќбъекты, который мы создали
	std::vector<Layer> layers;
	bool LoadFromFile(std::string fileNameTMX);//возвращает false если не получилось загрузить
public:
	Level(String fileNameTMX)
	{
		//this->player = new Player(0, 0);
		//player->GetPlayerView().reset(FloatRect(0, 0, 640, 480));
		this->fileNameTMX = "Levels/" + fileNameTMX;
		LoadFromFile(this->fileNameTMX);
	};
	Object GetObject(std::string name);
	std::vector<Object> GetObjects(std::string name);//выдаем объект в наш уровень
	std::vector<Object> GetAllObjects();//выдаем все объекты в наш уровень
	void Draw(sf::RenderWindow& window, float time);//рисуем в окно
	sf::Vector2i GetTileSize();//получаем размер тайла
};
#endif
///////////////////////////////////////

