//
// Created by downq on 2/20/2023.
//

#ifndef CS327_COSTS_H
#define CS327_COSTS_H

#include "../map/map.h"

void getDirection(struct p target, struct entity *e, struct map *m);

void getDirectionSwimmer(struct p target, struct entity *e, struct map *m);

int getCost(char entity, char terrain);

#endif //CS327_COSTS_H
