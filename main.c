#include <stdio.h>
#include "map/map.h"
#include "map/grid.h"
#include <time.h>

int main(int argc, char *argv[])
{
    int y = 0, x = 0;
    struct grid g;
    struct map *m;
    initGrid(&g, time(NULL));
    printf("main seed: %d\n", g.seed);
    m = getMap(&g, y, x);
    y = m->p.y;
    x = m->p.x;
    display(m);
}