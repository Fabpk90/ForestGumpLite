//
// Created by fab on 24/12/18.
//

#include <iostream>
#include "HUDManager.h"
#include "../game/gameManager.h"

void HUDManager::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (int i = 0; i < NUM_ELEMENT; ++i) {
        if(bElementsToBeDrawn[i])
            target.draw(arrayText[i]);
    }

}

HUDManager::HUDManager()
{

    for (int i = 0; i < NUM_ELEMENT; ++i) {
        bElementsToBeDrawn[i] = false;
    }

    for (int j = 0; j < NUM_ELEMENT; ++j) {
        arrayText[j].setFont(GameManager::Instance->getFont());
    }
}

void HUDManager::setTextColor(HUDManager::ETextIndex index, const sf::Color color)
{
    arrayText[index].setFillColor(color);
}

void HUDManager::setTextPosition(HUDManager::ETextIndex index, sf::Vector2f pos)
{
    arrayText[index].setPosition(pos);
}

void HUDManager::setActiveText(HUDManager::ETextIndex index, bool active)
{
    bElementsToBeDrawn[index] = active;
}

void HUDManager::setTextString(HUDManager::ETextIndex index, std::string str)
{
    arrayText[index].setString(str);
}

void HUDManager::deActivateAllTexts()
{
    for (int i = 0; i < NUM_ELEMENT; ++i) {
        bElementsToBeDrawn[i] = false;
    }
}
