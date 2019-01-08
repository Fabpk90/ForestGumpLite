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
                gameModeSelected = menu.getItem();
            }
        }
        if (event.type == sf::Event::Closed)
            window.close();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
            window.close();
    }

    window.clear();
    window.draw(menu);
    window.display();

    if(gameModeSelected == 3)
        window.close();
    else if (gameModeSelected != -1)
    {
        checkGameMode();
    }
}

void SceneMainMenu::checkGameMode()
{
    string path; bool isMapOk = false;
    if(gameModeSelected == 0 || gameModeSelected == 1)
        {
            if(menu.askForMap())
            {
                path = "res/map/";
                path.append(menu.getStringMapSelected());
                path.append(".level");
                isMapOk = true;
            }
            else
                gameModeSelected = -1;
        }

    switch (gameModeSelected)
        {
            case 0:
                if(isMapOk)
                GameManager::Instance->
                        setScene(new SceneGame(path.c_str(),
                                "res/texture/Player.png",
                                "res/texture/Player.png", false));
                break;

            case 2:
                GameManager::Instance->setScene(new Editor());
                break;

            case 1:
                if(isMapOk)
                GameManager::Instance->
                        setScene(new SceneGame(path.c_str(),
                                "res/texture/Player.png",
                                "res/texture/Player.png", true));
                break;
        }
}

SceneMainMenu::SceneMainMenu():menu(600,400)
{
    gameModeSelected = -1;
}

SceneMainMenu::~SceneMainMenu()
{

}
