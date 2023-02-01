//
// Created by downq on 2/1/2023.
//
#include <stdlib.h>
#include "terrain.h"

void generateTerrainV0(struct map *m)
{
    clearMap(m);
    setSeeds(m);
    growSeeds(m);
}

void clearMap(struct map *m)
{
    int y, x;
    for (y = 0; y < MAP_HEIGHT; y++)
        for (x = 0; x < MAP_WIDTH; x++)
            m->cells[y][x].c = ' ';
}

char pickTerrainV0()
{
    int num = rand() % 100;
    if (num < 30)
        return SHORT_GRASS;
    if (num < 60)
        return TALL_GRASS;
    if (num < 80)
        return TREE;
    return WATER;
}

char mostPopularNeighbor(char neighbors[8])
{
    int i, o;
    int count[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int max = 0;
    for (i = 0; i < 8; i++)
        for (o = 0; o < 8; o++)
            if (neighbors[i] != ' ')
            {
                if (neighbors[i] == neighbors[o])
                    count[i] = count[i] + 1;
                if (count[i] > max)
                    max = count[i];
            }
    for (i = 0; i < 8; i++)
        if (count[i] == max)
            return neighbors[i];
    return ' ';
}

void setSeeds(struct map *m)
{
    int y, x;
//    int i;
//    for (i = 0; i < MAP_HEIGHT * MAP_WIDTH / 8; i++)
//    {
//        x = 2 + (rand() % (MAP_WIDTH - 4));
//        y = 2 + (rand() % (MAP_HEIGHT - 4));
//    }
    for (y = 1; y < MAP_HEIGHT - 1; y++)
        for (x = 1; x < MAP_WIDTH - 1; x++)
            m->cells[y][x].c = pickTerrainV0();
}

void growSeedsIteration(struct map *m, int overwriteExisting)
{
    struct map cells2;
    clearMap(&cells2);
    int y, x;
    char neighbors[8];
    for (y = 1; y < MAP_HEIGHT - 1; y++)
        for (x = 1; x < MAP_WIDTH - 1; x++)
        {
            if (overwriteExisting || m->cells[y][x].c == ' ')
            {
                neighbors[0] = m->cells[y + -1][x + -1].c;
                neighbors[1] = m->cells[y + -1][x + 0].c;
                neighbors[2] = m->cells[y + -1][x + 1].c;
                neighbors[3] = m->cells[y + 0][x + -1].c;
                neighbors[4] = m->cells[y + 0][x + 1].c;
                neighbors[5] = m->cells[y + 1][x + -1].c;
                neighbors[6] = m->cells[y + 1][x + 0].c;
                neighbors[7] = m->cells[y + 1][x + 1].c;
                cells2.cells[y][x].c = mostPopularNeighbor(neighbors);
            } else
                cells2.cells[y][x].c = m->cells[y][x].c;
        }
    for (y = 1; y < MAP_HEIGHT - 1; y++)
        for (x = 1; x < MAP_WIDTH - 1; x++)
        {
            if (overwriteExisting || m->cells[y][x].c == ' ')
            {
                neighbors[0] = cells2.cells[y + -1][x + -1].c;
                neighbors[1] = cells2.cells[y + -1][x + 0].c;
                neighbors[2] = cells2.cells[y + -1][x + 1].c;
                neighbors[3] = cells2.cells[y + 0][x + -1].c;
                neighbors[4] = cells2.cells[y + 0][x + 1].c;
                neighbors[5] = cells2.cells[y + 1][x + -1].c;
                neighbors[6] = cells2.cells[y + 1][x + 0].c;
                neighbors[7] = cells2.cells[y + 1][x + 1].c;
                m->cells[y][x].c = mostPopularNeighbor(neighbors);
            }
        }
}

void growSeeds(struct map *m)
{
    growSeedsIteration(m, 1);
    growSeedsIteration(m, 1);
    growSeedsIteration(m, 1);
//    growSeedsIteration(m, 1);
//    growSeedsIteration(m, 1);
}