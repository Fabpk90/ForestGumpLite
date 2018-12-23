//
// Created by charlotte on 22/12/18.
//
#include <SFML/Graphics.hpp>
#include "../game/scenes/scene.h"

#ifndef FORESTGUMPLITE_MENU_H
#define FORESTGUMPLITE_MENU_H


class Menu : public Scene {
private:
    int itemSelected;
    sf::Font font;
    sf::Text menuText[3];

public:
    Menu(float width, float height);

    void drawMenu(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int getItem() {return itemSelected;}

    void update() override;

    ~Menu();
};


#endif //FORESTGUMPLITE_MENU_H
