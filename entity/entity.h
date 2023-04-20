//
// Created by downq on 2/20/2023.
//

#ifndef CS327_ENTITY_H
#define CS327_ENTITY_H

#include "../map/map.h"
#include "../data/pokemon.h"

#define PC '@'
#define HIKER 'h'
#define RIVAL 'r'
#define PACER 'p'
#define WANDERER 'w'
#define SENTRY 's'
#define EXPLORER 'e'
#define SWIMMER 'm'
#define PLACEHOLDER '`'
#define WILD '7'

enum direction
{
    N, S, E, W, NW, NE, SW, SE, H, REST, QUIT, FLY
};

struct entity
{
    char c;
    enum direction nextMove;
    int nextMoveCost;
    int nextMoveTime;

    void (*getMove)(struct entity *e, struct map *m);

    void (*emove)(struct entity *e, struct map *m);

    struct p p;

    pokemon *party[6];
};

void clearMapEntities(struct map *m);

int addEntity(struct map *m, char entity);

int transferEntity(struct map *m, struct entity *e);

int copyPC(struct map *m, struct entity *e);

void addEntities(int num, struct map *m);

void addEntities(int num, struct map *m, struct entity *e);

void defeated(struct entity *e, struct map *m);

int checkBounds(struct p p);

#endif //CS327_ENTITY_H
