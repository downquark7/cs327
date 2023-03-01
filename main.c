#include <stdio.h>
#include "map/map.h"
#include "map/grid.h"
#include "entity/entity.h"
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int y = 0, x = 0;
    struct grid g;
    struct map *m;
    initGrid(&g, time(NULL));
    printf("main seed: %d\n", g.seed);
    m = getMap(&g, y, x);
    srand(m->seed);
    addEntity(m, PC);
    addEntity(m, HIKER);
    addEntity(m, RIVAL);
    addEntity(m, SWIMMER);
    display(m);
}
