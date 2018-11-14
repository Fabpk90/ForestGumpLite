//
// Created by fab on 07/11/18.
//

#ifndef FORESTGUMPLITE_GAMEMANAGER_H
#define FORESTGUMPLITE_GAMEMANAGER_H

#include <SFML/Graphics.hpp>

#include "scenes/scene.h"

class GameManager
{
private:
    Scene* scene;
    sf::Window* window;

public:
    GameManager(sf::Window* window);
    ~GameManager();


    static GameManager* Instance;

    void setScene(Scene* scene, bool isToBeDeleted = false);
    void renderScene();

    sf::Window& getWindow() { return *window; }
};




#endif //FORESTGUMPLITE_GAMEMANAGER_H
