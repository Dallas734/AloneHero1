#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "Player.h"
#include "Entity.h"
#include "Level.h"

class Game
{
	private:
		bool endGame;
	public:
		Game()
		{
			endGame = false;
		}
		bool StartGame();
		void GameRunning();
		void SetEndGame(bool endGame);
};

