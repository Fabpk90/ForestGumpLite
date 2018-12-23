//
// Created by fab on 14/11/18.
//

#include <SFML/Window/Event.hpp>
#include "sceneMainMenu.h"
#include "../gameManager.h"
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
                //TODO: Rediriger vers le jeux ou l'editeur
                if(menu.getItem()==0) std::cout << "Jouer" << std::endl;
                if(menu.getItem()==1) std::cout << "Editeur" << std::endl;
                if(menu.getItem()==2) window.close();
            }
        }
        if (event.type == sf::Event::Closed)
            window.close();
    }


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();

    window.clear();
    menu.drawMenu(window);
    window.display();


}

SceneMainMenu::SceneMainMenu():menu(600,400)
{

}

SceneMainMenu::~SceneMainMenu()
{

}
