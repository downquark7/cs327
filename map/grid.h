//
// Created by downq on 2/7/2023.
//

#ifndef CS327_GRID_H
#define CS327_GRID_H
#include "map.h"
#define GRID_HEIGHT 401
#define GRID_WIDTH 401
struct grid {
    //TODO: make "infinite"
    struct map *maps[GRID_HEIGHT][GRID_WIDTH];
    int seed;
};
void initGrid(struct grid *g, int seed);
struct map *getMap (struct grid *g, int y, int x);
#endif //CS327_GRID_H
