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
	//int GetPropertyInt(std::string name);//����� �������� ������� � ����� ������
	//float GetPropertyFloat(std::string name);
	//std::string GetPropertyString(std::string name);

	std::string name;//�������� ���������� name ���� string
	std::string type;//� ����� ���������� type ���� string
	sf::Rect<float> rect;//��� Rect � �������� ����������
	std::map<std::string, std::string> properties;//������ ������������ ������. ���� - ��������� ���, �������� - ���������

	sf::Sprite sprite;//�������� ������
};

struct Layer//����
{
public:
	int opacity;//�������������� ����
	std::vector<sf::Sprite> tiles;//���������� � ������ �����
};

class Level//������� ����� - �������
{
private:
	Player* player;
	std::vector<Enemy> enemies;
	int width, height, tileWidth, tileHeight;//� tmx ����� width height � ������,����� ������ �����
	int firstTileID;//�������� ���� ������� �����
	std::string fileNameTMX;
	sf::Rect<float> drawingBounds;//������ ����� ����� ������� ������
	sf::Texture tilesetImage;//�������� �����
	std::vector<Object> objects;//������ ���� �������, ������� �� �������
	std::vector<Layer> layers;
	bool LoadFromFile(std::string fileNameTMX);//���������� false ���� �� ���������� ���������
public:
	Level(String fileNameTMX)
	{
		//this->player = new Player(0, 0);
		//player->GetPlayerView().reset(FloatRect(0, 0, 640, 480));
		this->fileNameTMX = "Levels/" + fileNameTMX;
		LoadFromFile(this->fileNameTMX);
	};
	Object GetObject(std::string name);
	std::vector<Object> GetObjects(std::string name);//������ ������ � ��� �������
	std::vector<Object> GetAllObjects();//������ ��� ������� � ��� �������
	void Draw(sf::RenderWindow& window, float time);//������ � ����
	sf::Vector2i GetTileSize();//�������� ������ �����
};
#endif
///////////////////////////////////////

