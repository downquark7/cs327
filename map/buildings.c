//
// Created by downq on 2/1/2023.
//

#include "buildings.h"

void placeBuildings(struct map *m)
{
    int x;
    for (x = 2; x <= MAP_WIDTH - 4; x++)
    {
        if (m->cells[m->exits[1].p.y + 1][x].c != ROAD &&
            m->cells[m->exits[1].p.y + 1][x + 1].c != ROAD &&
            m->cells[m->exits[1].p.y + 2][x].c != ROAD &&
            m->cells[m->exits[1].p.y + 2][x + 1].c != ROAD &&
            m->cells[m->exits[1].p.y][x].c == ROAD &&
            m->cells[m->exits[1].p.y][x + 1].c == ROAD &&
            m->cells[m->exits[1].p.y][x + 2].c == ROAD &&
            m->cells[m->exits[1].p.y][x - 1].c == ROAD)
        {
            m->cells[m->exits[1].p.y + 1][x].c = 'C';
            m->cells[m->exits[1].p.y + 1][x + 1].c = 'C';
            m->cells[m->exits[1].p.y + 2][x].c = 'C';
            m->cells[m->exits[1].p.y + 2][x + 1].c = 'C';
            break;
        }
    }
    for (x = MAP_WIDTH - 4; x >= 2; x--)
    {
        if (m->cells[m->exits[0].p.y - 1][x].c != ROAD &&
            m->cells[m->exits[0].p.y - 1][x + 1].c != ROAD &&
            m->cells[m->exits[0].p.y - 2][x].c != ROAD &&
            m->cells[m->exits[0].p.y - 2][x + 1].c != ROAD &&
            m->cells[m->exits[0].p.y][x].c == ROAD &&
            m->cells[m->exits[0].p.y][x + 1].c == ROAD &&
            m->cells[m->exits[0].p.y][x + 2].c == ROAD &&
            m->cells[m->exits[0].p.y][x - 1].c == ROAD)
        {
            m->cells[m->exits[0].p.y - 1][x].c = 'M';
            m->cells[m->exits[0].p.y - 1][x + 1].c = 'M';
            m->cells[m->exits[0].p.y - 2][x].c = 'M';
            m->cells[m->exits[0].p.y - 2][x + 1].c = 'M';
            break;
        }
    }
}