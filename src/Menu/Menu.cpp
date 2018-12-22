//
// Created by charlotte on 22/12/18.
//

#include "Menu.h"

Menu::Menu(float width, float height)
{
    menuText[0].setFont(font);
    menuText[0].setColor(sf::Color::Blue);
    menuText[0].setString("Jouer");
    menuText[0].setPosition(width/2, height/4);

    menuText[1].setFont(font);
    menuText[1].setColor(sf::Color::White);
    menuText[1].setString("Editeur");
    menuText[1].setPosition(width/2, height/8);

    menuText[3].setFont(font);
    menuText[3].setColor(sf::Color::White);
    menuText[3].setString("Quitter");
    menuText[3].setPosition(width/2, height/12);
    
    itemSelected=0;
}

void Menu::drawMenu(sf::RenderWindow &window)
{
    for (const auto &i : menuText)
    {
        window.draw(i);
    }
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

Menu::~Menu() {}