#include "Level.h"


//int Object::GetPropertyInt(std::string name)//���������� ����� �������� � ����� ������
//{
//	return atoi(properties[name].c_str());
//}
//
//float Object::GetPropertyFloat(std::string name)
//{
//	return strtod(properties[name].c_str(), NULL);
//}
//
//std::string Object::GetPropertyString(std::string name)//�������� ��� � ���� ������.����� �������
//{
//	return properties[name];
//}

bool Level::LoadFromFile(std::string filename)//���������-��������� � ������� ������ ��� ������ 
{
	TiXmlDocument levelFile(filename.c_str());//��������� ���� � TiXmlDocument

	// ��������� XML-�����
	if (!levelFile.LoadFile())//���� �� ������� ��������� �����
	{
		std::cout << "Loading level \"" << filename << "\" failed." << std::endl;//������ ������
		return false;
	}

	// �������� � ����������� map
	TiXmlElement* map;
	map = levelFile.FirstChildElement("map");

	// ������ �����: <map version="1.0" orientation="orthogonal"
	// width="10" height="10" tilewidth="34" tileheight="34">
	width = atoi(map->Attribute("width"));//��������� �� ����� ����� �� ��������
	height = atoi(map->Attribute("height"));//�� ��������, ������� �������� ��� ������ � 
	tileWidth = atoi(map->Attribute("tilewidth"));//������� ���������
	tileHeight = atoi(map->Attribute("tileheight"));

	// ����� �������� �������� � ������������� ������� �����
	TiXmlElement* tilesetElement;
	tilesetElement = map->FirstChildElement("tileset");
	firstTileID = atoi(tilesetElement->Attribute("firstgid"));

	// source - ���� �� �������� � ���������� image
	TiXmlElement* image;
	//image = tilesetElement->FirstChildElement("image");
	std::string imagepath = tilesetElement->Attribute("source");

	// �������� ��������� �������
	sf::Image img;

	if (!img.loadFromFile(imagepath))
	{
		std::cout << "Failed to load tile sheet." << std::endl;//���� �� ������� ��������� �������-������� ������ � �������
		return false;
	}


	img.createMaskFromColor(sf::Color(255, 255, 255));//��� ����� �����.������ ��� �����
	tilesetImage.loadFromImage(img);
	tilesetImage.setSmooth(false);//�����������

	// �������� ���������� �������� � ����� ��������
	int columns = tilesetImage.getSize().x / tileWidth;
	int rows = tilesetImage.getSize().y / tileHeight;

	// ������ �� ��������������� ����������� (TextureRect)
	std::vector<sf::Rect<int>> subRects;

	for (int y = 0; y < rows; y++)
		for (int x = 0; x < columns; x++)
		{
			sf::Rect<int> rect;

			rect.top = y * tileHeight;
			rect.height = tileHeight;
			rect.left = x * tileWidth;
			rect.width = tileWidth;

			subRects.push_back(rect);
		}

	// ������ �� ������
	TiXmlElement* layerElement;
	layerElement = map->FirstChildElement("layer");
	while (layerElement)
	{
		Layer layer;

		// ���� ������������ opacity, �� ������ ������������ ����, ����� �� ��������� �����������
		if (layerElement->Attribute("opacity") != NULL)
		{
			float opacity = strtod(layerElement->Attribute("opacity"), NULL);
			layer.opacity = 255 * opacity;
		}
		else
		{
			layer.opacity = 255;
		}

		//  ��������� <data> 
		TiXmlElement* layerDataElement;
		layerDataElement = layerElement->FirstChildElement("data");

		if (layerDataElement == NULL)
		{
			std::cout << "Bad map. No layer information found." << std::endl;
		}

		//  ��������� <tile> - �������� ������ ������� ����
		TiXmlElement* tileElement;
		tileElement = layerDataElement->FirstChildElement("tile");

		if (tileElement == NULL)
		{
			std::cout << "Bad map. No tile information found." << std::endl;
			return false;
		}

		int x = 0;
		int y = 0;

		int number = 0;

		while (tileElement)
		{
			/*number++;
			std::cout << number << "\n";*/
			int tileGID = atoi(tileElement->Attribute("gid"));
			int subRectToUse = tileGID - firstTileID;

			// ������������� TextureRect ������� �����
			if (subRectToUse >= 0)
			{
				sf::Sprite sprite;
				sprite.setTexture(tilesetImage);
				sprite.setTextureRect(subRects[subRectToUse]);
				sprite.setPosition(x * tileWidth, y * tileHeight);
				//sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

				layer.tiles.push_back(sprite);//���������� � ���� ������� ������
			}

			tileElement = tileElement->NextSiblingElement("tile");
			if (number == 2839)
			{
				std::cout << "?";
			}

			x++;
			if (x >= width)
			{
				x = 0;
				y++;
				if (y >= height)
					y = 0;
			}
		}

		layers.push_back(layer);

		layerElement = layerElement->NextSiblingElement("layer");
	}

	// ������ � ���������
	TiXmlElement* objectGroupElement;

	// ���� ���� ���� ��������
	if (map->FirstChildElement("objectgroup") != NULL)
	{
		objectGroupElement = map->FirstChildElement("objectgroup");
		while (objectGroupElement)
		{
			//  ��������� <object>
			TiXmlElement* objectElement;
			objectElement = objectGroupElement->FirstChildElement("object");

			while (objectElement)
			{
				// �������� ��� ������ - ���, ���, �������, � ��
				std::string objectType;
				if (objectElement->Attribute("type") != NULL)
				{
					objectType = objectElement->Attribute("type");
				}
				std::string objectName;
				if (objectElement->Attribute("name") != NULL)
				{
					objectName = objectElement->Attribute("name");
				}
				int x = atoi(objectElement->Attribute("x"));
				int y = atoi(objectElement->Attribute("y"));

				int width, height;

				sf::Sprite sprite;
				sprite.setTexture(tilesetImage);
				sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));
				sprite.setPosition(x, y);

				if (objectElement->Attribute("width") != NULL)
				{
					width = atoi(objectElement->Attribute("width"));
					height = atoi(objectElement->Attribute("height"));
				}
				else
				{
					width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
					height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;
					sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);
				}

				// ��������� �������
				Object object;
				object.name = objectName;
				object.type = objectType;
				object.sprite = sprite;

				sf::Rect <float> objectRect;
				objectRect.top = y;
				objectRect.left = x;
				objectRect.height = height;
				objectRect.width = width;
				object.rect = objectRect;

				// "����������" �������
				TiXmlElement* properties;
				properties = objectElement->FirstChildElement("properties");
				if (properties != NULL)
				{
					TiXmlElement* prop;
					prop = properties->FirstChildElement("property");
					if (prop != NULL)
					{
						while (prop)
						{
							std::string propertyName = prop->Attribute("name");
							std::string propertyValue = prop->Attribute("value");

							object.properties[propertyName] = propertyValue;

							prop = prop->NextSiblingElement("property");
						}
					}
				}


				objects.push_back(object);

				objectElement = objectElement->NextSiblingElement("object");
			}
			objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
		}
	}
	else
	{
		std::cout << "No object layers found..." << std::endl;
	}

	// ���� ������
	Object playerObject = GetObject("Player");
	if (player == nullptr)
	{
		this->player = new Player(playerObject.rect.left, playerObject.rect.top);
		view.reset(FloatRect(0, 0, 1200, 800));
	}

	FillEnemy("Skeleton");
	FillEnemy("Goblin");
	FillEnemy("Mushroom");

	return true;
}

Object Level::GetObject(std::string name)
{
	// ������ ������ ������ � �������� ������
	for (int i = 0; i < objects.size(); i++)
		if (objects[i].name == name)
			return objects[i];
}

std::vector<Object> Level::GetObjects(std::string name)
{
	// ��� ������� � �������� ������
	std::vector<Object> vec;
	for (int i = 0; i < objects.size(); i++)
		if (objects[i].name == name)
			vec.push_back(objects[i]);

	return vec;
}


std::vector<Object> Level::GetAllObjects()
{
	return objects;
};


sf::Vector2i Level::GetTileSize()
{
	return sf::Vector2i(tileWidth, tileHeight);
}

int Level::GetWidth()
{
	return this->width;
}

int Level::GetHeight()
{
	return this->height;
}

void Level::CheckCollision(double dx, double dy, Entity* entity)
{
	std::vector<Object> obj = this->GetAllObjects();
	for (int i = 0; i < obj.size(); i++)
	{
		if (entity->getRect().intersects(obj[i].rect))
		{
			if (obj[i].name == "Solid" )
			{
				if (dy > 0) {
					entity->SetY(obj[i].rect.top - entity->GetHeight());
					entity->SetDY(0); // ��� ��������
					if (typeid(*(entity)) == typeid(Enemy))
					{
						entity->SetState(RUN);
						//entity->SetState(HIT);
					}
					else
					{
						entity->SetState(IDLE);
					}
					entity->SetOnground(true);
				}
				if (dy < 0) 
				{ 
					entity->SetY(obj[i].rect.top + obj[i].rect.height); /*this->dy = 0;*/ std::cout << "I'm minus!"; 
				}
				if (dx > 0) 
				{ 
					entity->SetX(obj[i].rect.left - entity->GetWidth()); 
				}
				if (dx < 0)
				{ 
					entity->SetX(obj[i].rect.left + obj[i].rect.width);
				}
			}
			
			if (obj[i].name == "enemyBarier"  && typeid(*(entity)) == typeid(Enemy))
			{
			if (entity->GetDirection() == RIGHT) entity->SetDirection(LEFT);
			else entity->SetDirection(RIGHT);
			}
		}

		//////////////////////////////////////////////////////////////////////
		
		// ���� ���� ������������ � �������
	
		if (typeid(*(entity)) == typeid(Enemy))
		{
			Enemy* enemy = (Enemy*)entity;
			if (enemy->getRect().intersects(player->getRect()) && enemy->collisionWithPlayer == false && player->GetDY() == 0 && player->GetState() != HIT)
			{
				enemy->collisionWithPlayer = true;
				entity->SetState(HIT);
				player->SetState(DAMAGE);
				//player->SetDamage(entity->GetStrength());
				return;
			}
			else if (enemy->collisionWithPlayer && entity->GetState() == RUN && player->GetDY() == 0)
			{
				if (!entity->getRect().intersects(player->getRect()))
				{
					enemy->collisionWithPlayer = false;
				}
				if (enemy->collisionWithPlayer && player->GetState() != RUN && player->GetState() != HIT)
				{
					player->SetState(IDLE);
				}
				return;
			}
		}
		////////////////////////////////////////////////////////////////////////

		// ���� ����� ���������� ����� ��� �����.
		////////////////////////////////////////////////////////////////////////

		if (typeid(*(entity)) == typeid(Player))
		{
			for (int i = 0; i < enemies.size(); i++)
			{
				Enemy* enemy = &enemies[i];
				if (player->getHitRect().intersects(enemy->getRect()) && enemy->collisionWithPlayer == false && player->GetDY() == 0 && player->GetState() == HIT && enemy->GetState() != HIT && ((player->GetDirection() == LEFT && player->GetX() > enemy->GetX()) || (player->GetDirection() == RIGHT && player->GetX() < enemy->GetX())))
				{
					enemy->collisionWithPlayer = true;
					enemy->SetState(DAMAGE);
					//enemy->SetDamage(entity->GetStrength());
					return;
				}
				else if (enemy->collisionWithPlayer && player->GetState() != HIT && player->GetDY() == 0 && enemy->GetState() == DAMAGE)
				{
					if (!player->getHitRect().intersects(enemy->getRect()))
					{
						enemy->collisionWithPlayer = false;
					}
					if (player->GetState() != RUN && player->GetState() != HIT)
					{
						enemy->SetState(RUN);
						enemy->collisionWithPlayer = false;
					}
					return;
				}
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////
	}
}

bool Level::GetCollisionWithPlayer()
{
	return this->collisionWithPlayer;
}

void Level::ViewOnPlayer(Player* player)
{
	double tempX = player->GetX();
	double tempY = player->GetY();

	view.setSize(this->sizeOfView.x, this->sizeOfView.y);

	// �������� ������ ������� 
	if (tempX + this->sizeOfView.x / 2 >= this->width * this->tileWidth)
	{
		tempX = this->width * this->tileWidth - this->sizeOfView.x / 2;
	}

	// �������� ����� �������
	if (tempX - this->sizeOfView.x / 2 <= 0)
	{
		tempX = this->sizeOfView.x / 2;
	}

	// �������� ������ �������
	if (tempY + this->sizeOfView.y / 2 >= this->height * this->tileHeight)
	{
		tempY = this->height * this->tileHeight - this->sizeOfView.y / 2;
	}

	// �������� ������� �������
	if (tempY - this->sizeOfView.y / 2 <= 0)
	{
		tempY = this->sizeOfView.y / 2;
	}

	view.setCenter(tempX, tempY);
}

void Level::FillEnemy(std::string nameOfEnemy)
{
	std::vector<Object> enemyObjects = GetObjects(nameOfEnemy);
	for (int i = 0; i < enemyObjects.size(); i++)
	{
		Enemy* enemy = nullptr;
		if (nameOfEnemy == "Mushroom") enemy = new Mushroom(enemyObjects[i].rect.left, enemyObjects[i].rect.top, 0.08, 100, 50);
		else if (nameOfEnemy == "Skeleton") enemy = new Skeleton(enemyObjects[i].rect.left, enemyObjects[i].rect.top, 0.08, 300, 50);
		else if (nameOfEnemy == "Goblin") enemy = new Goblin(enemyObjects[i].rect.left, enemyObjects[i].rect.top, 0.08, 200, 50);
		this->enemies.push_back(*enemy);	
	}
}

void Level::Draw(sf::RenderWindow& window, float time)
{
	player->Update(time, window, this);
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i].Update(time, window, this);
		//window.draw(enemies[i].GetSprite(enemies[i].GetState()));
		// ?????? ������������ ����� ��������
	}

	// ���������
	window.setView(view);

	window.clear();

	// ������ ��� ����� (������� �� ������!)
	for (int layer = 0; layer < layers.size(); layer++)
		for (int tile = 0; tile < layers[layer].tiles.size(); tile++)
			window.draw(layers[layer].tiles[tile]);

	window.draw(player->GetSprite(player->GetState()));
	for (int i = 0; i < enemies.size(); i++)
	{
		window.draw(enemies[i].GetSprite(enemies[i].GetState()));
	}
	window.display();
}


