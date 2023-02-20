//
// Created by downq on 2/20/2023.
//

#include "costs.h"
#include "entity.h"
#include <stdlib.h>

int getCost(char entity, char terrain)
{
    switch (terrain)
    {
        case ROAD:
            return entity == SWIMMER ? INT_MAX : 10;
        case 'C':
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
        case TREE:
            return entity == HIKER ? 15 : INT_MAX;
        case ROCK:
            return entity == HIKER ? 15 : INT_MAX;
        case WATER:
            return entity == SWIMMER ? 7 : INT_MAX;
        default:
            return INT_MAX;
    }
}