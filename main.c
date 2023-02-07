#include <stdio.h>
#include "map/map.h"
#include "map/grid.h"
#include <time.h>

int main(int argc, char *argv[])
{
    int y = 0, x = 0;
    struct grid g;
    struct map *m;
    char buf[255];
    char c;
    initGrid(&g, time(NULL));
    printf("main seed: %d\n", g.seed);
    while (1)
    {
        m = getMap(&g, y, x);
        y = m->p.y;
        x = m->p.x;
        display(m);
        fgets(buf, 255, stdin);
        if (buf[0] == 'n')
            y--;
        if (buf[0] == 's')
            y++;
        if (buf[0] == 'e')
            x++;
        if (buf[0] == 'w')
            x--;
        if (buf[0] == 'q')
            break;
        if (buf[0] == 'f')
            sscanf(buf, "%c%d%d", &c, &x, &y);
    }
}