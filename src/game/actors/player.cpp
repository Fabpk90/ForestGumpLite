//
// Created by fab on 07/11/18.
//

#include <iostream>
#include <cmath>
#include "player.h"
#include "../gameManager.h"
#include "../../util/VectorHelper.h"
#include "../../util/Constants.h"

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
    GameManager::Instance->setWinner(!isPlayer1);
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
    sf::Vector2f centeredPos = sprite->getPosition();

    centeredPos.x += sprite->getTexture()->getSize().x >> 1;
    centeredPos.y += sprite->getTexture()->getSize().y >> 1;

    aimingLineVertexArray[0].position = centeredPos;
    aimingLineVertexArray[1].position = sf::Vector2f(position);
}

sf::RectangleShape Player::getAimRectangle()
{
    //used to represent the ray
    sf::RectangleShape rect;

    //this vector represents the translated aim vector, the center of the cartesian model being the player pos
    sf::Vector2f translatedPosition = aimingLineVertexArray[1].position;

    //translating with the player pos
    translatedPosition.x -= aimingLineVertexArray[0].position.x;
    translatedPosition.y -= aimingLineVertexArray[0].position.y;


    float angle = VectorHelper::angleBetween(translatedPosition, sf::Vector2f(0.0f, 0.0f));

    if (angle < 0) angle += 2 * PI;

    rect.setPosition(aimingLineVertexArray[0].position);


    rect.setSize(sf::Vector2f(2.0f, VectorHelper::getLength((aimingLineVertexArray[1].position - aimingLineVertexArray[0].position).x,
            (aimingLineVertexArray[1].position - aimingLineVertexArray[0].position).y)));

    rect.setRotation((angle * 180.0f / PI) - 90);

    return rect;
}
