//
// Created by fab on 14/11/18.
//

#ifndef FORESTGUMPLITE_SCENEGAME_H
#define FORESTGUMPLITE_SCENEGAME_H

#include "scene.h"
#include "../actors/player.h"
#include "../../map/mapManager.h"
#include "../../util/HUDManager.h"

class SceneGame : public Scene
{
private:

    sf::RenderWindow& window;
    sf::View view;

    MapManager mapManager;

    ///Players are pointer because in the mapManager they are in the array of pointers
    ///all elements of this array get deleted, thus them being pointers
    Player* p1;
    Player* p2;

    Player* playerPlaying;

    bool isPlayer1Turn;
    bool isIAPlayer;

    ///used to know whether or not the player playing sees the other one
    sf::RectangleShape sightRectangle;

    /// Changes player turn, setting variables accordingly
    void changePlayerTurn();

    /// Updates the HUD according to the playerPlaying
    void updatePlayerHUD();

    /// Checks if the player sees the other player
    /// \return whether the player is seeing the other one
    bool checkPlayerSight();

    /// Checks if the player is pressing keys to move
    void checkForPlayerMovement();

    /// Checks if the player is pressing keys to turn
	void checkForPlayerTurning(int AITurning = 0);

	/// Checks if the given position is valid for the player playing
	/// if so, apply the movement to it
    void validateAndMovePos(const sf::Vector2f &pos);

	///Initialize the HUD of the Game
    void initHUD();

    /// Moves the IA
    void moveIA(sf::Vector2f vector2);

    /// Handles ia turn, finite state machine for ia behaviours
    void handleAITurn();
    /// Handles the aiming of the ai
    void IA_Aim();

    HUDManager hud;
public:

    ~SceneGame() override;

    SceneGame(const char* mapPath, const char* player1ImgPath, const char* player2ImgPath, bool IA);

    void update() override;
};


#endif //FORESTGUMPLITE_SCENEGAME_H
