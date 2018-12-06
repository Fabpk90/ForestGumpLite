//
// Created by fab on 07/11/18.
//

#include <iostream>
#include "player.h"
#include "../gameManager.h"
#include "../../util/VectorHelper.h"

Player::~Player()
{

}

Player::Player(const char *path, int health, bool isPlayer1) : Actor(path, health)
{

    this->isPlayer1 = isPlayer1;
    isAiming = false;

    rect.setSize(sf::Vector2f(10.0f, 10.0f));

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

    target.draw(rect);

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

sf::FloatRect Player::getAimRect()
{
    sf::Transform tr;

    float x0 = aimingLineVertexArray[0].position.x * aimingLineVertexArray[0].position.x;
    float y0 = aimingLineVertexArray[0].position.y * aimingLineVertexArray[0].position.y;

    float x1 = aimingLineVertexArray[1].position.x * aimingLineVertexArray[1].position.x;
    float y1 = aimingLineVertexArray[1].position.y * aimingLineVertexArray[1].position.y;

    float cosangle;

   // cosangle = VectorHelper::getDotProduct(aimingLineVertexArray[0].position.x, aimingLineVertexArray[0].position.y
   //             , aimingLineVertexArray[1].position.x, aimingLineVertexArray[1].position.y) / (VectorHelper::getLength(x0, y0) * VectorHelper::getLength(x1 , y1));


    cosangle = VectorHelper::getDotProduct(aimingLineVertexArray[0].position.x, aimingLineVertexArray[0].position.y
                , aimingLineVertexArray[1].position.x, aimingLineVertexArray[1].position.y) / (VectorHelper::getLength(x0, y0) * VectorHelper::getLength(x1 , y1));

    float angle = atan2(aimingLineVertexArray[0].position.y, aimingLineVertexArray[0].position.x)
            - atan2(aimingLineVertexArray[1].position.y, aimingLineVertexArray[1].position.x);

    std::cout  << angle * 180.0f / PI  << " " << cosangle<< "  " << acos(cosangle) * 180.0f / PI << std::endl;

    rect.setPosition(sprite->getPosition());

    rect.setSize(sf::Vector2f(1.0f, aimingLineVertexArray[1].position.y));

    rect.setRotation(acos(cosangle)* 180.0f / PI);

    //tr.rotate(acos(cosangle) * 180.0f / PI, aimingLineVertexArray[0].position);

    return rect.getGlobalBounds();
    //return tr.transformRect(aimingLineVertexArray.getBounds());
}
