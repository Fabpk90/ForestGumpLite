//
// Created by fab on 14/11/18.
//

#include <SFML/Window/Event.hpp>
#include "sceneMainMenu.h"
#include "../gameManager.h"
#include "sceneGame.h"
#include "../../editor/editor.h"
#include <iostream>

void SceneMainMenu::update()
{
    sf::RenderWindow& window = GameManager::Instance->getWindow();

    int btnSelected = -1;
    sf::Event event;
    while (window.pollEvent(event))
    {
        if(event.type == sf::Event::KeyReleased)
        {
            if(event.key.code == sf::Keyboard::Up) menu.MoveUp();
            if(event.key.code == sf::Keyboard::Down) menu.MoveDown();
            if(event.key.code == sf::Keyboard::Return)
            {
                btnSelected = menu.getItem();
            }
        }
        if (event.type == sf::Event::Closed)
            window.close();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();

    window.clear();
    window.draw(menu);
    window.display();

    switch (btnSelected)
    {
        case 0:
            GameManager::Instance->
            setScene(new SceneGame("res/map/map2.level", "res/texture/Player.png", "res/texture/Player.png"));
            break;

        case 1:
            GameManager::Instance->setScene(new Editor());
            break;

        case 2:
            window.close();
            break;
    }
}

SceneMainMenu::SceneMainMenu():menu(600,400)
{

}

SceneMainMenu::~SceneMainMenu()
{

}
