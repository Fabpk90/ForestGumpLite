//
// Created by fab on 14/11/18.
//

#include <iostream>
#include <cstdlib>
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

    p1->setPosition(mapManager.getFreePosition());
    p1->setOrientation(Player::UP);
	p1->getSprite().setTextureRect(sf::IntRect(0,32,32,32));

    mapManager.addActor(p1);

    p2->setPosition(mapManager.getFreePosition());
    p2->setOrientation(Player::DOWN);
    p2->getSprite().setTextureRect(sf::IntRect(32,0,32,32));
    
    mapManager.addActor(p2);

    sightRectangle.setSize(sf::Vector2f(2, SCREEN_SIZE_WIDTH));

    playerPlaying = p2;
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
        //if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            handleAITurn();
    }
    else
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type==sf::Event::KeyPressed && sf::Keyboard::isKeyPressed((sf::Keyboard::P))) changePlayerTurn();

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

        if(playerPlaying->getMovementRemaining() && !playerPlaying->getIsAiming())
            checkForPlayerMovement();
            
        if(!playerPlaying->getIsAiming())
			checkForPlayerTurning();
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

void SceneGame::handleAITurn()
{
    srand(time(NULL));
    int rng=rand()%5;
	
	checkForPlayerTurning(rng);
    switch(rng)
        {
            case 0: {
                IA_Aim();
                break;
            }
            case 1: {//Deplacement Gauche
								
                while(playerPlaying->getMovementRemaining())
                {
                    if(playerPlaying->getPosition().x-PIXEL_SIZE>=(-SCREEN_SIZE_WIDTH/2))
                        moveIA(sf::Vector2f(-PIXEL_SIZE, 0));
                    playerPlaying->setMovementRemaining(0);
                }
                IA_Aim();
                break;
            }
            case 2:{//Deplacement Bas
								
                while(playerPlaying->getMovementRemaining())
                {
                    if(playerPlaying->getPosition().y+PIXEL_SIZE<SCREEN_SIZE_HEIGHT/2)
                        moveIA(sf::Vector2f(0, PIXEL_SIZE));
                    playerPlaying->setMovementRemaining(0);
                }
                IA_Aim();
                break;
            }
            case 3: {//Deplacement Droite
								
                while(playerPlaying->getMovementRemaining())
                {
                    if(playerPlaying->getPosition().x+PIXEL_SIZE<SCREEN_SIZE_WIDTH/2)
                        moveIA(sf::Vector2f(PIXEL_SIZE, 0));
                    playerPlaying->setMovementRemaining(0);
                }
                IA_Aim();
                break;
            }
            case 4: {//Deplacement Haut

                while(playerPlaying->getMovementRemaining())
                {
                    if(playerPlaying->getPosition().y-PIXEL_SIZE>=(-SCREEN_SIZE_HEIGHT/2))
                     moveIA(sf::Vector2f(0, -PIXEL_SIZE));
                    playerPlaying->setMovementRemaining(0);
                }
                IA_Aim();
                break;
            }
            default: break;
        }
        
    window.clear(GameManager::Instance->getClearColor());
    window.draw(mapManager);
    window.draw(hud);
    window.display();
}

void SceneGame::moveIA(sf::Vector2f vec) {
    sf::Vector2f pos = playerPlaying->getPosition();
    pos += vec;
    validateAndMovePos(pos);
}

void SceneGame::changePlayerTurn()
{
    playerPlaying->setIsAiming(false);

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
    startPos.x += (playerPlaying->getSprite().getTexture()->getSize().x >> 2);
    startPos.y += (playerPlaying->getSprite().getTexture()->getSize().y >> 2);

    //centering the pos to the center of the other player sprite
    endPos.x += (otherPlayer.getSprite().getTexture()->getSize().x >> 2);
    endPos.y += (otherPlayer.getSprite().getTexture()->getSize().y >> 2);

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

    validateAndMovePos(pos);

}

void SceneGame::validateAndMovePos(const sf::Vector2f &pos)
{
    if(pos != playerPlaying->getPosition() && mapManager.getIsPositionFree(pos))
    {
        playerPlaying->moveTo(pos);

        string str = "Movement:"+ to_string(playerPlaying->getMovementRemaining());
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

//Use ZQSD to change orientation
void SceneGame::checkForPlayerTurning(int AITurning)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || AITurning == 4)
		{
			playerPlaying->setOrientation(Player::UP);
			
			playerPlaying->getSprite().setTextureRect(sf::IntRect(0,32,32,32));
			
		}
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)  || AITurning == 3)
        {
			playerPlaying->setOrientation(Player::RIGHT);
			playerPlaying->getSprite().setTextureRect(sf::IntRect(0,0,32,32));
		}
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)  || AITurning == 2)
		{
			playerPlaying->setOrientation(Player::DOWN);
			playerPlaying->getSprite().setTextureRect(sf::IntRect(32,0,32,32));
		}
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)  || AITurning == 1)
        {
			playerPlaying->setOrientation(Player::LEFT);
			playerPlaying->getSprite().setTextureRect(sf::IntRect(32,32,32,32));
		}
		
	//After turning we check whether or not to draw the other player
	if(AITurning == 0)
	{
		if(checkPlayerSight())
		{
			if(isPlayer1Turn)
				p2->setToBeDrawn(true);
			else
				p1->setToBeDrawn(true);
		}
		else
		{
			if(isPlayer1Turn)
				p2->setToBeDrawn(false);
			else
				p1->setToBeDrawn(false);
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
    GameManager::Instance->getWindow().setView(GameManager::Instance->getWindow().getDefaultView());
}

void SceneGame::IA_Aim() {
    if(checkPlayerSight())//Initialise la vision des joueurs
    {
        if(isPlayer1Turn)
            p2->setToBeDrawn(true);
        else
            p1->setToBeDrawn(true);
    }

    if(p1->getToBeDrawn() && p2->getToBeDrawn())//Permet de savoir si le joueur voit l'autre joueur
    {
        playerPlaying->toggleAiming();
        sf::Vector2i *playerPos = new sf::Vector2i((isPlayer1Turn ? p2 : p1)->getPosition());
        playerPlaying->updateAimingLine(window.mapPixelToCoords(*playerPos));//Vise le joueur ennemi si il le voit
        if(playerPlaying->getHealth()>playerPlaying->getPowerInUse())//Le joueur peut-il tirer?
        {
            playerPlaying->setIsAiming(false);
            mapManager.collisionAimCheck(*playerPlaying);
            if(isPlayer1Turn)
            {
                std::cout<<"P1 Shot on P2"<<std::endl;
            }
            else
            {
                std::cout<<"P2 Shot on P1"<<std::endl;
            }
            changePlayerTurn();
        } else
        {
            playerPlaying->setIsAiming(false);
            changePlayerTurn();//Si il ne peut pas tirer, il passe
        }
    }
    else changePlayerTurn();
}
