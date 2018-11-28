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

    //TODO: find a way to update the vertex array pos

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
    sf::Vertex v1, v2;

    aimingLineVertexArray.setPrimitiveType(sf::PrimitiveType::Lines);

    v1.position = sprite->getPosition();

    v2.position = v1.position;

    aimingLineVertexArray.append(v1);
    aimingLineVertexArray.append(v2);
}
