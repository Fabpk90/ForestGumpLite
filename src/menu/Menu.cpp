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
    mapSelected = -1;

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
}

Menu::~Menu() {}

void Menu::loadMapList()
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("res/map")) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL)
        {
            if(ent->d_type == DT_REG)
            {
                std::string str = std::string(ent->d_name);
                str = str.substr(0, str.length() - 6);

                mapList.push_back(str);;
            }
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
    }
}

bool Menu::askForMap()
{
    if(mapList.empty())
    {
        std::cout << "Aucune map n'est presente, passer par l'editeur avant" << std::endl;
        return false;
    }
    int mapNum = -1;
    std::cout << "Quel carte voulez-vous charger ? (-1 pour sortir)\n";

    for(int i = 0; i < mapList.size(); ++i)
    {
        std::cout << i+1 <<" " << mapList[i] << std::endl;
    }

    while(mapNum == -1)
    {
        try
        {
            std::string buf;
            std::getline(std::cin,buf);

            mapNum = std::stoi(buf) - 1;

            if(mapNum == -2)
                return false;
            if(mapNum < 0 || mapNum >= mapList.size())
            {
                std::cout << "Ce n'est pas valide, retentez" << std::endl;
                mapNum = -1;
            }
            else
            {
                std::cout << "Map chargee!" << std::endl;
                mapSelected = mapNum;

                return true;
            }
        }
        catch (std::invalid_argument)
        {
            std::cout << "argument invalide, map non chargee\n";
            return false;
        }
        catch (std::out_of_range)
        {
            std::cout << "nombre trop grand, map non chargee\n";
            return false;
        }
    }

    return false;
}

