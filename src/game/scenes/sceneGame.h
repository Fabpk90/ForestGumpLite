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

    //Players are pointer because in the mapManager they are in the array of pointers
    //all elements of this array get deleted, thus them being pointers
    Player* p1;
    Player* p2;

    Player* playerPlaying;

    bool isPlayer1Turn;
    bool isIAPlayer;

    //used to know whether or not the player playing sees the other one
    sf::RectangleShape sightRectangle;

    void changePlayerTurn();
    void updatePlayerHUD();

    /// Checks if the player sees the other player
    /// \return
    bool checkPlayerSight();

    void checkForPlayerMovement();
	void checkForPlayerTurning();
	
    void initHUD();

    HUDManager hud;
public:

    ~SceneGame() override;

    SceneGame(const char* mapPath, const char* player1ImgPath, const char* player2ImgPath, bool IA);

    void update() override;
    void IA_Aim();
};


#endif //FORESTGUMPLITE_SCENEGAME_H
