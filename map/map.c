//
// Created by downq on 1/30/2023.
//
#include "map.h"
#include "terrain.h"
#include "roads_and_border.h"
#include "buildings.h"
#include <stdio.h>

void setMapFunctions(struct map *m)
{
    m->display = displayToPrintf;
    m->generate = generateV0;
}

void displayToPrintf(struct map *m)
{
    int y, x;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
            printf("%c", m->cells[y][x].c);
        printf("\n");
    }
}

void generateV0(struct map *m)
{
    generateTerrainV0(m);
    generateRoadsAndBorderV0(m);
    placeBuildingsV0(m);
}