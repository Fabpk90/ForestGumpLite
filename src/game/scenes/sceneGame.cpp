//
// Created by fab on 14/11/18.
//

#include <iostream>
#include "../gameManager.h"
#include "sceneGame.h"
#include "../../util/Constants.h"
#include "../../util/Collision.h"
#include "../../util/VectorHelper.h"
#include "time.h"

SceneGame::SceneGame(const char* mapPath, const char* player1ImgPath
        , const char* player2ImgPath, bool IA)
: mapManager(mapPath), hud(), window(GameManager::Instance->getWindow())
{
    view.setSize(sf::Vector2f(GameManager::Instance->getWindow().getSize()));
    view.setCenter(0,0);

    GameManager::Instance->getWindow().setView(view);

    initHUD();

    isIAPlayer= IA;

    p1 = new Player(player1ImgPath, 10, true, hud);
    p2 = new Player(player2ImgPath, 10, false, hud);

    //p1->setPosition(mapManager.getFreePosition());
    p1->setPosition(sf::Vector2f(0, 0));
    p1->setOrientation(Player::UP);
    mapManager.addActor(p1);

    //p2->setPosition(mapManager.getFreePosition());
    p2->setPosition(sf::Vector2f(PIXEL_SIZE, 0));
    p2->setOrientation(Player::DOWN);
    mapManager.addActor(p2);

    //mapManager.setDrawLines(true);

    sightRectangle.setSize(sf::Vector2f(2, SCREEN_SIZE_WIDTH));

    isPlayer1Turn = false;
    changePlayerTurn();
}

void SceneGame::initHUD()
{
    hud.setActiveText(HUDManager::HEALTH, true);
    hud.setTextString(HUDManager::HEALTH, "0");

    hud.setActiveText(HUDManager::PLAYER, true);
    hud.setTextString(HUDManager::PLAYER, "Player1");

    hud.setActiveText(HUDManager::MOVEMENT, true);
    hud.setTextString(HUDManager::MOVEMENT, "Movement: 3");

    sf::Vector2f textPos = window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2, 0));

    textPos.x -= hud.getText(HUDManager::PLAYER).getLocalBounds().width
                        / 2;
    hud.setTextPosition(HUDManager::PLAYER
            , textPos);

    textPos = window.mapPixelToCoords(sf::Vector2i(window.getSize().x, 0));

    textPos.x -= hud.getText(HUDManager::MOVEMENT).getLocalBounds().width;

    hud.setTextPosition(HUDManager::MOVEMENT
            , textPos);

    textPos = window.mapPixelToCoords(sf::Vector2i(0, 0));
    hud.setTextPosition(HUDManager::HEALTH, textPos);
}

void SceneGame::update()
{
    if(isIAPlayer)
    {
        srand(time(NULL));
        int rng=rand()%5;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            switch (rng) {
                case 0: {
                    IA_Aim();
                    break;
                }
                case 1: {//Deplacement Gauche
                    IA_Move(-PIXEL_SIZE, 0);
                    IA_Aim();
                    break;
                }
                case 2: {//Deplacement Haut
                    IA_Move(0, PIXEL_SIZE);
                    IA_Aim();
                    break;
                }
                case 3: {//Deplacement Droite
                    IA_Move(PIXEL_SIZE, 0);
                    IA_Aim();
                    break;
                }
                case 4: {//Deplacement Bas
                    IA_Move(0, -PIXEL_SIZE);
                    IA_Aim();
                    break;
                }
                default:
                    break;
            }
        }
    }
    else
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && playerPlaying->getIsAiming()
                   && playerPlaying->getCanShoot())
                {
                    playerPlaying->setIsAiming(false);
                    mapManager.collisionAimCheck(*playerPlaying);
                    changePlayerTurn();
                }
                else if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
                {
                    playerPlaying->toggleAiming();
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                    playerPlaying->updateAimingLine(window.mapPixelToCoords(pixelPos));
                }
            }
            else if(event.type == sf::Event::MouseMoved)
            {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                playerPlaying->updateAimingLine(window.mapPixelToCoords(pixelPos));
            }
            else if (event.type == sf::Event::Closed)
                window.close();

            if(playerPlaying->getMovementRemaining())
                checkForPlayerMovement();
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();

    //draw stuff on the screen
    window.clear(GameManager::Instance->getClearColor());
    window.draw(mapManager);
    window.draw(hud);
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

    updatePlayerHUD();
}

bool SceneGame::checkPlayerSight()
{
    Player& otherPlayer = isPlayer1Turn ? *p2 : *p1;
    sf::Vector2f startPos = playerPlaying->getPosition();
    sf::Vector2f endPos = otherPlayer.getPosition();

    //centering the pos to the center of the player sprite
    startPos.x += playerPlaying->getSprite().getTexture()->getSize().x >> 1;
    startPos.y += playerPlaying->getSprite().getTexture()->getSize().y >> 1;

    //centering the pos to the center of the other player sprite
    endPos.x += otherPlayer.getSprite().getTexture()->getSize().x >> 1;
    endPos.y += otherPlayer.getSprite().getTexture()->getSize().y >> 1;

    //normalizing end pos to compute angle
    endPos.x -= startPos.x;
    endPos.y -= startPos.y;

    sightRectangle.setPosition(startPos);

    float angle = VectorHelper::angleBetween(endPos, sf::Vector2f(0.0f, 0.0f));
    if(angle < 0) angle += 2 * PI;

    angle = (angle * 180.0f / PI);

    //because of the collision check, we need to see if the other player has been touch
    //if it has, we need to see if it is the nearest
    std::list<Actor*> actorHit;
    float distanceMin = SCREEN_SIZE_WIDTH;

    //we check if the player could possibly see the other one
    if(playerPlaying->isAngleValid(angle))
    {
        sightRectangle.setRotation(angle - 90);

        auto actors = mapManager.getActorList();

        //first pass to see who's been hit
        for (Actor *actor : actors)
        {
            if (Collision::BoundingBoxTest(actor->getSprite(), sightRectangle))
            {
                actorHit.push_back(actor);
            }
        }

        Actor *nearestActor = nullptr;

        float distance = 0;
        //checking the nearest hit actor
        for (Actor* actor : actorHit)
        {
            distance = VectorHelper::getLength(actor->getPosition() - playerPlaying->getPosition());
            if (distanceMin > distance)
            {
                Player *player = dynamic_cast<Player *>(actor);

                if (player)
                {
                    //here we could be hitting ourselves, if so we ignore it
                    if (player == &otherPlayer)
                    {
                        nearestActor = actor;
                        distanceMin = distance;
                    }
                }
                else
                {
                    nearestActor = actor;
                    distanceMin = distance;
                }
            }
        }

        Player *player = dynamic_cast<Player *>(nearestActor);

        //here we could be hitting ourselves, if so we ignore it
        if (player && player == &otherPlayer)
        {
            return true;
        }
    }
    return false;
}

void SceneGame::checkForPlayerMovement()
{
    sf::Vector2f pos = playerPlaying->getPosition();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        pos += sf::Vector2f(-PIXEL_SIZE, 0);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        pos += sf::Vector2f(PIXEL_SIZE, 0);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        pos += sf::Vector2f(0, -PIXEL_SIZE);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        pos += sf::Vector2f(0, PIXEL_SIZE);

    if(pos != playerPlaying->getPosition() && mapManager.getIsPositionFree(pos))
    {
        playerPlaying->moveTo(pos);

        std::string str = "Movement:"+ std::to_string(playerPlaying->getMovementRemaining());
        hud.setTextString(HUDManager::MOVEMENT, str);

        if(checkPlayerSight())
        {
            if(isPlayer1Turn)
                p2->setToBeDrawn(true);
            else
                p1->setToBeDrawn(true);
        }
    }

}

void SceneGame::updatePlayerHUD()
{
    hud.deActivateAllTexts();

    hud.setActiveText(HUDManager::HEALTH, true);
    hud.setTextString(HUDManager::HEALTH, std::to_string(playerPlaying->getHealth()));

    if(playerPlaying->getHealth() < playerPlaying->getMaxHealth() >> 1)
    {
        hud.setTextColor(HUDManager::HEALTH, sf::Color::Red);
    }

    std::string str = "Player";
    std::string c = playerPlaying->isPlayerOne() ? "1" : "2";
    str.append(c);

    hud.setActiveText(HUDManager::PLAYER, true);
    hud.setTextString(HUDManager::PLAYER, str);

    str = "Movement:"+ std::to_string(playerPlaying->getMovementRemaining());

    hud.setActiveText(HUDManager::MOVEMENT, true);
    hud.setTextString(HUDManager::MOVEMENT, str);
}

SceneGame::~SceneGame()
{
    GameManager::Instance->getWindow().setView(
            GameManager::Instance->getWindow().getDefaultView());
}

void SceneGame::IA_Aim() {
    Player* whoPlay=playerPlaying;

    sf::Vector2i *playerPos = new sf::Vector2i((whoPlay == p1 ? p2 : p1)->getPosition());

    if(checkPlayerSight())
    {
        playerPlaying->toggleAiming();
        playerPlaying->updateAimingLine(window.mapPixelToCoords(*playerPos));
        if(playerPlaying->getCanShoot()) {
            playerPlaying->setIsAiming(false);
            mapManager.collisionAimCheck(*playerPlaying);
            changePlayerTurn();
        }
    }
    else
    {
        sf::Vector2i *anotherPos; //s'adapte à la l'orientation du joueur
        if(playerPlaying->getOrientation()==(Player::UP)) anotherPos = new sf::Vector2i((playerPlaying->getPosition().x)+2*PIXEL_SIZE,(playerPlaying->getPosition().y)+2*PIXEL_SIZE);
        else if(playerPlaying->getOrientation()==(Player::DOWN)) anotherPos = new sf::Vector2i((playerPlaying->getPosition().x)+2*PIXEL_SIZE,(playerPlaying->getPosition().y)-2*PIXEL_SIZE);
        else if(playerPlaying->getOrientation()==(Player::LEFT)) anotherPos = new sf::Vector2i((playerPlaying->getPosition().x)-2*PIXEL_SIZE,(playerPlaying->getPosition().y)+2*PIXEL_SIZE);
        else if(playerPlaying->getOrientation()==(Player::RIGHT)) anotherPos = new sf::Vector2i((playerPlaying->getPosition().x)+2*PIXEL_SIZE,(playerPlaying->getPosition().y)+2*PIXEL_SIZE);
        playerPlaying->toggleAiming();
        playerPlaying->updateAimingLine(window.mapPixelToCoords(*anotherPos));
        if(playerPlaying->getCanShoot()) {
            playerPlaying->setIsAiming(false);
            mapManager.collisionAimCheck(*playerPlaying);
            changePlayerTurn();
        }
    }
}

void SceneGame::IA_Move(int x, int y) {
    while(playerPlaying->getMovementRemaining())
    {
        sf::Vector2f pos = playerPlaying->getPosition();
        pos += sf::Vector2f(x, y);
        if(pos != playerPlaying->getPosition() && mapManager.getIsPositionFree(pos))
        {
            playerPlaying->moveTo(pos);

            std::string str = "Movement:"+ std::to_string(playerPlaying->getMovementRemaining());
            hud.setTextString(HUDManager::MOVEMENT, str);

            if(checkPlayerSight())
            {
                if(isPlayer1Turn)
                    p2->setToBeDrawn(true);
                else
                    p1->setToBeDrawn(true);
            }
        }
        else playerPlaying->setMovementRemaining(0);
    }
};
