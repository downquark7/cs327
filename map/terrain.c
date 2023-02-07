//
// Created by downq on 2/1/2023.
//
#include <stdlib.h>
#include "terrain.h"
#include <limits.h>

void generateTerrain(struct map *m)
{
    clearMap(m);
    seedsMethod(m);
}

void clearMap(struct map *m)
{
    int y, x;
    for (y = 0; y < MAP_HEIGHT; y++)
        for (x = 0; x < MAP_WIDTH; x++)
            m->cells[y][x].c = ' ';
}

int randX()
{
    return (rand() % (MAP_WIDTH - 2)) + 1;
}

int randY()
{
    return (rand() % (MAP_HEIGHT - 2)) + 1;
}

void seedsMethod(struct map *m)
{
    struct seed seeds[] = {
            {randY(), randX(), 2,  SHORT_GRASS},
            {randY(), randX(), 2,  SHORT_GRASS},
            {randY(), randX(), 2,  SHORT_GRASS},
            {randY(), randX(), 2,  SHORT_GRASS},
            {randY(), randX(), 3,  TALL_GRASS},
            {randY(), randX(), 3,  TALL_GRASS},
            {randY(), randX(), 3,  TALL_GRASS},
            {randY(), randX(), 3,  TALL_GRASS},
            {randY(), randX(), 3,  WATER},
            {randY(), randX(), 3,  WATER},
            {randY(), randX(), 3,  WATER},
            {randY(), randX(), 3,  WATER},
            {randY(), randX(), 4,  TREE},
            {randY(), randX(), 4,  TREE},
            {randY(), randX(), 4,  TREE},
            {randY(), randX(), 4,  TREE},
            {randY(), randX(), 20, ROCK},
            {randY(), randX(), 20, ROCK},
            {randY(), randX(), 20, ROCK},
            {randY(), randX(), 20, ROCK}
    };
    int y, x, min, d2, dx, dy, i;
    char c = ' ';
    for (y = 0; y < MAP_HEIGHT; y++)
        for (x = 0; x < MAP_WIDTH; x++)
        {
            min = INT_MAX;
            c = ' ';
            for (i = 0; i < 20; i++)
            {
                dy = y - seeds[i].y;
                dx = x - seeds[i].x;
                d2 = (seeds[i].weight) * (106 * (dy * dy) + 15 * (dx * dx));
                if (d2 < min)
                {
                    c = seeds[i].c;
                    min = d2;
                }
            }
            m->cells[y][x].c = c;
        }
}