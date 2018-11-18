//
// Created by fab on 07/11/18.
//
#include "../util/constants.h"
#include <iostream>
#include "gameManager.h"

GameManager* GameManager::Instance = nullptr;

GameManager::GameManager()
{
    if(GameManager::Instance == nullptr)
    {
        GameManager::Instance = this;
        this->window = new sf::RenderWindow(sf::VideoMode(SCREEN_SIZE_HEIGHT, SCREEN_SIZE_WIDTH), "ForestGumpLite");
        scene = nullptr;
    }
}

void GameManager::setScene(Scene *scene, bool isOldToBeDeleted)
{
    if(isOldToBeDeleted)
        delete scene;

    this->scene = scene;
}

void GameManager::renderScene()
{
    scene->update();
}

GameManager::~GameManager()
{
    delete scene;
    delete window;
}
