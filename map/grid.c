//
// Created by downq on 2/7/2023.
//

#include <stdlib.h>
#include "grid.h"

void initGrid(struct grid *g, int seed)
{
    int y, x;
    for (y = 0; y < GRID_HEIGHT; y++)
        for (x = 0; x < GRID_WIDTH; x++)
            g->maps[y][x] = NULL;
}

void setMapExits(struct map *m);

struct map *getMap(struct grid *g, int y, int x)
{
    if (g->maps[y][x] != NULL)
        return g->maps[y][x];
    struct map *m = g->maps[y][x] = malloc(sizeof(struct map));
    if (m == NULL)
        abort();
    m->g = g;
    m->p.y = y;
    m->p.x = x;
    m->seed = g->seed + x + y + x * x + y * y;
    setMapExits(m);
    generate(m);
    return m;
}

int randy()
{
    return 4 + (rand() % (MAP_HEIGHT - 8));
}

int randx()
{
    return 4 + (rand() % (MAP_WIDTH - 8));
}

int getNum(int seed, int exit, int y, int x)
{
    switch (exit)
    {
        case 0://x-
            if (x < 0)
                x++;
            break;
        case 1://x+
            if (x > 0)
                x--;
            break;
        case 2://y-
            if (y < 0)
                y++;
            break;
        case 3://y+
            if (y > 0)
                y--;
            break;
        default:
            abort();
    }
    srand(seed + x + y + exit + x * x + y * y + exit * exit);
    if (exit == 0 || exit == 1)
        return randy();
    return randx();
}

void setMapExits(struct map *m)
{
    m->exits[0].p.x = 0;
    m->exits[0].p.y = getNum(m->g->seed, 0, m->p.y, m->p.x);
    m->exits[1].p.x = MAP_WIDTH - 1;
    m->exits[1].p.y = getNum(m->g->seed, 1, m->p.y, m->p.x);
    m->exits[2].p.x = getNum(m->g->seed, 2, m->p.y, m->p.x);
    m->exits[2].p.y = 0;
    m->exits[3].p.x = getNum(m->g->seed, 3, m->p.y, m->p.x);
    m->exits[3].p.y = MAP_HEIGHT - 1;
}