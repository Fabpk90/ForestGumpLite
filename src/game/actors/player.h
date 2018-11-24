//
// Created by fab on 07/11/18.
//

#ifndef FORESTGUMPLITE_PLAYER_H
#define FORESTGUMPLITE_PLAYER_H

#include <SFML/Graphics.hpp>

#include "actor.h"

class Player : public Actor
{
public:
    ~Player() override;

    Player(const char* path, int health);

    bool takeDamage(int amount) override;

    void onDie() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif //FORESTGUMPLITE_PLAYER_H
