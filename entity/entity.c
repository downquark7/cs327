//
// Created by downq on 2/20/2023.
//

#include "entity.h"
#include <stdlib.h>

void clearMapEntities(struct map *m)
{
    int y, x;
    for (y = 0; y < MAP_HEIGHT; y++)
        for (x = 0; x < MAP_WIDTH; x++)
            m->e = NULL;
}