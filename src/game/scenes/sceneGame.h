//
// Created by fab on 14/11/18.
//

#ifndef FORESTGUMPLITE_SCENEGAME_H
#define FORESTGUMPLITE_SCENEGAME_H

#include "scene.h"
#include "../map/mapManager.h"
#include "../actors/player.h"

class SceneGame : public Scene
{
private:
    MapManager mapManager;

    //Players are pointer because in the mapManager they are in the array of pointers
    //all elements of this array get deleted, thus them being pointers
    Player* p1;
    Player* p2;

    sf::Color clearColor;

public:

    SceneGame(const char* mapPath, const char* player1ImgPath, const char* player2ImgPath);

    void update() override;
};


#endif //FORESTGUMPLITE_SCENEGAME_H
