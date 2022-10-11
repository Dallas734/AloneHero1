#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "Player.h"
#include "Entity.h"
#include "Level.h"


using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML works!");
    Clock clock;

    // Карта
    Level lvl;//создали экземпляр класса уровень
    lvl.LoadFromFile("Levels/map_XML.tmx");//загрузили в него карту, внутри класса с помощью методов он ее обработает.

    Player player(0, 0);
    
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
        player.Update(time, window);

        // Отрисовка
        window.clear();
        lvl.Draw(window);
        //window.display();
        //lvl.Draw(window);
        //player.Update(time, window);
        //window.clear();
        window.draw(player.GetSprite(player.GetState()));
        window.display();

    }

    return 0;
}