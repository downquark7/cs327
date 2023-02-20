//
// Created by downq on 1/30/2023.
//
#include "map.h"
#include "terrain.h"
#include "roads_and_border.h"
#include "buildings.h"
#include "../entity/entity.h"
#include <stdio.h>
#include <stdlib.h>

void displayToPrintf(struct map *m)
{
    printf("y:%d x:%d seed: %d\n", m->p.y, m->p.x, m->seed);
    int y, x;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
            printf("%c", m->cells[y][x].c);
        printf("\n");
    }
}

void display(struct map *m)
{
    displayToPrintf(m);
}

void generate(struct map *m)
{
    clearMapEntities(m);
    srand(m->seed);
    generateTerrain(m);
    generateRoadsAndBorder(m);
    placeBuildings(m);
}