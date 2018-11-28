//
// Created by fab on 28/11/18.
//

#ifndef FORESTGUMPLITE_EDITOR_H
#define FORESTGUMPLITE_EDITOR_H


#include "../game/scenes/scene.h"
#include "../map/mapManager.h"

class Editor  : public Scene {

private:
    MapManager mapManager;


public:
    Editor() = default;

    ~Editor() override;

    void update();

};


#endif //FORESTGUMPLITE_EDITOR_H
