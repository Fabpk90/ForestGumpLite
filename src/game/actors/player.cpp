//
// Created by fab on 07/11/18.
//

#include <iostream>
#include <cmath>
#include "player.h"
#include "../gameManager.h"
#include "../../util/VectorHelper.h"
#include "../../util/Constants.h"

Player::Player(const char *path, int health, bool isPlayer1, HUDManager& hud)
: Actor(path, health), hud(hud)
{
    maxHealth = health;
    this->isPlayer1 = isPlayer1;
    isAiming = false;

    shouldBeDrawn = true;

    aimingCircle = sf::CircleShape();
    aimingCircle.setFillColor(sf::Color::Transparent);

    aimingCircle.setOutlineThickness(2.f);
    aimingCircle.setOutlineColor(sf::Color::Red);

    aimingCircle.setPosition(sprite.getPosition());

    loadAimingLine();
}

bool Player::takeDamage(int amount)
{
    GameManager::Instance->setWinner(!isPlayer1);
    return false;
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
        {
            target.draw(aimingLineVertexArray);

            if(canShoot)
                target.draw(aimingCircle);
        }
    }
}

void Player::setOrientation(EDirection direction)
{
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

    aimAngleMin -= 1;
    aimAngleMax += 1;
}

void Player::setIsAiming(bool aiming)
{
    isAiming = aiming;

    if(isAiming)
        hud.setActiveText(HUDManager::POWER, true);
}

void Player::loadAimingLine()
{
    aimingLineVertexArray = sf::VertexArray(sf::Lines, 2);

    aimingLineVertexArray[0].position = sprite.getPosition();
    aimingLineVertexArray[0].color = sf::Color::Red;

    aimingLineVertexArray[1].position = sprite.getPosition() * 1.5f;
    aimingLineVertexArray[1].color = sf::Color::Red;
}

void Player::updateAimingLine(sf::Vector2f position)
{
    sf::Vector2f pos = sprite.getPosition();

    //centering the pos to the center of the player sprite
    pos.x += sprite.getTexture()->getSize().x >> 1;
    pos.y += sprite.getTexture()->getSize().y >> 1;

    aimingLineVertexArray[0].position = pos;

    //this vector represents the translated aim vector, the center of the cartesian model being the player pos
    //translating with the player pos, normalizing the pos to calculate the angle
    sf::Vector2f tmp = position;

    tmp.x -= aimingLineVertexArray[0].position.x;
    tmp.y -= aimingLineVertexArray[0].position.y;

    float angle = VectorHelper::angleBetween(tmp, sf::Vector2f(0.0f, 0.0f));
    if(angle < 0) angle += 2 * PI;

    angle = (angle * 180.0f / PI);

    //if correct angle, set it to the actual angle
    if(isAngleValid(angle))
    {
        aimAngle = angle;

        float power = VectorHelper::getLength(aimingLineVertexArray[0].position - position)
                / PIXEL_SIZE;

        aimingLineVertexArray[1].position = position;

        if(power >= 1 && power < PLAYER_MAX_POWER +1
        && isAiming && power - health >= 1)
        {
            powerInUse = (int)power;
            canShoot = true;

            updatePowerText(position, power);
            updateAimingCircle();
        }
        else
        {
            hud.setActiveText(HUDManager::POWER, false);
            canShoot = false;
        }
    }
    else
    {
        hud.setActiveText(HUDManager::POWER, false);
        canShoot = false;
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
    position.x += sprite.getTexture()->getSize().x >> 1;
    position.y += sprite.getTexture()->getSize().y >> 1;

    aimingLineVertexArray[0].position = position;
}

bool Player::isAngleValid(float angle)
{
    //special case, because of %360
    if(orientation == UP * 90 && angle == 0)
        return true;

    //special case where the orientation is zero, we have to accept a weird angle because of its nature %360
    if(orientation == RIGHT)
    {
        if(angle >= aimAngleMin || angle <= aimAngleMax)
        {
            return true;
        }
    }
    else
    {
        if(angle >= aimAngleMin && angle <= aimAngleMax)
        {
            return true;
        }
    }

    return false;
}

sf::CircleShape Player::getAimCircle()
{
    updateAimingCircle();

    return aimingCircle;
}

void Player::updateAimingCircle()
{
    aimingCircle.setRadius(powerInUse * PIXEL_SIZE);

    //centering the circle
    aimingCircle.setPosition(aimingLineVertexArray[1].position.x - aimingCircle.getRadius()
            , aimingLineVertexArray[1].position.y - aimingCircle.getRadius());
}

void Player::moveTo(sf::Vector2f pos)
{
    setPosition(pos);
    movementRemaining--;
}

void Player::updatePowerText(sf::Vector2f mousePosition, int power)
{
    if(power > 0)
    {
        //sets the text on the center of the aim line
        sf::Vector2f pos = sprite.getPosition();
        pos.x += mousePosition.x;
        pos.y += mousePosition.y;

        pos.x /= 2;
        pos.y /= 2;

        hud.setActiveText(HUDManager::POWER, true);
        hud.setTextPosition(HUDManager::POWER, pos);
        hud.setTextString(HUDManager::POWER, std::to_string(power));
    }
    else
        hud.setActiveText(HUDManager::POWER, false);

}

void Player::toggleAiming()
{
    isAiming = !isAiming;
    hud.setActiveText(HUDManager::POWER, isAiming);
}

void Player::takeSelfDamage(int amount)
{
    health -= amount;
}

Player::~Player()
{
}

