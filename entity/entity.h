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
#define PLACEHOLDER '`'

enum direction
{
    N, S, E, W, H, NW, NE, SW, SE
};

struct entity
{
    char c;
    enum direction nextMove;
    int nextMoveCost;
    int nextMoveTime;
    struct p p;

    void (*getMove)(struct entity *e, struct map *m);

    void (*move)(struct entity *e, struct map *m);
};

void clearMapEntities(struct map *m);

void addEntity(struct map *m, char entity);

#endif //CS327_ENTITY_H
