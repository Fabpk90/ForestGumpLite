#include <SFML/Graphics.hpp>

#include "game/actors/obstacle.h"
#include "game/gameManager.h"
#include "game/scenes/sceneMainMenu.h"
#include "game/scenes/sceneGame.h"
#include "editor/editor.h"
#include "menu/Menu.h"

int main()
{
    GameManager gm;

    gm.setScene(new SceneMainMenu());

    while (gm.getWindow().isOpen())
    {
        gm.renderScene();
    }

    return 0;
}
