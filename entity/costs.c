//
// Created by downq on 2/20/2023.
//

#include "entity.h"
#include "costs.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../data/heap.h"

int chebyshevDistance(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    return (dx > dy) ? dx : dy;
}

int manhattanDistance(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    return dx + dy;
}

int squareDistance(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    return dx * dx + dy * dy;
}

int zeroDistance(int x1, int y1, int x2, int y2)
{
    return 0;
}

int visuallyCorrectedDistance(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    return 106 * (dy * dy) + 15 * (dx * dx);
}

int heuristic(int x1, int y1, int x2, int y2)
{
    return visuallyCorrectedDistance(x1, y1, x2, y2);
}

enum direction getDirection(struct p target, struct entity *e, struct map *m)
{
    int y, x;
    int costs[MAP_HEIGHT][MAP_WIDTH];
    for (y = 0; y < MAP_HEIGHT; y++)
        for (x = 0; x < MAP_WIDTH; x++)
            costs[y][x] = -1;

    int cost;
    struct p *p = malloc(sizeof(struct p));
    p->y = target.y;
    p->x = target.x;
    node *root = NULL;
    root = insert(root, 0, p);

    while (root != NULL)
    {
        struct p *min = (struct p *) (root->data);

        //cost = -1 if not visited
        if (costs[min->y][min->x] == -1)
        {
            costs[min->y][min->x] = root->key;

//            if ((min->x == e->p.x && min->y == e->p.y))
//            {
//                deleteAll(root);
//                break;
//            }

            if (costs[min->y - 1][min->x - 1] < 0)
            {
                if (min->x >= 2 && min->x < MAP_WIDTH - 2 && min->y >= 2 && min->y < MAP_HEIGHT - 2 &&
                    (cost = root->key + getCost(e->c, m->cells[min->y - 1][min->x - 1])) > 0 &&
                    cost != INT_MAX)
                {
                    p = malloc(sizeof(struct p));
                    p->y = min->y - 1;
                    p->x = min->x - 1;
                    cost += heuristic(p->x, p->y, e->p.x, e->p.y);
                    root = insert(root, cost, p);
                }
            }

            if (costs[min->y - 1][min->x] < 0)
            {
                if (min->x >= 2 && min->x < MAP_WIDTH - 2 && min->y >= 2 && min->y < MAP_HEIGHT - 2 &&
                    (cost = root->key + getCost(e->c, m->cells[min->y - 1][min->x])) > 0 &&
                    cost != INT_MAX)
                {
                    p = malloc(sizeof(struct p));
                    p->y = min->y - 1;
                    p->x = min->x;
                    cost += heuristic(p->x, p->y, e->p.x, e->p.y);
                    root = insert(root, cost, p);
                }
            }

            if (costs[min->y - 1][min->x + 1] < 0)
            {
                if (min->x >= 2 && min->x < MAP_WIDTH - 2 && min->y >= 2 && min->y < MAP_HEIGHT - 2 &&
                    (cost = root->key + getCost(e->c, m->cells[min->y - 1][min->x + 1])) > 0 &&
                    cost != INT_MAX)
                {
                    p = malloc(sizeof(struct p));
                    p->y = min->y - 1;
                    p->x = min->x + 1;
                    cost += heuristic(p->x, p->y, e->p.x, e->p.y);
                    root = insert(root, cost, p);
                }
            }

            if (costs[min->y][min->x - 1] < 0)
            {
                if (min->x >= 2 && min->x < MAP_WIDTH - 2 && min->y >= 2 && min->y < MAP_HEIGHT - 2 &&
                    (cost = root->key + getCost(e->c, m->cells[min->y][min->x - 1])) > 0 &&
                    cost != INT_MAX)
                {
                    p = malloc(sizeof(struct p));
                    p->y = min->y;
                    p->x = min->x - 1;
                    cost += heuristic(p->x, p->y, e->p.x, e->p.y);
                    root = insert(root, cost, p);
                }
            }

            if (costs[min->y][min->x + 1] < 0)
            {
                if (min->x >= 2 && min->x < MAP_WIDTH - 2 && min->y >= 2 && min->y < MAP_HEIGHT - 2 &&
                    (cost = root->key + getCost(e->c, m->cells[min->y][min->x + 1])) > 0 &&
                    cost != INT_MAX)
                {
                    p = malloc(sizeof(struct p));
                    p->y = min->y;
                    p->x = min->x + 1;
                    cost += heuristic(p->x, p->y, e->p.x, e->p.y);
                    root = insert(root, cost, p);
                }
            }

            if (costs[min->y + 1][min->x - 1] < 0)
            {
                if (min->x >= 2 && min->x < MAP_WIDTH - 2 && min->y >= 2 && min->y < MAP_HEIGHT - 2 &&
                    (cost = root->key + getCost(e->c, m->cells[min->y + 1][min->x - 1])) > 0 &&
                    cost != INT_MAX)
                {
                    p = malloc(sizeof(struct p));
                    p->y = min->y + 1;
                    p->x = min->x - 1;
                    cost += heuristic(p->x, p->y, e->p.x, e->p.y);
                    root = insert(root, cost, p);
                }
            }

            if (costs[min->y + 1][min->x] < 0)
            {
                if (min->x >= 2 && min->x < MAP_WIDTH - 2 && min->y >= 2 && min->y < MAP_HEIGHT - 2 &&
                    (cost = root->key + getCost(e->c, m->cells[min->y + 1][min->x])) > 0 &&
                    cost != INT_MAX)
                {
                    p = malloc(sizeof(struct p));
                    p->y = min->y + 1;
                    p->x = min->x;
                    cost += heuristic(p->x, p->y, e->p.x, e->p.y);
                    root = insert(root, cost, p);
                }
            }

            if (costs[min->y + 1][min->x + 1] < 0)
            {
                if (min->x >= 2 && min->x < MAP_WIDTH - 2 && min->y >= 2 && min->y < MAP_HEIGHT - 2 &&
                    (cost = root->key + getCost(e->c, m->cells[min->y + 1][min->x + 1])) > 0 &&
                    cost != INT_MAX)
                {
                    p = malloc(sizeof(struct p));
                    p->y = min->y + 1;
                    p->x = min->x + 1;
                    cost += heuristic(p->x, p->y, e->p.x, e->p.y);
                    root = insert(root, cost, p);
                }
            }
        }

        root = deleteMin(root);
    }

    //print all costs
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            if (costs[y][x] == -1)
                printf("   ");
            else
                printf("%2d ", costs[y][x] % 100);
        }
        printf("\n");
    }

    //return direction
    int min = INT_MAX;
    int nx, ny;
    enum direction d = H;
    y = e->p.y;
    x = e->p.x;

    while (costs[y][x] > 0)
    {
        if (costs[y - 1][x - 1] < min && costs[y - 1][x - 1] != -1)
        {
            min = costs[y - 1][x - 1];
            ny = y - 1;
            nx = x - 1;
            d = NW;
        }
        if (costs[y - 1][x] < min && costs[y - 1][x] != -1)
        {
            min = costs[y - 1][x];
            ny = y - 1;
            nx = x;
            d = N;
        }
        if (costs[y - 1][x + 1] < min && costs[y - 1][x + 1] != -1)
        {
            min = costs[y - 1][x + 1];
            ny = y - 1;
            nx = x + 1;
            d = NE;
        }
        if (costs[y][x - 1] < min && costs[y][x - 1] != -1)
        {
            min = costs[y][x - 1];
            ny = y;
            nx = x - 1;
            d = W;
        }
        if (costs[y][x + 1] < min && costs[y][x + 1] != -1)
        {
            min = costs[y][x + 1];
            ny = y;
            nx = x + 1;
            d = E;
        }
        if (costs[y + 1][x - 1] < min && costs[y + 1][x - 1] != -1)
        {
            min = costs[y + 1][x - 1];
            ny = y + 1;
            nx = x - 1;
            d = SW;
        }
        if (costs[y + 1][x] < min && costs[y + 1][x] != -1)
        {
            min = costs[y + 1][x];
            ny = y + 1;
            nx = x;
            d = S;
        }
        if (costs[y + 1][x + 1] < min && costs[y + 1][x + 1] != -1)
        {
            min = costs[y + 1][x + 1];
            ny = y + 1;
            nx = x + 1;
            d = SE;
        }
//        m->cells[y][x] = '*';
        break;//was supposed to print path but this is better for later
        y = ny;
        x = nx;
    }
    return d;
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