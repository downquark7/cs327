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

void displayToNcurses(struct map *m)
{
    mvprintw(1, 0, "y:%d x:%d seed: %d\n", m->p.y, m->p.x, m->seed);

    char saved[m->eCount];
    int i;
    for (i = 0; i < m->eCount; i++)
    {
        saved[i] = m->cells[m->e[i].p.y][m->e[i].p.x];
        m->cells[m->e[i].p.y][m->e[i].p.x] = m->e[i].c;
    }

    int y;
    for (y = 0; y < MAP_HEIGHT; y++)
        mvaddstr(y + 3, 0, m->cells[y]);

    for (i = 0; i < m->eCount; i++)
    {
        m->cells[m->e[i].p.y][m->e[i].p.x] = saved[i];
    }
    refresh();
}

void display(struct map *m)
{
    displayToNcurses(m);
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