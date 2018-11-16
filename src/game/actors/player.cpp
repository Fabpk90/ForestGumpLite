//
// Created by fab on 07/11/18.
//

#include "player.h"

Player::~Player()
{

}

Player::Player(const char *path, int health) : Actor(path, health)
{

}

bool Player::takeDamage(int amount)
{
    return Actor::takeDamage(amount);
}

void Player::onDie()
{

}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    Actor::draw(target, states);
}
