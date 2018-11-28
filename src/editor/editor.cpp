//
// Created by fab on 28/11/18.
//

#include "editor.h"
#include "../game/gameManager.h"


void Editor::update()
{
    sf::RenderWindow& window = GameManager::Instance->getWindow();




    window.clear(GameManager::Instance->getClearColor());
    window.draw(mapManager);

    window.display();

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();
}

Editor::~Editor()
{

}

Editor::Editor()
{
    mapManager.setDrawLines(true);
}
