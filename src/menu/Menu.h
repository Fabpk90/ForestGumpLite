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

    //the sprite and texture of the background
    sf::Sprite sprite;
    sf::Texture texture;

    bool isModeSelected;
    /// which map is selected, to be used with mapList
    int mapSelected;

    std::vector<std::string> mapList;

    /// Loads the list of map's name from the directory
    void loadMapList();

public:
    Menu(float width, float height);

    /// Moves up in the menu list
    void MoveUp();
    /// Moves down in the menu list
    void MoveDown();

    int getSelectedItem() {return itemSelected;}
    std::string getStringMapSelected() { return mapList[mapSelected]; }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /// Asks the user to choose from the map list
    /// \return if the user has chose(true) or if it wants to go back(false)
    bool askForMap();

    ~Menu();
};


#endif //FORESTGUMPLITE_MENU_H
