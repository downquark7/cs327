//
// Created by downq on 2/1/2023.
//

#include <stdlib.h>
#include "buildings.h"

int buildingSpawnRandomizer(int d)
{
    if (d == 0)
        return 1;
    if (d > 200)
        return (rand() % 20) == 0;
    return (rand() % 50) < (-45 * d / 200 + 50);
}

void placeBuildings(struct map *m)
{
    int x;
    if (buildingSpawnRandomizer(abs(m->p.x) + abs(m->p.y)))
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
    if (buildingSpawnRandomizer(abs(m->p.x) + abs(m->p.y)))
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