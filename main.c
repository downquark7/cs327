#include <stdio.h>
#include "map/map.h"
#include "map/grid.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    struct grid g;
    initGrid(&g, time(NULL));
    printf("main seed: %d\n", g.seed);
//    int seed = 1675295982;
    struct map *m = getMap(&g, 0, 0);
    generate(m);
    display(m);
}