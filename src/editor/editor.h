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
	sf::Color clearColor;
	sf::Thread thread;
	
public:
    Editor();

    ~Editor() override;

    void update() override;
	void palette();
    void paint(sf::RenderWindow& window);

};


#endif //FORESTGUMPLITE_EDITOR_H
