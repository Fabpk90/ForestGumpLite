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

    //TODO: long-term, add all the sprite somewhere and only reference them by the actor, to save up some mem

    bool getIsPositionFree(sf::Vector2f pos);

public:
    ~MapManager() override;
    MapManager(const char *path);

    /// Loads the map into the manager
    /// \param path The path to the map leve
    /// \return Whether or not the map has been successfully loaded
    bool loadMapFromFile(const char *path);

    sf::Vector2f getFreePosition();

    /// Adds an actor in the map
    /// \param actor
    /// \return whether or not it has been added ( if free pos available)
    bool addActor(Actor* actor);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif //FORESTGUMPLITE_MAPMANAGER_H
