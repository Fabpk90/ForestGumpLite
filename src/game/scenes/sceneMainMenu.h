//
// Created by fab on 14/11/18.
//

#ifndef FORESTGUMPLITE_SCENEMAINMENU_H
#define FORESTGUMPLITE_SCENEMAINMENU_H

#include "scene.h"
#include "../../menu/Menu.h"

class SceneMainMenu : public Scene
{
private:
    int gameModeSelected;
    Menu menu;
public:

    ~SceneMainMenu() override;

    SceneMainMenu();

    void update() override;
};


#endif //FORESTGUMPLITE_SCENEMAINMENU_H
