//
// Created by downq on 2/20/2023.
//

#ifndef CS327_ENTITY_H
#define CS327_ENTITY_H

#include "../map/map.h"

#define PC '@'
#define HIKER 'H'
#define RIVAL 'R'
#define SWIMMER 'S'

enum direction
{
    N, S, E, W, H
};

struct entity
{
    char c;
    enum direction nextMove;

    void (*move)(struct entity *e);
};

void clearMapEntities(struct map *m);

#endif //CS327_ENTITY_H
