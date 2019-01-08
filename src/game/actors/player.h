//
// Created by fab on 07/11/18.
//

#ifndef FORESTGUMPLITE_PLAYER_H
#define FORESTGUMPLITE_PLAYER_H

#include <SFML/Graphics.hpp>

#include "actor.h"
#include "../../util/HUDManager.h"

class Player : public Actor
{
private:

    int maxHealth;
    int movementRemaining;

    bool shouldBeDrawn;

    /// the power of the weapon
    int powerMax;
    /// power in use in this turn
    int powerInUse;
    bool isPlayer1;

    int orientation;

    ///For drawing the aiming line
    sf::VertexArray aimingLineVertexArray;
    /// For drawing the circle of impact of the aim
    sf::CircleShape aimingCircle;

    bool canShoot;
    bool isAiming;
    float aimAngle;

    int aimAngleMax;
    int aimAngleMin;


    HUDManager& hud;

    /// Loads the lines in the vertex array, the position is by default the position of the player
    void loadAimingLine();

    /// Updates the ui power of the preparing shot
    void updatePowerText(sf::Vector2f mousePosition, int power);

    /// Updates the circle of damage
    void updateAimingCircle();

public:
    enum EDirection
    {
        RIGHT = 0,
        DOWN,
        LEFT,
        UP
    };

    Player(const char* path, int health, bool isPlayer1, HUDManager& hud);
    ~Player() override;

    bool takeDamage(int amount) override;
    void takeSelfDamage(int amount);

    void onDie() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /// Updates the aiming line with the passed position as the tip of the aim
    void updateAimingLine(sf::Vector2f position);

    int getMaxHealth() { return  maxHealth; }

    int getPowerMax() { return powerMax; }
    int getPowerInUse() { return powerInUse; }

    void setOrientation(EDirection direction);
    int getOrientation() { return orientation; }

    /// Checks if the angle is in the field of view
    /// \param angleAmount The angle to check
    /// \return whether the angle is in the field of view
    bool isAngleValid(float angleAmount);

    void setIsAiming(bool aiming);
    void toggleAiming();
    bool getIsAiming() { return  isAiming; }

    bool getCanShoot() { return canShoot && isAiming; }

    bool isPlayerOne() { return isPlayer1; }

    void setPosition(sf::Vector2f position) override;

    /// Moves the player to the pos, consuming 1 movement
    /// \param pos Position to go
    void moveTo(sf::Vector2f pos);

    void setToBeDrawn(bool drawn) { shouldBeDrawn = drawn; }
    bool getToBeDrawn() { return shouldBeDrawn; }

    int getAimMaxAngle() { return aimAngleMax; }
    int getAimMinAngle() { return aimAngleMin; }

    void setMovementRemaining(int amount) { movementRemaining = amount; }
    int getMovementRemaining() { return movementRemaining; }

    sf::RectangleShape getAimRectangle();
    sf::CircleShape getAimCircle();
};


#endif //FORESTGUMPLITE_PLAYER_H
