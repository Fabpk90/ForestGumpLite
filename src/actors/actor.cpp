#include "actor.h"

Actor::Actor(const char* path)
{
    tex = new sf::Texture();
    
    if(tex->loadFromFile(path))
    {
        sprite = new sf::Sprite(*tex);
        health = 10;
    }
    else
    {
        delete tex;
        exit(-1);
    }
}

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