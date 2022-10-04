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

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
         }

        p.Move(time, "Run.png", 160, 0, 160, 111);

        /*if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 8) CurrentFrame -= 8;
            heroSprite.setTextureRect(IntRect(160 * int(CurrentFrame), 0, 160, 111));
            heroSprite.move(0.1 * time, 0);
        }*/

        // Анимация
        //if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
        //{
        //    p.SetDirection(LEFT);
        //    p.SetSpeed(0.1);
        //    currentFrameX += 0.005 * time;
        //    // Переход на новую строку
        //    if (currentFrameX > 3)
        //    {
        //        currentFrameX -= 3;
        //        currentFrameY++;
        //    }
        //    if (currentFrameY > 3)
        //    {
        //        currentFrameX -= 3;
        //        currentFrameY -= 3;
        //    }
        //    // Вырезаем спрайт
        //    p.GetSprite().setTextureRect(IntRect(45 * int(currentFrameX), 17 * int(currentFrameY), 128, 64));
        //}

        window.clear();
        window.draw(p.GetSprite());
        window.display();
    }

    return 0;
}