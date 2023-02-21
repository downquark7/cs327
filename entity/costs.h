//
// Created by downq on 2/20/2023.
//

#ifndef CS327_COSTS_H
#define CS327_COSTS_H

#include "../map/map.h"

int getPathCost(struct p p, struct entity *e, struct map *m);

int getCost(char entity, char terrain);

#endif //CS327_COSTS_H
