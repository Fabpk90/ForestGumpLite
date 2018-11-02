#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Actor : public sf::Drawable
{
private:
    sf::Texture* tex;
    sf::Sprite* sprite;
    int health;

public:
    Actor(const char* path);
    Actor(const char* path, int health);

    virtual ~Actor();

    int getHealth() { return health; }
    virtual bool takeDamage(int amount);

    virtual void onDie() = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif