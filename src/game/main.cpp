#include <SFML/Graphics.hpp>

#include "actors/obstacle.h"
#include "gameManager.h"
#include "scenes/sceneMainMenu.h"

int main()
{
    GameManager gm;
    //Actor actor("res/tree.png", 10);

    gm.setScene(new SceneMainMenu());

    while (gm.getWindow().isOpen())
    {
        gm.renderScene();
    }

    return 0;
}