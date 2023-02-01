//
// Created by downq on 2/1/2023.
//

#ifndef CS327_TERRAIN_H
#define CS327_TERRAIN_H
#include "map.h"
void generateTerrainV0(struct map *m);
void clearMap(struct map *m);
void setSeeds(struct map *m);
void growSeeds(struct map *m);
void growSeedsIteration(struct map *m, int overwriteExisting);
char mostPopularNeighbor(char neighbors[8]);
#endif //CS327_TERRAIN_H
