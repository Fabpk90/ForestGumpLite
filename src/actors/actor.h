#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Actor
{
private:
    sf::Texture* tex;
    sf::Sprite* sprite;
    int health;

public:
    Actor(const char* path);
    Actor(const char* path, int health);

    int getHealth() { return health; }
    bool takeDamage(int amount);

    virtual void onDie() = 0;
};

#endif