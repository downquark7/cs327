//
// Created by downq on 2/20/2023.
//

#include "entity.h"
#include "costs.h"
#include <stdlib.h>
#include <limits.h>

struct data
{
    int c;
    int v;
};

int getPathCost(struct p p, struct entity *e, struct map *m)
{
    struct data d[MAP_HEIGHT][MAP_WIDTH];
    int y, x;

    for (y = 0; y < MAP_HEIGHT; y++)
        for (x = 0; x < MAP_WIDTH; x++)
        {
            d[y][x].c = -1;
            d[y][x].v = 0;
        }

}

int getCost(char entity, char terrain)
{
    switch (terrain)
    {
        case ROAD:
            return entity == SWIMMER ? INT_MAX : 10;
        case 'C': // NOLINT(bugprone-branch-clone)
            if (entity == PC)
                return 10;
            return entity == SWIMMER ? INT_MAX : 50;
        case 'M':
            if (entity == PC)
                return 10;
            return entity == SWIMMER ? INT_MAX : 50;
        case TALL_GRASS:
            switch (entity)
            {
                default:
                    return 20;
                case SWIMMER:
                    return INT_MAX;
                case HIKER:
                    return 15;
            }
        case SHORT_GRASS:
            return entity == SWIMMER ? INT_MAX : 10;
        case TREE: // NOLINT(bugprone-branch-clone)
            return entity == HIKER ? 15 : INT_MAX;
        case ROCK:
            return entity == HIKER ? 15 : INT_MAX;
        case WATER:
            return entity == SWIMMER ? 7 : INT_MAX;
        default:
            return INT_MAX;
    }
}