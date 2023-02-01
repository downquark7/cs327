//
// Created by downq on 2/1/2023.
//

#ifndef CS327_TERRAIN_H
#define CS327_TERRAIN_H
#include "map.h"
void generateTerrainV0(struct map *m);
void clearMap(struct map *m);
struct seed
{
    int y, x;
    int weight;
    char c;
};
void seedsMethod(struct map *m);
#endif //CS327_TERRAIN_H
