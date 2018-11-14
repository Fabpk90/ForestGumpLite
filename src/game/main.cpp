#include <SFML/Graphics.hpp>

#include "actors/obstacle.h"
#include "gameManager.h"
#include "scenes/sceneMainMenu.h"

int main()
{
    GameManager gm;
    //Actor actor("res/tree.png", 10);

    //TODO: c'est un peu chiant de devoir faire ça pour la première scène
    SceneMainMenu menu;

    gm.setScene(&menu);

    while (gm.getWindow().isOpen())
    {
        gm.renderScene();
    }

    return 0;
}