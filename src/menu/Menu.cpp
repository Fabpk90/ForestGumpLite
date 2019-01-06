//
// Created by charlotte on 22/12/18.
//

#include <iostream>
#include "Menu.h"

Menu::Menu(float width, float height)
{
    if(!font.loadFromFile("res/font/Roboto.ttf"))
    {
        std::cerr << "Erreur de chargement du font Roboto";
        exit(-1);
    }

    menuText[0].setFont(font);
    menuText[0].setFillColor(sf::Color::Blue);
    menuText[0].setString("Joueur VS Joueur");
    //menuText[0].setCharacterSize(24);
    menuText[0].setPosition(width/2, height/4);

    menuText[2].setFont(font);
    menuText[2].setFillColor(sf::Color::White);
    menuText[2].setString("Editeur");
    menuText[2].setPosition(width/2, height/2);

    menuText[3].setFont(font);
    menuText[3].setFillColor(sf::Color::White);
    menuText[3].setString("Quitter");
    menuText[3].setPosition(width/2, height);

    menuText[1].setFont(font);
    menuText[1].setFillColor(sf::Color::White);
    menuText[1].setString("IA VS IA");
    menuText[1].setPosition(width/2, height/3);

    itemSelected=0;

    if (!texture.loadFromFile("res/texture/fond.jpg"))
    {
        std::cerr << "Erreur de chargement de la texture fond";
    }
    texture.setSmooth(true);

    sprite.setTexture(texture);
    sprite.setScale(1.1,1.1);
}

void Menu::MoveUp()
{
    if(itemSelected-1 >= 0)
    {
        menuText[itemSelected].setFillColor(sf::Color::White);
        itemSelected--;
        menuText[itemSelected].setFillColor(sf::Color::Blue);
    }
}

void Menu::MoveDown()
{
    if(itemSelected+1 < 4)
    {
        menuText[itemSelected].setFillColor(sf::Color::White);
        itemSelected++;
        menuText[itemSelected].setFillColor(sf::Color::Blue);
    }
}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite);
    for(auto const &t:menuText)
    {
        target.draw(t);
    }
}

Menu::~Menu() {}

