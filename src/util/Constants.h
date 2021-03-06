//
// Created by fab on 18/11/2018.
//

#ifndef FORESTGUMPLITE_CONSTANTS_H
#define FORESTGUMPLITE_CONSTANTS_H

/*Player consts*/

#define PLAYER_MAX_POWER 5

/*  Screen constants  */

#define PIXEL_SIZE 32

#define SCREEN_SIZE_WIDTH 640
#define SCREEN_SIZE_HEIGHT 512

#define PIXEL_COUNT_HEIGHT (SCREEN_SIZE_HEIGHT >> 1) / PIXEL_SIZE
#define PIXEL_COUNT_WIDTH (SCREEN_SIZE_WIDTH >> 1) / PIXEL_SIZE

#define PI 3.14159265f

#define MOVEMENT_PER_TURN 3

/* Map constants  */
#define TILE_TREE 1
#define TILE_TREE_BIG 2
#define TILE_ROCK 3
#define TILE_ROCK_BIG 4

#define HEALTH_TREE 1
#define HEALTH_TREE_BIG 3

#define HEALTH_ROCK 1
#define HEALTH_ROCK_BIG 3

#endif //FORESTGUMPLITE_CONSTANTS_H
