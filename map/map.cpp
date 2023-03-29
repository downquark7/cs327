//
// Created by downq on 1/30/2023.
//
#include <ncurses.h>
#include "map.h"
#include "terrain.h"
#include "roads_and_border.h"
#include "buildings.h"
#include "../entity/entity.h"
#include <stdlib.h>

void copyToSwimmerCells(struct map *m);

void displayEntities(struct map *m)
{
    int i;
    for (i = 0; i < m->eCount; i++)
        mvaddch(m->e[i].p.y + 1, m->e[i].p.x, m->e[i].c);
}

void displayToNcurses(struct map *m)
{
    mvprintw(0, 0, "y:%d x:%d seed: %d\n", m->p.y, m->p.x, m->seed);

    int y;
    for (y = 0; y < MAP_HEIGHT; y++)
        mvaddstr(y + 1, 0, m->cells[y]);
}

void display(struct map *m)
{
    displayToNcurses(m);
    displayEntities(m);
    refresh();
}

void generate(struct map *m)
{
    srand(m->seed);
    clearMapEntities(m);
    generateTerrain(m);
    copyToSwimmerCells(m);
    generateRoadsAndBorder(m);
    placeBuildings(m);
}

void copyToSwimmerCells(struct map *m)
{
    int y, x;
    for (y = 0; y < MAP_HEIGHT; y++)
        for (x = 0; x < MAP_WIDTH + 1; x++)
            if (x == 0 || x == (MAP_WIDTH - 1) ||
                y == 0 || y == (MAP_HEIGHT - 1))
                m->swimmerCells[y][x] = ROCK;
            else
                m->swimmerCells[y][x] = m->cells[y][x];
}