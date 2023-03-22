//
// Created by downq on 2/20/2023.
//

#ifndef CS327_ENTITY_H
#define CS327_ENTITY_H

#include "../map/map.h"

#define PC '@'
#define HIKER 'h'
#define RIVAL 'r'
#define PACER 'p'
#define WANDERER 'w'
#define SENTRY 's'
#define EXPLORER 'e'
#define SWIMMER 'm'
#define PLACEHOLDER '`'

enum direction
{
    N, S, E, W, H, NW, NE, SW, SE, REST
};

struct entity
{
    char c;
    enum direction nextMove;
    int thisMoveCost;
    int nextMoveCost;
    int nextMoveTime;

    void (*getMove)(struct entity *e, struct map *m);

    void (*emove)(struct entity *e, struct map *m);

    struct p p;
};

void clearMapEntities(struct map *m);

int addEntity(struct map *m, char entity);

void addEntities(int num, struct map *m);

#endif //CS327_ENTITY_H
