//
// Created by fab on 07/11/18.
//

#ifndef FORESTGUMPLITE_GAMEMANAGER_H
#define FORESTGUMPLITE_GAMEMANAGER_H

#include <SFML/Graphics.hpp>

#include "scenes/scene.h"
#include "../editor/editor.h"

class GameManager
{
private:
    Scene* scene;
    Scene* nextScene;
    sf::RenderWindow* window;

    bool isSceneToBeFreed;

    sf::Color clearColor;

    sf::Font font;

public:
    GameManager();
    ~GameManager();

    static GameManager* Instance;

    void setScene(Scene* scene);
    void renderScene();

    sf::RenderWindow& getWindow() { return *window; }

    void setWinner(bool isWinnerPlayer1);

    sf::Font& getFont() { return font; }
    sf::Color& getClearColor() { return clearColor; }
};




#endif //FORESTGUMPLITE_GAMEMANAGER_H
