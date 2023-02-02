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

//    for (i = 0; i < 4; i++)
//        m->cells[m->exits[i].p.y][m->exits[i].p.x].c = ROAD;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

void drawLine(struct map *m, int y1, int x1, int y2, int x2, char c)
{
    int y, x;
    if (y2 == y1)
    {
        y = y2;
        for (x = min(x2, x1); x <= max(x2, x1); x++)
            m->cells[y][x].c = c;
    } else if (x2 == x1)
    {
        x = x2;
        for (y = min(y2, y1); y <= max(y2, y1); y++)
            m->cells[y][x].c = c;
    }
}

void fillRoads(struct map *m)
{
    int y, x;
    int randx = 3 + (rand() % (MAP_WIDTH - 6));
    int randy = 3 + (rand() % (MAP_HEIGHT - 6));
    drawLine(m, m->exits[0].p.y, m->exits[0].p.x, m->exits[0].p.y, randx, ROAD);
    drawLine(m, m->exits[1].p.y, m->exits[1].p.x, m->exits[1].p.y, randx, ROAD);
    drawLine(m, m->exits[0].p.y, randx, m->exits[1].p.y, randx, ROAD);
    drawLine(m, m->exits[2].p.y, m->exits[2].p.x, randy, m->exits[2].p.x, ROAD);
    drawLine(m, m->exits[3].p.y, m->exits[3].p.x, randy, m->exits[3].p.x, ROAD);
    drawLine(m, randy, m->exits[2].p.x, randy, m->exits[3].p.x, ROAD);
}