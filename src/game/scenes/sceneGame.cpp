//
// Created by fab on 14/11/18.
//

#include "sceneGame.h"

SceneGame::SceneGame(const char* mapPath, const char* player1ImgPath, const char* player2ImgPath)
: mapManager(mapPath),
p1(player1ImgPath, 10),
p2(player2ImgPath, 10)
{
}

void SceneGame::update()
{

}
