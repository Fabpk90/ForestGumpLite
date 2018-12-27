//
// Created by fab on 24/12/18.
//

#include <iostream>
#include "HUDManager.h"

void HUDManager::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (int i = 0; i < NUM_ELEMENT; ++i) {
        if(bElementsToBeDrawn[i])
            target.draw(arrayText[i]);
    }

}

HUDManager::HUDManager()
{
    if(!font.loadFromFile("res/font/Roboto.ttf"))
    {
        std::cerr << "Error while loading the font Roboto";
        exit(-1);
    }

    for (int i = 0; i < NUM_ELEMENT; ++i) {
        bElementsToBeDrawn[i] = false;
    }

    for (int j = 0; j < NUM_ELEMENT; ++j) {
        arrayText[j].setFont(font);
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
