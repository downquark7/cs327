#include <stdio.h>
#include "map/map.h"

int main(int argc, char *argv[])
{
    struct map m;
    m.generate(&m);
    m.display(&m);
}