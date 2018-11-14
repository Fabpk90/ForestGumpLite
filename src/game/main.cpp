#include <SFML/Graphics.hpp>

#include "actors/obstacle.h"
#include "gameManager.h"
#include "scenes/sceneMainMenu.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "ForestGumpLite");
    GameManager gm(&window);
    //Actor actor("res/tree.png", 10);

    //TODO: c'est un peu chiant de devoir faire ça pour la première scène
    SceneMainMenu menu;

    gm.setScene(&menu);

    while (window.isOpen())
    {

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();

        //gm.renderScene();

        //partie en commun de toutes les scenes
        window.clear();
        window.display();
    }

    return 0;
}