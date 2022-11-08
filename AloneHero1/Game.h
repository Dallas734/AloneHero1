#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "Player.h"
#include "Entity.h"
#include "Level.h"

class Game
{
	private:
		std::vector<Level*> levels;
	public:
		Game()
		{
			levels.push_back(new Level("map_XML_2.tmx"));
		}
		bool StartGame();
		void GameRunning();
};

