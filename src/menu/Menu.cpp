//
// Created by charlotte on 22/12/18.
//

#include "Menu.h"

Menu::Menu(float width, float height)
{
    /*if(!font.loadFromFile("Arial.ttf"))
    {

    }*/
    menuText[0].setFont(font);
    menuText[0].setFillColor(sf::Color::Blue);
    menuText[0].setString("Jouer");
    menuText[0].setCharacterSize(24);
    menuText[0].setPosition(width/2, height/4);

    menuText[1].setFont(font);
    menuText[1].setFillColor(sf::Color::White);
    menuText[1].setString("Editeur");
    menuText[1].setPosition(width/2, height/8);

    menuText[3].setFont(font);
    menuText[3].setFillColor(sf::Color::White);
    menuText[3].setString("Quitter");
    menuText[3].setPosition(width/2, height/12);

    itemSelected=0;
}

void Menu::MoveUp()
{
    if(itemSelected-1 >= 0)
    {
        menuText[itemSelected].setColor(sf::Color::White);
        itemSelected--;
        menuText[itemSelected].setColor(sf::Color::Blue);
    }
}

void Menu::MoveDown()
{
    if(itemSelected-1 < 3)
    {
        menuText[itemSelected].setColor(sf::Color::White);
        itemSelected++;
        menuText[itemSelected].setColor(sf::Color::Blue);
    }
}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for(auto t:menuText)
    {
        target.draw(t);
    }
}

Menu::~Menu() {}

