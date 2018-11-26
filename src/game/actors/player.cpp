//
// Created by fab on 07/11/18.
//

#include "player.h"
#include "../gameManager.h"

Player::~Player()
{

}

Player::Player(const char *path, int health, bool isPlayer1) : Actor(path, health)
{
    this->isPlayer1 = isPlayer1;
}

bool Player::takeDamage(int amount)
{
    return Actor::takeDamage(amount);
}

void Player::onDie()
{
    GameManager::Instance->setWinner(isPlayer1);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    Actor::draw(target, states);
}
