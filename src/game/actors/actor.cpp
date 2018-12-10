#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include "actor.h"
#include "../../util/Constants.h"

Actor::Actor(const char* path, int health)
{
    tex = new sf::Texture();

    if(tex->loadFromFile(path))
    {
        sprite = new sf::Sprite(*tex);
        this->health = health;
    }
    else
    {
        delete tex;
        exit(-1);
    }
}

Actor::~Actor()
{
    delete tex;
    delete sprite;
}

void Actor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*sprite);
}

bool Actor::takeDamage(int amount)
{
    if(amount >= health)
    {
        health = 0;
        onDie();

        return true;
    }
    else
    {
        health -= amount;

        return false;
    }
}

const sf::Vector2f& Actor::getPosition()
{
    return sprite->getPosition();
}

void Actor::setPosition(sf::Vector2f v)
{
    sprite->setPosition(v.x, v.y);
}

void Actor::setPosition(float x, float y)
{
    sprite->setPosition(x, y);
}

Actor::Actor(const Actor &act)
{
    tex = act.tex;
    sprite = act.sprite;
}
