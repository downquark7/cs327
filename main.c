#include <stdio.h>
#include "map/map.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int seed = time(NULL);
    printf("seed: %d\n", seed);
//    int seed = 1675295982;
    srand(seed);
    struct map m;
    setMapFunctions(&m);
    m.generate(&m);
    m.display(&m);
}