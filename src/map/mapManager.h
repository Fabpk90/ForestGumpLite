//
// Created by fab on 07/11/18.
//

#ifndef FORESTGUMPLITE_MAPMANAGER_H
#define FORESTGUMPLITE_MAPMANAGER_H

#include <SFML/Graphics.hpp>

#include <list>
#include "../game/actors/actor.h"
#include "../game/actors/player.h"

using namespace std;

class MapManager : public sf::Drawable
{
private:
    list<Actor*> actorList;

    //used  for storing the line points, sent to the graphic card every frame to be drawn
    sf::VertexArray lineVertexPoints;

    //TODO: long-term, add all the sprite somewhere and only reference them by the actor, to save up some mem

    bool getIsPositionFree(sf::Vector2f pos);

    void loadLines();

    bool drawLines;

public:
    ~MapManager() override;

    MapManager(const char *path);
    MapManager();

    /// Loads the map into the manager
    /// \param path The path to the map leve
    /// \return Whether or not the map has been successfully loaded
    bool loadMapFromFile(const char *path);

    sf::Vector2f getFreePosition();

    /// Adds an actor in the map
    /// \param actor
    /// \return whether or not it has been added ( if free pos available)
    bool addActor(Actor* actor);

    list<Actor*>& getActorList() { return actorList; }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /// Checks whether or not a collision has happend, if so destroys the actor collided
    /// \param rect the "ray" casted to check the collision
    /// \return true if something has been hit, false otherwise
    bool collisionCheck(sf::FloatRect rect, Player& playerAiming);


    void setDrawLines(bool drawLines) { this->drawLines = drawLines; }
};


#endif //FORESTGUMPLITE_MAPMANAGER_H
