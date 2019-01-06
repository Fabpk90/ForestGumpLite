//
// Created by fab on 28/11/18.
//

#ifndef FORESTGUMPLITE_EDITOR_H
#define FORESTGUMPLITE_EDITOR_H


#include "../game/scenes/scene.h"
#include "../map/mapManager.h"

class Editor  : public Scene{

private:
    MapManager mapManager;
	int brushType;
	int Health;
	sf::Color clearColor;
	sf::RenderWindow* winPalette;
	list<Actor*> obstaclesP;
	
	sf::View view;

public:
    Editor();

    ~Editor() override;

    void update() override;
    void paint(sf::RenderWindow& window);
	void brushSelect(sf::RenderWindow& window);
	void setHealth();
	void save();
	void load();
};


#endif //FORESTGUMPLITE_EDITOR_H
