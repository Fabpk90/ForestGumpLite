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

    //gm.setScene(new SceneGame("res/map/map1.level", "res/texture/Player.png", "res/texture/Player.png"));
    //gm.setScene(new Editor());
    gm.setScene(new SceneMainMenu());
   // gm.setScene(new SceneGame("res/map/map1.level", "res/texture/Player.png", "res/texture/Player.png"));
    //gm.setScene(new SceneGame("LOL.level", "res/texture/Player.png", "res/texture/Player.png"));

    while (gm.getWindow().isOpen())
    {
        gm.renderScene();
    }

    return 0;
}
