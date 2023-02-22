#include <stdio.h>
#include "map/map.h"
#include "map/grid.h"
#include "entity/entity.h"
#include "data/heap.h"
#include "entity/costs.h"
#include <time.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char *argv[])
{
    int y = 0, x = 0;
    struct grid g;
    struct map *m;
    initGrid(&g, time(NULL));
    printf("main seed: %d\n", g.seed);
    m = getMap(&g, y, x);

//    display(m);

    m->eCount = 1;
    m->e = malloc(sizeof(struct entity *) * m->eCount);
    struct entity *pc = &m->e[0];
    pc->c = PC;
    do
    {
        pc->p.y = (rand() % (MAP_HEIGHT - 4)) + 2;
        pc->p.x = (rand() % (MAP_WIDTH - 4)) + 2;
    } while (m->cells[pc->p.y][pc->p.x] != ROAD);
    display(m);

    struct p start = {3, 3};
    struct entity hiker = {HIKER, H, start, NULL};
    hiker.nextMove = getDirection(pc->p, &hiker, m);
    struct entity rival = {RIVAL, H, start, NULL};
    hiker.nextMove = getDirection(pc->p, &rival, m);
//    display(m);
}
