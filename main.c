#include <stdio.h>
#include "map/map.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int seed = 42;
    srand(seed);
//    printf("seed: %d\n", seed);
    struct map m;
    m.generate(&m);
    m.display(&m);
}