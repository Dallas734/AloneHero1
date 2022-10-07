#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "Player.h"
#include "Entity.h"

using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML works!");
    Clock clock;

    Player p(250, 250);
    
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
        
        // Состояние для отображения соответствующей анимации.
        States state;
        state = p.Update(time);

        //p.Update(time);
        if (state == RUN)
        {
            window.clear();
            window.draw(p.GetSprite(RUN));
        }
        else if (state == IDLE)
        {
            window.clear();
            window.draw(p.GetSprite(IDLE));
        }
        window.display();
    }

    return 0;
}