//
// Created by fab on 07/11/18.
//

#ifndef FORESTGUMPLITE_MAPMANAGER_H
#define FORESTGUMPLITE_MAPMANAGER_H

#include <SFML/Graphics.hpp>

#include <vector>
#include "../actors/actor.h"

using namespace std;

class MapManager : public sf::Drawable
{
private:
    vector<Actor*> actorList;

    vector<sf::Sprite*> groundList;
    sf::Texture groundTex;
    //TODO: long-term, add all the sprite somewhere and only reference them by the actor, to save up some mem

public:
    ~MapManager() override;
    MapManager(const char *path);

    bool loadFromFile(const char *path);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif //FORESTGUMPLITE_MAPMANAGER_H
