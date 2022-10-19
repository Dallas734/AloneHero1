#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "Player.h"
#include "Entity.h"
#include "Level.h"

using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!");
    Clock clock;

    // �����
    Level lvl("map_XML_2.tmx");//������� ��������� ������ �������
    //lvl.LoadFromFile("Levels/map_XML.tmx");//��������� � ���� �����, ������ ������ � ������� ������� �� �� ����������.

    //Player player(0, 0);
    //player.GetPlayerView().reset(FloatRect(0, 0, 640, 480));
    
    while (window.isOpen())
    {
        // ����� ��� ��������.
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //player.Update(time, window);

        //// ���������
        //window.setView(player.GetPlayerView());

        //window.clear();
        //lvl.Draw(window);

        //window.draw(player.GetSprite(player.GetState()));
        //window.display();
        lvl.Draw(window, time);

    }

    return 0;
}