//
// Created by fab on 07/11/18.
//

#include <iostream>
#include <cmath>
#include "player.h"
#include "../gameManager.h"
#include "../../util/VectorHelper.h"
#include "../../util/Constants.h"

Player::~Player() = default;

Player::Player(const char *path, int health, bool isPlayer1) : Actor(path, health)
{
    this->isPlayer1 = isPlayer1;
    isAiming = false;

    shouldBeDrawn = true;

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
    if(shouldBeDrawn)
    {
        Actor::draw(target, states);

        if(isAiming)
            target.draw(aimingLineVertexArray);
    }
}

void Player::setOrientation(EDirection direction)
{
    //TODO: maybe change this to not include a modulo op
    orientation = direction * 90;

    if(orientation == 0)
    {
        aimAngleMin = 3 * 90;
        aimAngleMax = 1 * 90;
    }
    else
    {
        aimAngleMin = orientation - 90;
        aimAngleMax = orientation + 90;
    }
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

    aimingLineVertexArray[1].position = sprite->getPosition() * 1.5f;
    aimingLineVertexArray[1].color = sf::Color::Red;
}

void Player::updateAimingLine(sf::Vector2i position)
{
    //this vector represents the translated aim vector, the center of the cartesian model being the player pos
    sf::Vector2f translatedPosition = sf::Vector2f(position);

    //translating with the player pos, normalizing the pos to calculate the angle
    translatedPosition.x -= aimingLineVertexArray[0].position.x;
    translatedPosition.y -= aimingLineVertexArray[0].position.y;

    float angle = VectorHelper::angleBetween(translatedPosition, sf::Vector2f(0.0f, 0.0f));
    if(angle < 0) angle += 2 * PI;

    angle = (angle * 180.0f / PI);

    //if correct angle, set it to the actual angle
    if(isAngleValid(angle))
    {
        aimingLineVertexArray[1].position = sf::Vector2f(position);
        aimAngle = angle;
    }
}

sf::RectangleShape Player::getAimRectangle()
{
    //used to represent the ray
    sf::RectangleShape rect;

    rect.setPosition(aimingLineVertexArray[0].position);

    rect.setSize(sf::Vector2f(2.0f,
            VectorHelper::getLength((aimingLineVertexArray[1].position - aimingLineVertexArray[0].position).x,
                           (aimingLineVertexArray[1].position - aimingLineVertexArray[0].position).y)));

    rect.setRotation(aimAngle - 90); // because 0 is down

    return rect;
}

void Player::setPosition(sf::Vector2f position)
{
    Actor::setPosition(position);

    //centering the pos to the center of the player sprite
    position.x += sprite->getTexture()->getSize().x >> 1;
    position.y += sprite->getTexture()->getSize().y >> 1;

    aimingLineVertexArray[0].position = position;

    aimingLineVertexArray[1].position = position * 1.5f;
}

bool Player::isAngleValid(float angle)
{

    //special case where the orientation is zero, we have to accept a weird angle because of its nature %361
    if(orientation == 0)
    {
        if(angle > aimAngleMin || angle < aimAngleMax)
        {
            return true;
        }
    }
    else
    {
        if(angle > aimAngleMin && angle < aimAngleMax)
        {
            return true;
        }
    }

    return false;
}
