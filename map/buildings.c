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
    return (rand() % 100) < (-45 * d / 200 + 50);
}

void placeBuildings(struct map *m)
{
    int x;
    if (buildingSpawnRandomizer(abs(m->p.x) + abs(m->p.y)))
    {
        for (x = 2; x <= MAP_WIDTH - 4; x++)
        {
            if (m->cells[m->exits[1].p.y + 1][x] != ROAD &&
                m->cells[m->exits[1].p.y + 1][x + 1] != ROAD &&
                m->cells[m->exits[1].p.y + 2][x] != ROAD &&
                m->cells[m->exits[1].p.y + 2][x + 1] != ROAD &&
                m->cells[m->exits[1].p.y][x] == ROAD &&
                m->cells[m->exits[1].p.y][x + 1] == ROAD &&
                m->cells[m->exits[1].p.y][x + 2] == ROAD &&
                m->cells[m->exits[1].p.y][x - 1] == ROAD)
            {
                m->cells[m->exits[1].p.y + 1][x] = 'C';
                m->cells[m->exits[1].p.y + 1][x + 1] = 'C';
                m->cells[m->exits[1].p.y + 2][x] = 'C';
                m->cells[m->exits[1].p.y + 2][x + 1] = 'C';
                break;
            }
        }
        for (x = MAP_WIDTH - 4; x >= 2; x--)
        {
            if (m->cells[m->exits[0].p.y - 1][x] != ROAD &&
                m->cells[m->exits[0].p.y - 1][x + 1] != ROAD &&
                m->cells[m->exits[0].p.y - 2][x] != ROAD &&
                m->cells[m->exits[0].p.y - 2][x + 1] != ROAD &&
                m->cells[m->exits[0].p.y][x] == ROAD &&
                m->cells[m->exits[0].p.y][x + 1] == ROAD &&
                m->cells[m->exits[0].p.y][x + 2] == ROAD &&
                m->cells[m->exits[0].p.y][x - 1] == ROAD)
            {
                m->cells[m->exits[0].p.y - 1][x] = 'M';
                m->cells[m->exits[0].p.y - 1][x + 1] = 'M';
                m->cells[m->exits[0].p.y - 2][x] = 'M';
                m->cells[m->exits[0].p.y - 2][x + 1] = 'M';
                break;
            }
        }
    }
}