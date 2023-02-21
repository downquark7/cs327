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

    char saved[m->eCount];
    int i;
    for (i = 0; i < m->eCount; i++)
    {
        saved[i] = m->cells[m->e[i].p.y][m->e[i].p.x];
        m->cells[m->e[i].p.y][m->e[i].p.x] = m->e[i].c;
    }

    int y;
    for (y = 0; y < MAP_HEIGHT; y++)
        printf("%s\n", m->cells[y]);

    for (i = 0; i < m->eCount; i++)
    {
        m->cells[m->e[i].p.y][m->e[i].p.x] = saved[i];
    }
}

void display(struct map *m)
{
    displayToPrintf(m);
}

void generate(struct map *m)
{
    srand(m->seed);
    clearMapEntities(m);
    generateTerrain(m);
    generateRoadsAndBorder(m);
    placeBuildings(m);
}