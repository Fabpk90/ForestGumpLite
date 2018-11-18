#include <SFML/Graphics.hpp>

#include "actors/obstacle.h"
#include "gameManager.h"
#include "scenes/sceneMainMenu.h"
#include "scenes/sceneGame.h"

int main()
{
    GameManager gm;

    gm.setScene(new SceneGame("res/map/map1.level", "res/texture/tree.png", "res/texture/tree.png"));

    while (gm.getWindow().isOpen())
    {
        gm.renderScene();
    }

    return 0;
}