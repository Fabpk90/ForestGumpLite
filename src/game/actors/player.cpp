//
// Created by fab on 07/11/18.
//

#include <iostream>
#include "player.h"
#include "../gameManager.h"

Player::~Player()
{

}

Player::Player(const char *path, int health, bool isPlayer1) : Actor(path, health)
{

    this->isPlayer1 = isPlayer1;
    isAiming = false;

    loadAimingLine();
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

    if(isAiming)
        target.draw(aimingLineVertexArray);
}

void Player::setOrientation(int amount)
{
    //TODO: maybe change this to not include a modulo op
    orientation = amount % 361;
}

void Player::setIsAiming(bool aiming)
{
    isAiming = aiming;
}

void Player::loadAimingLine()
{
    aimingLineVertexArray = sf::VertexArray(sf::Lines, 2);

    aimingLineVertexArray[0].position = sprite->getPosition();
    aimingLineVertexArray[0].color = sf::Color::Red;

    aimingLineVertexArray[1].position = sprite->getPosition() * .5f;
    aimingLineVertexArray[1].color = sf::Color::Red;
}

void Player::updateAimingLine(sf::Vector2i position)
{
    aimingLineVertexArray[0].position = sprite->getPosition();
    aimingLineVertexArray[1].position = sf::Vector2f(position);
}
