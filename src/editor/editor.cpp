//
// Created by fab on 28/11/18.
//

#include "editor.h"
#include "../game/gameManager.h"


void Editor::update()
{
    sf::RenderWindow& window = GameManager::Instance->getWindow();





    window.draw(mapManager);
}

Editor::~Editor()
{

}
