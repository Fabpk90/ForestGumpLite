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
    int powerMax;
    bool isPlayer1;

    int orientation;

    //For drawing the aiming line
    sf::VertexArray aimingLineVertexArray;

    bool isAiming;

    //loads the lines in the vertex array, the position is by default the position of the player
    void loadAimingLine();

public:
    ~Player() override;

    Player(const char* path, int health, bool isPlayer1);

    bool takeDamage(int amount) override;

    void onDie() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void updateAimingLine(sf::Vector2i position);

    void setPower(int amount) { powerMax = amount; }
    int getPower() { return powerMax; }

    void setOrientation(int amount);
    int getOrientation() { return orientation; }

    void setIsAiming(bool aiming);
    bool getIsAiming() { return  isAiming; }

};


#endif //FORESTGUMPLITE_PLAYER_H
