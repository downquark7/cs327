//
// Created by downq on 2/7/2023.
//

#include <stdlib.h>
#include "grid.h"

void initGrid(struct grid *g, int seed)
{
    g->seed = seed;
    int y, x;
    for (y = 0; y < GRID_HEIGHT; y++)
        for (x = 0; x < GRID_WIDTH; x++)
            g->maps[y][x] = NULL;
}

void setMapExits(struct map *m);

struct map *getMap(struct grid *g, int y, int x)
{
    struct map *m;
    y = y + (GRID_HEIGHT / 2);
    x = x + (GRID_HEIGHT / 2);
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x >= GRID_WIDTH) x = GRID_WIDTH - 1;
    if (y >= GRID_HEIGHT) y = GRID_HEIGHT - 1;
    if (g->maps[y][x] != NULL)
        return g->maps[y][x];
    m = static_cast<map *>(malloc(sizeof(struct map)));
    g->maps[y][x] = m;
    y = y - (GRID_HEIGHT / 2);
    x = x - (GRID_HEIGHT / 2);
    m->g = g;
    m->p.y = y;
    m->p.x = x;
    m->seed = g->seed + x + y + x * x + y * y;
    m->root = nullptr;
    setMapExits(m);
    generate(m);
    y = y + (GRID_HEIGHT / 2);
    x = x + (GRID_HEIGHT / 2);
    if (x == 0) m->cells[m->exits[0].p.y][0] = ROCK;
    if (y == 0) m->cells[0][m->exits[2].p.x] = ROCK;
    if (x == GRID_WIDTH - 1) m->cells[m->exits[1].p.y][MAP_WIDTH - 1] = ROCK;
    if (y == GRID_HEIGHT - 1) m->cells[MAP_HEIGHT - 1][m->exits[3].p.x] = ROCK;
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
        case 1:
            if (x < 0)
            {
                x++;
                exit = 0;
            }
            break;
        case 0:
            if (x > 0)
            {
                x--;
                exit = 1;
            }
            break;
        case 3:
            if (y < 0)
            {
                y++;
                exit = 2;
            }
            break;
        case 2:
            if (y > 0)
            {
                y--;
                exit = 3;
            }
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