#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "Player.h"

using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML works!");
    Clock clock;

    Player p(250, 250);
    
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        // window.draw(p.GetSpriteIdle());

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        /*p.Idle(time);
        window.clear();
        window.draw(p.GetSpriteIdle());*/
        //p.Move(time);
        States state;
        state = p.Update(time);

        //p.Update(time);
        if (state == RUN)
        {
            window.clear();
            window.draw(p.GetSpriteMove());
        }
        else if (state == IDLE)
        {
            window.clear();
            window.draw(p.GetSpriteIdle());
        }
        //window.draw(p.GetSpriteIdle());
        window.display();
    }

    return 0;
}