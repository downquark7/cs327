//
// Created by downq on 2/1/2023.
//

#include "roads_and_border.h"
#include <stdlib.h>

void generateRoadsAndBorder(struct map *m)
{
    fillBoarder(m);
    fillRoads(m);
}

void fillBoarder(struct map *m)
{
    int y, x;
    for (y = 0; y < MAP_HEIGHT; y++)
        for (x = 0; x < MAP_WIDTH; x++)
            if (x == 0 || x == (MAP_WIDTH - 1) ||
                y == 0 || y == (MAP_HEIGHT - 1))
                m->cells[y][x] = ROCK;
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
            m->cells[y][x] = c;
    } else if (x2 == x1)
    {
        x = x2;
        for (y = min(y2, y1); y <= max(y2, y1); y++)
            m->cells[y][x] = c;
    }
}

void fillRoads(struct map *m)
{
    int randx = 4 + (rand() % (MAP_WIDTH - 8));
    int randy = 4 + (rand() % (MAP_HEIGHT - 8));
    drawLine(m, m->exits[0].p.y, m->exits[0].p.x, m->exits[0].p.y, randx, ROAD);
    drawLine(m, m->exits[0].p.y, randx, m->exits[1].p.y, randx, ROAD);
    drawLine(m, m->exits[1].p.y, m->exits[1].p.x, m->exits[1].p.y, randx, ROAD);
    drawLine(m, m->exits[2].p.y, m->exits[2].p.x, randy, m->exits[2].p.x, ROAD);
    drawLine(m, randy, m->exits[2].p.x, randy, m->exits[3].p.x, ROAD);
    drawLine(m, m->exits[3].p.y, m->exits[3].p.x, randy, m->exits[3].p.x, ROAD);
}