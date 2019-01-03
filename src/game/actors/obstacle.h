//
// Created by fab on 07/11/18.
//

#ifndef FORESTGUMPLITE_OBSTACLE_H
#define FORESTGUMPLITE_OBSTACLE_H

#include "../../map/mapManager.h"
#include "actor.h"

class Obstacle : public Actor
{
	private:
	int type;
		
	public:
		Obstacle(const char* path, int health, int x, int y, int type);
		int getType();
		void setType(int type);
		void onDie();
};


#endif //FORESTGUMPLITE_OBSTACLE_H
