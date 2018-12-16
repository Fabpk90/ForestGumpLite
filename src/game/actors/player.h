//
// Created by fab on 07/11/18.
//

#ifndef FORESTGUMPLITE_PLAYER_H
#define FORESTGUMPLITE_PLAYER_H

#include <SFML/Graphics.hpp>

#include "actor.h"

class Player : public Actor
{
private:
    //the power of the weapon
    int powerMax;
    bool isPlayer1;

    int orientation;

    //For drawing the aiming line
    sf::VertexArray aimingLineVertexArray;

    bool isAiming;
    float aimAngle;

    int aimAngleMax;
    int aimAngleMin;

    //loads the lines in the vertex array, the position is by default the position of the player
    void loadAimingLine();

    bool shouldBeDrawn;

public:
    enum EDirection
    {
        RIGHT = 0,
        DOWN,
        LEFT,
        UP
    };

    ~Player() override;

    Player(const char* path, int health, bool isPlayer1);

    bool takeDamage(int amount) override;

    void onDie() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void updateAimingLine(sf::Vector2i position);

    void setPower(int amount) { powerMax = amount; }
    int getPower() { return powerMax; }

    void setOrientation(EDirection direction);
    int getOrientation() { return orientation; }

    bool isAngleValid(float angleAmount);

    void setIsAiming(bool aiming);
    void toggleAiming() { isAiming = !isAiming; }
    bool getIsAiming() { return  isAiming; }

    bool isPlayerOne() { return isPlayer1; }

    void setPosition(sf::Vector2f position) override;

    void setToBeDrawn(bool drawn) { shouldBeDrawn = drawn; }
    bool getToBeDrawn() { return shouldBeDrawn; }


    int getAimMaxAngle() { return aimAngleMax; }
    int getAimMinAngle() { return aimAngleMin; }

    sf::RectangleShape getAimRectangle();
};


#endif //FORESTGUMPLITE_PLAYER_H
