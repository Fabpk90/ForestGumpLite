//
// Created by fab on 24/12/18.
//

#ifndef FORESTGUMPLITE_HUDMANAGER_H
#define FORESTGUMPLITE_HUDMANAGER_H

#define NUM_ELEMENT 3

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class HUDManager : public sf::Drawable{

private:

    sf::Font font;

    bool bElementsToBeDrawn[NUM_ELEMENT];
    sf::Text arrayText[NUM_ELEMENT];

public:

    enum ETextIndex
    {
        HEALTH = 0,
        POWER,
        PLAYER
    };

    HUDManager();

    void setTextPosition(ETextIndex index, sf::Vector2f pos);
    void setActiveText(ETextIndex index, bool active);
    //here we're not using a ref, to be able to pass "" strings
    void setTextString(ETextIndex index, std::string str);
    void setTextColor(ETextIndex index, const sf::Color color);

    void deActivateAllTexts();

    sf::Text& getText(ETextIndex index) { return arrayText[index]; };


protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

};


#endif //FORESTGUMPLITE_HUDMANAGER_H
