//
// Created by charlotte on 22/12/18.
//
#include <SFML/Graphics.hpp>
#include <list>
#include "../game/scenes/scene.h"

#ifndef FORESTGUMPLITE_MENU_H
#define FORESTGUMPLITE_MENU_H

#define MENU_MAIN_ITEMS 4

class Menu : public sf::Drawable {
private:
    int itemSelected;
    sf::Font font;
    //handled from 0 -> upper text n -> lower
    sf::Text menuText[MENU_MAIN_ITEMS];
    sf::Sprite sprite;
    sf::Texture texture;

    bool isModeSelected;
    int mapSelected;


    std::vector<std::string> mapList;

    void loadMapList();

public:
    Menu(float width, float height);

    void MoveUp();
    void MoveDown();
    int getItem() {return itemSelected;}
    std::string getStringMapSelected() { return mapList[mapSelected]; }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool askForMap();

    ~Menu();
};


#endif //FORESTGUMPLITE_MENU_H
