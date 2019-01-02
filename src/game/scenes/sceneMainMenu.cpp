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

    sf::Event event;
    while (window.pollEvent(event))
    {
        if(event.type == sf::Event::KeyReleased)
        {
            if(event.key.code == sf::Keyboard::Up) menu.MoveUp();
            if(event.key.code == sf::Keyboard::Down) menu.MoveDown();
            if(event.key.code == sf::Keyboard::Return)
            {
                if(menu.getItem()==0) GameManager::Instance->setScene(
                        new SceneGame("res/map/map1.level"
                        , "res/texture/Player.png"
                        , "res/texture/Player.png"));
                if(menu.getItem()==1) GameManager::Instance->setScene(new Editor())
                if(menu.getItem()==2) window.close();
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
}

SceneMainMenu::SceneMainMenu():menu(600,400)
{

}

SceneMainMenu::~SceneMainMenu()
{

}
