//
// Created by downq on 2/20/2023.
//

#include "entity.h"
#include <stdlib.h>

void clearMapEntities(struct map *m)
{
    m->e = NULL;
    m->eCount = 0;
}