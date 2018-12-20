//
// Created by fab on 14/11/18.
//

#include <iostream>
#include "../gameManager.h"
#include "sceneGame.h"
#include "../../util/Constants.h"
#include "../../util/Collision.h"
#include "../../util/VectorHelper.h"

SceneGame::SceneGame(const char* mapPath, const char* player1ImgPath, const char* player2ImgPath)
: mapManager(mapPath)
{
    p1 = new Player(player1ImgPath, 1, true);
    p2 = new Player(player2ImgPath, 1, false);


    p1->setPosition(mapManager.getFreePosition());
    p1->setOrientation(Player::UP);
    mapManager.addActor(p1);

    p2->setPosition(mapManager.getFreePosition());
    p2->setOrientation(Player::DOWN);
    mapManager.addActor(p2);

    mapManager.setDrawLines(true);

    sightRectangle.setSize(sf::Vector2f(5, SCREEN_SIZE_WIDTH));

    isPlayer1Turn = false;
    changePlayerTurn();
}

void SceneGame::update()
{
    sf::RenderWindow& window = GameManager::Instance->getWindow();

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && playerPlaying->getIsAiming())
            {
                mapManager.collisionAimCheck(*playerPlaying);

                playerPlaying->setIsAiming(false);

                changePlayerTurn();

            }
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
            {
                playerPlaying->toggleAiming();
                playerPlaying->updateAimingLine(sf::Mouse::getPosition(window));
            }
        }
        else if(event.type == sf::Event::MouseMoved)
        {
            playerPlaying->updateAimingLine(sf::Mouse::getPosition(window));
        }
        else if (event.type == sf::Event::Closed)
            window.close();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();

    //draw stuff on the screen
    window.clear(GameManager::Instance->getClearColor());
    window.draw(mapManager);
    window.display();
}

void SceneGame::changePlayerTurn()
{
    if(isPlayer1Turn)
    {
        playerPlaying = p2;

        p1->setToBeDrawn(false);
        p2->setToBeDrawn(true);
    }
    else
    {
        playerPlaying = p1;

        p1->setToBeDrawn(true);
        p2->setToBeDrawn(false);
    }

    playerPlaying->setMovementRemaining(MOVEMENT_PER_TURN);

    isPlayer1Turn = !isPlayer1Turn;

    //if the player sees the other one, we draw him
    if(checkPlayerSight())
    {
        if(isPlayer1Turn)
            p2->setToBeDrawn(true);
        else
            p1->setToBeDrawn(true);
    }
}

bool SceneGame::checkPlayerSight()
{
    Player& otherPlayer = isPlayer1Turn ? *p2 : *p1;
    sf::Vector2f startPos = playerPlaying->getPosition();
    sf::Vector2f endPos = otherPlayer.getPosition();

    //centering the pos to the center of the player sprite
    startPos.x += playerPlaying->getSprite().getTexture()->getSize().x >> 1;
    startPos.y += playerPlaying->getSprite().getTexture()->getSize().y >> 1;


    //normalizing end pos to compute angle
    endPos.x -= startPos.x;
    endPos.y -= startPos.y;

    sightRectangle.setPosition(startPos);

    float angle = VectorHelper::angleBetween(endPos, sf::Vector2f(0.0f, 0.0f));
    if(angle < 0) angle += 2 * PI;

    angle = (angle * 180.0f / PI);

    //we check if the player could possibly see the other
    if(playerPlaying->isAngleValid(angle))
    {
        sightRectangle.setRotation(angle - 90);

        auto actors = mapManager.getActorList();

        for(Actor* actor : actors)
        {
            if(Collision::BoundingBoxTest(actor->getSprite(), sightRectangle))
            {
                Player* player = dynamic_cast<Player*>(actor);

                if(player)
                {
                    //here we could be hitting ourselves, if so we ignore it
                    if(player == &otherPlayer)
                        return true;
                }
                else
                    return false;
            }
        }
    }

    return false;
}

SceneGame::~SceneGame() = default;
