#include <stdio.h>
#include "map/map.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
//    int seed = time(NULL);
    int seed = 1675714840;
    printf("seed: %d\n", seed);
    srand(seed);
    struct map m;
    setMapFunctions(&m);
    m.generate(&m);
    m.display(&m);
}