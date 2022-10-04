#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "Player.h"

using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML works!");
    
    Clock clock;

    Player p("Run.png", 250, 250, 96, 96);

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
         }

        p.Update(time);

        window.clear();
        window.draw(p.GetSprite());
        window.display();
    }

    return 0;
}