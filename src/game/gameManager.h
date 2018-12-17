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
    Editor* editor;
    sf::RenderWindow* window;

    sf::Color clearColor;

public:
    GameManager();
    ~GameManager();

    static GameManager* Instance;

    void setScene(Scene* scene, bool isOldToBeDeleted = false);
    void setEditor(Editor* edit) {editor = edit;}
    void renderScene();
    void editorMode();

    sf::RenderWindow& getWindow() { return *window; }

    void setWinner(bool isWinnerPlayer1);

    sf::Color& getClearColor() { return clearColor; }
};




#endif //FORESTGUMPLITE_GAMEMANAGER_H
