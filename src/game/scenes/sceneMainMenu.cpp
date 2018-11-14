//
// Created by fab on 14/11/18.
//

#include <SFML/Window/Event.hpp>
#include "sceneMainMenu.h"
#include "../gameManager.h"

void SceneMainMenu::update()
{
    sf::Window& window = GameManager::Instance->getWindow();

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();
}

SceneMainMenu::SceneMainMenu()
{
    printf("ha");
}
