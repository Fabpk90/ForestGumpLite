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

    /// used for drawing the net on the map
    sf::VertexArray lineVertexPoints;

    /// Loads the lines drawing the pixels
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

    /// Gets a free position in the map
    /// \return The free position, represented by a Vector2D
    sf::Vector2f getFreePosition();

    /// Adds an actor in the map
    /// \param actor
    /// \return whether or not it has been added ( if free pos available)
    bool addActor(Actor* actor);

    list<Actor*>& getActorList() { return actorList; }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /// Checks whether or not a collision has happened where the player is aiming, if so destroys the actor collided
    /// \param playerAiming the player casting the ray to be check for collision
    /// \return true if something has been hit, false otherwise
    bool collisionAimCheck(Player &playerAiming);

    void setDrawLines(bool drawLines) { this->drawLines = drawLines; }

    /// Checks if the given position is not occupied
    /// \param pos The position to check for
    /// \return whether the position is occupied
    bool getIsPositionFree(sf::Vector2f pos);
};


#endif //FORESTGUMPLITE_MAPMANAGER_H
