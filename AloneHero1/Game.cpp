#include "Game.h"

bool Game::StartGame()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Alone Hero");
    Clock clock;

    // Инициализация уровней
    std::vector<Level*> levels;
    levels.push_back(new Level("map_XML_2.tmx"));

    // Карта
    Level lvl("map_XML_2.tmx");//создали экземпляр класса уровень

    while (window.isOpen())
    {
        // Время для анимации.
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Tab) || endGame) 
            return true;
        if (Keyboard::isKeyPressed(Keyboard::Escape)) return false;

        levels.at(0)->Draw(window, time, this);
    }

    return false;
}


void Game::GameRunning()
{
    // В этом условии сделать переход в меню
    if (StartGame())
    {
        endGame = false;
        GameRunning();
    }
}

void Game::SetEndGame(bool endGame)
{
    this->endGame = endGame;
}
