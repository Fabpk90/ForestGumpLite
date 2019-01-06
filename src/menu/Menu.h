//
// Created by charlotte on 22/12/18.
//
#include <SFML/Graphics.hpp>
#include "../game/scenes/scene.h"

#ifndef FORESTGUMPLITE_MENU_H
#define FORESTGUMPLITE_MENU_H


class Menu : public sf::Drawable {
private:
    int itemSelected;
    sf::Font font;
    sf::Text menuText[3];
    sf::Sprite sprite;
    sf::Texture texture;

public:
    Menu(float width, float height);

    void MoveUp();
    void MoveDown();
    int getItem() {return itemSelected;}

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    ~Menu();
};


#endif //FORESTGUMPLITE_MENU_H
