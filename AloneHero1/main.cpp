#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "Player.h"
#include "Entity.h"

using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML works!");
    Clock clock;

    Player player(250, 250);
    
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
        States statePlayer;
        statePlayer = player.Update(time);

        //p.Update(time);
        if (statePlayer == RUN)
        {
            window.clear();
            window.draw(player.GetSprite(RUN));
        }
        else if (statePlayer == IDLE)
        {
            window.clear();
            window.draw(player.GetSprite(IDLE));
        }
        else if (statePlayer == HIT)
        {
            window.clear();
            window.draw(player.GetSprite(HIT));
        }
        window.display();
    }

    return 0;
}