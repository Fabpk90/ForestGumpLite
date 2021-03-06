#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Actor : public sf::Drawable
{
protected:
    sf::Texture tex;
    sf::Sprite sprite;
    int health;

public:
    Actor(const char* path, int health);

    int getHealth() { return health; }

    const sf::Vector2f& getPosition();

    virtual void setPosition(sf::Vector2f position);

    void setPosition(float x, float y);

    sf::FloatRect getGlobalBounds() { return sprite.getGlobalBounds(); }
    sf::Sprite& getSprite() { return  sprite; }

    virtual bool takeDamage(int amount);

    virtual void onDie() = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif