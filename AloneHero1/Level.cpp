#include "Level.h"
#include "Game.h"


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

	FillSupportItem("GreenPotion");
	FillSupportItem("RedPotion");

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

void Level::FillSupportItem(std::string nameOfSupportItem)
{
	std::vector<Object> supportObjects = GetObjects(nameOfSupportItem);
	for (int i = 0; i < supportObjects.size(); i++)
	{
		SupportItem* supportItem;
		if (nameOfSupportItem == "GreenPotion") supportItem = new GreenPotion(supportObjects[i].rect.left, supportObjects[i].rect.top, 0.1);
		else if (nameOfSupportItem == "RedPotion") supportItem = new RedPotion(supportObjects[i].rect.left, supportObjects[i].rect.top, 20);
		this->supportItems.push_back(supportItem);
	}
}

void Level::GetMessage(Message& message)
{
	Message* messageToEnemy = nullptr;
	Message* messageToPlayer = nullptr;
	Message* messageToSomeone = nullptr;
	Message* messageToItem = nullptr;
	std::vector<Object> obj = this->GetAllObjects();

	//	����� �������� ������������ ��� ������
	if (message.code == RUN_C)
	{
		for (int i = 0; i < obj.size(); i++)
		{
			if (message.sender->getRect().intersects(obj[i].rect))
			{
				if (obj[i].name == "Solid")
				{
					if (message.dy > 0) {
						messageToSomeone = new Message(FALL_C, 0, nullptr, 0, obj[i].rect.top - message.sender->GetHeight(), 0, 0);
						message.sender->GetMessage(*messageToSomeone);
					}
					if (message.dy < 0)
					{
						messageToSomeone = new Message(JUMP_C, 0, nullptr, 0, obj[i].rect.top + obj[i].rect.height, 0, 0);
						message.sender->GetMessage(*messageToSomeone);
					}
					if (message.dx > 0)
					{
						messageToSomeone = new Message(CHANGE_X, 0, nullptr, obj[i].rect.left - message.sender->GetWidth(), 0, 0, 0);
						message.sender->GetMessage(*messageToSomeone);
					}
					if (message.dx < 0)
					{
						messageToSomeone = new Message(CHANGE_X, 0, nullptr, obj[i].rect.left + obj[i].rect.width, 0, 0, 0);
						message.sender->GetMessage(*messageToSomeone);
					}
				}

				if (obj[i].name == "enemyBarier" && typeid(*(message.sender)) == typeid(Enemy))
				{
					messageToEnemy = new Message(ENEMY_BARIER, 0, nullptr);
					message.sender->GetMessage(*messageToEnemy);
				}
			}
		}
	}

	// �����
	if (typeid(*(message.sender)) == typeid(Player))
	{
		if (message.code == HIT_C)
		{
			for (int i = 0; i < enemies.size(); i++)
			{
				Enemy* enemy = &enemies[i];
				if (player->getHitRect().intersects(enemy->getRect()) && enemy->collisionWithPlayer == false && player->GetDY() == 0 && player->GetState() == HIT && enemy->GetState() != HIT && ((player->GetDirection() == LEFT && player->GetX() > enemy->GetX()) || (player->GetDirection() == RIGHT && player->GetX() < enemy->GetX())))
				{
					messageToEnemy = new Message(DAMAGE_C, player->GetStrength(), nullptr);
					enemy->GetMessage(*messageToEnemy);
					return;
				}
				else if (enemy->collisionWithPlayer && player->GetState() != HIT && player->GetDY() == 0 && enemy->GetState() == DAMAGE)
				{
					messageToEnemy = new Message(RUN_C, 0, nullptr);
					enemy->GetMessage(*messageToEnemy);
					return;
				}
			}
		}

		if (message.code == RUN_C)
		{
			for (int i = 0; i < supportItems.size(); i++)
			{
				SupportItem* supportItem = supportItems[i];
				if (player->getRect().intersects(supportItems[i]->getRect()))
				{
					messageToItem = new Message(IMPROVE_STATS, 0, player);
					supportItem->GetMessage(*messageToItem);
				}
			}
		}
	}

	//std::cout << typeid(*(message.sender)).name();
	// ����
	if (typeid(*(message.sender)) == typeid(Enemy))
	{
		Enemy* enemy = (Enemy*)message.sender;
		if (message.code == RUN_C)
		{
			if (enemy->getRect().intersects(player->getRect()))
			{
				int a = 0;
			}

			if (enemy->getRect().intersects(player->getRect()) && enemy->collisionWithPlayer == false && player->GetDY() == 0 && player->GetState() != HIT)
			{
				messageToEnemy = new Message(HIT_C, 0, nullptr);
				messageToPlayer = new Message(DAMAGE_C, enemy->GetStrength(), nullptr);
				enemy->GetMessage(*messageToEnemy);
				player->GetMessage(*messageToPlayer);
				return;
			}
			else if (enemy->collisionWithPlayer && enemy->GetState() == RUN && player->GetDY() == 0)
			{
				if (!enemy->getRect().intersects(player->getRect()))
				{
					messageToEnemy = new Message(RUN_C, 0, nullptr);
					enemy->GetMessage(*messageToEnemy);
					/*enemy->collisionWithPlayer = false;*/
				}
				if (enemy->collisionWithPlayer && player->GetState() != RUN && player->GetState() != HIT)
				{
					messageToPlayer = new Message(IDLE_C, 0, nullptr);
					player->GetMessage(*messageToPlayer);
					/*player->SetState(IDLE);*/
				}
				return;
			}

		}
	}
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

void Level::Draw(sf::RenderWindow& window, float time, Game* game)
{
	player->Update(time, window, this);
	if (player->GetState() == DEATH)
	{
		game->SetEndGame(true);
		return;
	}
	
	// ���������� �� ���� ������
	for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); )
	{
		it->Update(time, window, this);
		if (it->GetState() == DEATH)
		{
			it = enemies.erase(it);
		}
		else it++;
		//window.draw(enemies[i].GetSprite(enemies[i].GetState()));
	}

	// ���������� �� ��������� ���������
	for (std::vector<SupportItem*>::iterator it = supportItems.begin(); it != supportItems.end(); )
	{
		(*it)->Update(time, window);
		if ((*it)->GetUsed())
		{
			it = supportItems.erase(it);
		}
		else it++;
	}

	// ���������
	window.setView(view);

	window.clear();

	// ������ ��� ����� (������� �� ������!)
	for (int layer = 0; layer < layers.size(); layer++)
		for (int tile = 0; tile < layers[layer].tiles.size(); tile++)
			window.draw(layers[layer].tiles[tile]);

	// ������ ���������
	window.draw(player->GetSprite(player->GetState()));
	
	// ������ ������
	for (int i = 0; i < enemies.size(); i++)
	{
		window.draw(enemies[i].GetSprite(enemies[i].GetState()));
	}

	// ������ �������� ���������
	for (int i = 0; i < supportItems.size(); i++)
	{
		window.draw(supportItems[i]->GetSprite());
	}

	window.display();
}


