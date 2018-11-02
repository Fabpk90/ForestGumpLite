#include <SFML/Graphics.hpp>

#include "actors/actor.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 400), "ForestGumpLite");
    //Actor actor("res/tree.png", 10);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();

        window.clear();
        //window.draw(actor);
        window.display();
    }

    return 0;
}