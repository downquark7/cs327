//
// Created by downq on 2/1/2023.
//
#include <stdlib.h>
#include "terrain.h"

void generateTerrainV0(struct map *m)
{
    clearMap(m);
    setSeeds(m);
    m->display(m);
    growSeeds(m);
}

void clearMap(struct map *m)
{
    int y, x;
    for (y = 0; y < MAP_HEIGHT; y++)
        for (x = 0; x < MAP_WIDTH; x++)
            m->cells[y][x].c = ' ';
}

char pickTerrain()
{
    int num = rand() % 8192;
    if (num < 28)
        return SHORT_GRASS;
    if (num < 52)
        return TALL_GRASS;
    if (num < 76)
        return TREE;
    if (num < 100)
        return WATER;
    return ' ';
}

char mostPopularNeighbor(char neighbors[9])
{
    int i, o;
    double count[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    double max = 0;
    double cw = .5313;
    double ew = .9717;
    double sw = 1;
    double weight[] = {cw, ew, cw, ew, sw, ew, cw, ew, cw};
    for (i = 0; i < 9; i++)
        for (o = 0; o < 9; o++)
            if (neighbors[i] != ' ')
            {
                if (neighbors[i] == neighbors[o])
                    count[i] = count[i] + weight[i];
                if (count[i] > max)
                    max = count[i];
            }
    for (i = 0; i < 8; i++)
        if (count[i] == max)
            return neighbors[i];
    return ' ';
}

char mostPopularNeighborSquare(char neighbors[9])
{
    int i, o;
    double count[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    double max = 0;
    double cw = 1;
    double ew = 1;
    double sw = 0;
    double weight[] = {cw, ew, cw, ew, sw, ew, cw, ew, cw};
    for (i = 0; i < 9; i++)
        for (o = 0; o < 9; o++)
            if (neighbors[i] != ' ')
            {
                if (neighbors[i] == neighbors[o])
                    count[i] = count[i] + weight[i];
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
    for (y = 3; y < MAP_HEIGHT - 3; y++)
        for (x = 3; x < MAP_WIDTH - 3; x++)
            m->cells[y][x].c = pickTerrain();
}

void growSeedsIteration(struct map *m, int overwriteExisting)
{
    struct map cells2;
    clearMap(&cells2);
    int y, x;
    char neighbors[9];
    for (y = 1; y < MAP_HEIGHT - 1; y++)
        for (x = 1; x < MAP_WIDTH - 1; x++)
        {
            if (overwriteExisting || m->cells[y][x].c == ' ')
            {
                neighbors[0] = m->cells[y + -1][x + -1].c;
                neighbors[1] = m->cells[y + -1][x + 0].c;
                neighbors[2] = m->cells[y + -1][x + 1].c;
                neighbors[3] = m->cells[y + 0][x + -1].c;
                neighbors[4] = m->cells[y + 0][x + 0].c;
                neighbors[5] = m->cells[y + 0][x + 1].c;
                neighbors[6] = m->cells[y + 1][x + -1].c;
                neighbors[7] = m->cells[y + 1][x + 0].c;
                neighbors[8] = m->cells[y + 1][x + 1].c;
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
                neighbors[4] = cells2.cells[y + 0][x + 0].c;
                neighbors[5] = cells2.cells[y + 0][x + 1].c;
                neighbors[6] = cells2.cells[y + 1][x + -1].c;
                neighbors[7] = cells2.cells[y + 1][x + 0].c;
                neighbors[8] = cells2.cells[y + 1][x + 1].c;
                m->cells[y][x].c = mostPopularNeighbor(neighbors);
            }
        }
}

void growSeeds(struct map *m)
{
    growSeedsIteration(m, 1);
//    growSeedsIteration(m, 1);
//    growSeedsIteration(m, 1);
//    growSeedsIteration(m, 1);
//    growSeedsIteration(m, 1);
//    growSeedsIteration(m, 1);
//    growSeedsIteration(m, 1);
}