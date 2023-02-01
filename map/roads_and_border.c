//
// Created by downq on 2/1/2023.
//

#include "roads_and_border.h"
#include <stdlib.h>

void generateRoadsAndBorderV0(struct map *m)
{
    fillBoarder(m);
    placeExits(m);
    fillRoads(m);
}

void fillBoarder(struct map *m)
{
    int y, x;
    for (y = 0; y < MAP_HEIGHT; y++)
        for (x = 0; x < MAP_WIDTH; x++)
            if (x == 0 || x == (MAP_WIDTH - 1) ||
                y == 0 || y == (MAP_HEIGHT - 1))
//                if (m->cells[y][x].c != WATER)
                    m->cells[y][x].c = ROCK;
}

void placeExits(struct map *m)
{
    int i;
    m->exits[0].p.x = 0;
    m->exits[0].p.y = 2 + (rand() % (MAP_HEIGHT - 4));

    m->exits[1].p.x = MAP_WIDTH - 1;
    m->exits[1].p.y = 2 + (rand() % (MAP_HEIGHT - 4));

    m->exits[2].p.x = 2 + (rand() % (MAP_WIDTH - 4));
    m->exits[2].p.y = 0;

    m->exits[3].p.x = 2 + (rand() % (MAP_WIDTH - 4));
    m->exits[3].p.y = MAP_HEIGHT - 1;

    for (i = 0; i < 4; i++)
        m->cells[m->exits[i].p.y][m->exits[i].p.x].c = ROAD;
}

void fillRoads(struct map *m)
{

}