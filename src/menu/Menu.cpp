//
// Created by charlotte on 22/12/18.
//

#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include "Menu.h"
#include "../game/gameManager.h"

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

    isModeSelected = false;
    mapSelected = 0;

    mapList = std::vector<std::string>();

    loadMapList();
}

void Menu::MoveUp()
{
    if(!isModeSelected)
    {
        if(itemSelected-1 >= 0)
        {
            menuText[itemSelected].setFillColor(sf::Color::White);
            itemSelected--;
            menuText[itemSelected].setFillColor(sf::Color::Blue);
        }
    }
    else
    {

    }
}

void Menu::MoveDown()
{
    if(!isModeSelected)
    {
        if(itemSelected+1 < MENU_MAIN_ITEMS)
        {
            menuText[itemSelected].setFillColor(sf::Color::White);
            itemSelected++;
            menuText[itemSelected].setFillColor(sf::Color::Blue);
        }
    }
    else
    {

    }
}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite);
    if(!isModeSelected)
    {
        for(auto const &t:menuText)
        {
            target.draw(t);
        }
    }
    else
    {
        for(auto const &t : mapTextList)
        {
            target.draw(t);
        }
    }



}

Menu::~Menu() {}

void Menu::loadMapList()
{
    DIR *dir;
    struct dirent *ent;
    sf::Text text;

    text.setFont(GameManager::Instance->getFont());

    if ((dir = opendir ("res/map")) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL)
        {
            if(ent->d_type == DT_REG)
            {
                std::string str = std::string(ent->d_name);
                mapList.push_back(str);

                str = str.substr(0, str.length() - 6);
                text.setString(str);
                mapTextList.push_back(text);


                std::cout << str << std::endl;
            }
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
    }
}

