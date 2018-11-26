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
    sf::RenderWindow* window;

public:
    GameManager();
    ~GameManager();

    static GameManager* Instance;

    void setScene(Scene* scene, bool isOldToBeDeleted = false);
    void renderScene();

    sf::RenderWindow& getWindow() { return *window; }

    void setWinner(bool isWinnerPlayer1);
};




#endif //FORESTGUMPLITE_GAMEMANAGER_H
