#include <stdio.h>
#include "map/map.h"
#include "map/grid.h"
#include "entity/entity.h"
#include "data/heap.h"
#include "entity/costs.h"
#include <time.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char *argv[])
{
    int y = 0, x = 0;
    struct grid g;
    struct map *m;
    initGrid(&g, time(NULL));
    printf("main seed: %d\n", g.seed);
    m = getMap(&g, y, x);
//    display(m);

    m->eCount = 1;
    m->e = malloc(sizeof(struct entity *) * m->eCount);
    struct entity *pc = &m->e[0];
    pc->c = PC;
    do
    {
        pc->p.y = (rand() % (MAP_HEIGHT - 4)) + 2;
        pc->p.x = (rand() % (MAP_WIDTH - 4)) + 2;
    } while (m->cells[pc->p.y][pc->p.x] != ROAD);
    display(m);

    int costs[MAP_HEIGHT][MAP_WIDTH];
    for (y = 0; y < MAP_HEIGHT; y++)
        for (x = 0; x < MAP_WIDTH; x++)
            costs[y][x] = -1;

    int cost;
    struct p *p;
    p = malloc(sizeof(struct p));
    p->y = pc->p.y;
    p->x = pc->p.x;
    node *root = NULL;
    root = insert(root, 0, p);

    while (root != NULL)
    {
        struct p *min = (struct p *) (root->data);

        if (costs[min->y][min->x] == -1)
        {
            costs[min->y][min->x] = root->key;

            if (costs[min->y - 1][min->x - 1] < 0)
            {
                if (min->x >= 2 && min->x < MAP_WIDTH - 2 && min->y >= 2 && min->y < MAP_HEIGHT - 2 &&
                    (cost = root->key + getCost(HIKER, m->cells[min->y - 1][min->x - 1])) > 0 &&
                    cost != INT_MAX)
                {
                    p = malloc(sizeof(struct p));
                    p->y = min->y - 1;
                    p->x = min->x - 1;
                    root = insert(root, cost, p);
                }
            }

            if (costs[min->y - 1][min->x] < 0)
            {
                if (min->x >= 2 && min->x < MAP_WIDTH - 2 && min->y >= 2 && min->y < MAP_HEIGHT - 2 &&
                    (cost = root->key + getCost(HIKER, m->cells[min->y - 1][min->x])) > 0 &&
                    cost != INT_MAX)
                {
                    p = malloc(sizeof(struct p));
                    p->y = min->y - 1;
                    p->x = min->x;
                    root = insert(root, cost, p);
                }
            }

            if (costs[min->y - 1][min->x + 1] < 0)
            {
                if (min->x >= 2 && min->x < MAP_WIDTH - 2 && min->y >= 2 && min->y < MAP_HEIGHT - 2 &&
                    (cost = root->key + getCost(HIKER, m->cells[min->y - 1][min->x + 1])) > 0 &&
                    cost != INT_MAX)
                {
                    p = malloc(sizeof(struct p));
                    p->y = min->y - 1;
                    p->x = min->x + 1;
                    root = insert(root, cost, p);
                }
            }

            if (costs[min->y][min->x - 1] < 0)
            {
                if (min->x >= 2 && min->x < MAP_WIDTH - 2 && min->y >= 2 && min->y < MAP_HEIGHT - 2 &&
                    (cost = root->key + getCost(HIKER, m->cells[min->y][min->x - 1])) > 0 &&
                    cost != INT_MAX)
                {
                    p = malloc(sizeof(struct p));
                    p->y = min->y;
                    p->x = min->x - 1;
                    root = insert(root, cost, p);
                }
            }

            if (costs[min->y][min->x + 1] < 0)
            {
                if (min->x >= 2 && min->x < MAP_WIDTH - 2 && min->y >= 2 && min->y < MAP_HEIGHT - 2 &&
                    (cost = root->key + getCost(HIKER, m->cells[min->y][min->x + 1])) > 0 &&
                    cost != INT_MAX)
                {
                    p = malloc(sizeof(struct p));
                    p->y = min->y;
                    p->x = min->x + 1;
                    root = insert(root, cost, p);
                }
            }

            if (costs[min->y + 1][min->x - 1] < 0)
            {
                if (min->x >= 2 && min->x < MAP_WIDTH - 2 && min->y >= 2 && min->y < MAP_HEIGHT - 2 &&
                    (cost = root->key + getCost(HIKER, m->cells[min->y + 1][min->x - 1])) > 0 &&
                    cost != INT_MAX)
                {
                    p = malloc(sizeof(struct p));
                    p->y = min->y + 1;
                    p->x = min->x - 1;
                    root = insert(root, cost, p);
                }
            }

            if (costs[min->y + 1][min->x] < 0)
            {
                if (min->x >= 2 && min->x < MAP_WIDTH - 2 && min->y >= 2 && min->y < MAP_HEIGHT - 2 &&
                    (cost = root->key + getCost(HIKER, m->cells[min->y + 1][min->x])) > 0 &&
                    cost != INT_MAX)
                {
                    p = malloc(sizeof(struct p));
                    p->y = min->y + 1;
                    p->x = min->x;
                    root = insert(root, cost, p);
                }
            }

            if (costs[min->y + 1][min->x + 1] < 0)
            {
                if (min->x >= 2 && min->x < MAP_WIDTH - 2 && min->y >= 2 && min->y < MAP_HEIGHT - 2 &&
                    (cost = root->key + getCost(HIKER, m->cells[min->y + 1][min->x + 1])) > 0 &&
                    cost != INT_MAX)
                {
                    p = malloc(sizeof(struct p));
                    p->y = min->y + 1;
                    p->x = min->x + 1;
                    root = insert(root, cost, p);
                }
            }
        }

        root = delete_min(root);
    }

    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            printf("%2d ", costs[y][x] % 100);
        }
        printf("\n");
    }
}
