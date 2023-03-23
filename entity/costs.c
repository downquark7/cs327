//
// Created by downq on 2/20/2023.
//

#include "entity.h"
#include "costs.h"
#include <stdlib.h>
#include <limits.h>
#include <math.h>
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
    return sqrt(106 * (dy * dy) + 15 * (dx * dx));
}

int heuristic(int x1, int y1, int x2, int y2)
{
    return visuallyCorrectedDistance(x1, y1, x2, y2);
}

void getDirection(struct p target, struct entity *e, struct map *m)
{
    char saved[m->eCount];
    for (int i = 0; i < m->eCount; i++)
    {
        saved[i] = m->cells[m->e[i].p.y][m->e[i].p.x];
        m->cells[m->e[i].p.y][m->e[i].p.x] = PLACEHOLDER;
    }

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
        if (costs[min->y][min->x] == -1 && min->x >= 1 && min->x < MAP_WIDTH - 1 && min->y >= 1 &&
            min->y < MAP_HEIGHT - 1)
        {
            costs[min->y][min->x] = root->key;

            if ((min->x == e->p.x && min->y == e->p.y))
            {
                break;
            }

            if (min->x >= 1 && min->x < MAP_WIDTH - 1 && min->y >= 1 && min->y < MAP_HEIGHT - 1 &&
                costs[min->y - 1][min->x - 1] == -1 &&
                (cost = root->key + getCost(e->c, m->cells[min->y - 1][min->x - 1])) > 0 &&
                cost != INT_MAX)
            {
                p = malloc(sizeof(struct p));
                p->y = min->y - 1;
                p->x = min->x - 1;
                cost += heuristic(p->x, p->y, e->p.x, e->p.y);
                root = insert(root, cost, p);
            }

            if (min->x >= 1 && min->x < MAP_WIDTH - 1 && min->y >= 1 && min->y < MAP_HEIGHT - 1 &&
                costs[min->y - 1][min->x] == -1 &&
                (cost = root->key + getCost(e->c, m->cells[min->y - 1][min->x])) > 0 &&
                cost != INT_MAX)
            {
                p = malloc(sizeof(struct p));
                p->y = min->y - 1;
                p->x = min->x;
                cost += heuristic(p->x, p->y, e->p.x, e->p.y);
                root = insert(root, cost, p);
            }

            if (min->x >= 1 && min->x < MAP_WIDTH - 1 && min->y >= 1 && min->y < MAP_HEIGHT - 1 &&
                costs[min->y - 1][min->x + 1] == -1 &&
                (cost = root->key + getCost(e->c, m->cells[min->y - 1][min->x + 1])) > 0 &&
                cost != INT_MAX)
            {
                p = malloc(sizeof(struct p));
                p->y = min->y - 1;
                p->x = min->x + 1;
                cost += heuristic(p->x, p->y, e->p.x, e->p.y);
                root = insert(root, cost, p);
            }

            if (min->x >= 1 && min->x < MAP_WIDTH - 1 && min->y >= 1 && min->y < MAP_HEIGHT - 1 &&
                costs[min->y][min->x - 1] == -1 &&
                (cost = root->key + getCost(e->c, m->cells[min->y][min->x - 1])) > 0 &&
                cost != INT_MAX)
            {
                p = malloc(sizeof(struct p));
                p->y = min->y;
                p->x = min->x - 1;
                cost += heuristic(p->x, p->y, e->p.x, e->p.y);
                root = insert(root, cost, p);
            }

            if (min->x >= 1 && min->x < MAP_WIDTH - 1 && min->y >= 1 && min->y < MAP_HEIGHT - 1 &&
                costs[min->y][min->x + 1] == -1 &&
                (cost = root->key + getCost(e->c, m->cells[min->y][min->x + 1])) > 0 &&
                cost != INT_MAX)
            {
                p = malloc(sizeof(struct p));
                p->y = min->y;
                p->x = min->x + 1;
                cost += heuristic(p->x, p->y, e->p.x, e->p.y);
                root = insert(root, cost, p);
            }

            if (min->x >= 1 && min->x < MAP_WIDTH - 1 && min->y >= 1 && min->y < MAP_HEIGHT - 1 &&
                costs[min->y + 1][min->x - 1] == -1 &&
                (cost = root->key + getCost(e->c, m->cells[min->y + 1][min->x - 1])) > 0 &&
                cost != INT_MAX)
            {
                p = malloc(sizeof(struct p));
                p->y = min->y + 1;
                p->x = min->x - 1;
                cost += heuristic(p->x, p->y, e->p.x, e->p.y);
                root = insert(root, cost, p);
            }

            if (min->x >= 1 && min->x < MAP_WIDTH - 1 && min->y >= 1 && min->y < MAP_HEIGHT - 1 &&
                costs[min->y + 1][min->x] == -1 &&
                (cost = root->key + getCost(e->c, m->cells[min->y + 1][min->x])) > 0 &&
                cost != INT_MAX)
            {
                p = malloc(sizeof(struct p));
                p->y = min->y + 1;
                p->x = min->x;
                cost += heuristic(p->x, p->y, e->p.x, e->p.y);
                root = insert(root, cost, p);
            }

            if (min->x >= 1 && min->x < MAP_WIDTH - 1 && min->y >= 1 && min->y < MAP_HEIGHT - 1 &&
                costs[min->y + 1][min->x + 1] == -1 &&
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
        free(root->data);
        root = deleteMin(root);
    }
    deleteAllData(root);

    //print all costs
//    printf("\n     ");
//    for (x = 0; x < MAP_WIDTH; x++)
//        printf("%4d ", x);
//    printf("\n");
//    for (y = 0; y < MAP_HEIGHT; y++)
//    {
//        printf("%4d ", y);
//        for (x = 0; x < MAP_WIDTH; x++)
//        {
//            if (costs[y][x] == -1)
//                printf("   - ");
//            else
//                printf("%4d ", costs[y][x]);
//        }
//        printf("%4d ", y);
//        printf("\n");
//    }
//    printf("     ");
//    for (x = 0; x < MAP_WIDTH; x++)
//        printf("%4d ", x);
//    printf("\n");

    for (int i = 0; i < m->eCount; i++)
    {
        m->cells[m->e[i].p.y][m->e[i].p.x] = saved[i];
    }

    if (getCost(e->c, m->cells[target.y][target.x]) >= getCost(e->c, PLACEHOLDER))
        costs[target.y][target.x] = INT_MAX;

    for (int i = 0; i < m->eCount; i++)
        costs[m->e[i].p.y][m->e[i].p.x] = INT_MAX;

    //return direction
    int min = INT_MAX - 10;
    int nx, ny;
    enum direction d = H;
    y = e->p.y;
    ny = y;
    x = e->p.x;
    nx = x;
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
    e->nextMove = d;
    e->nextMoveCost = getCost(e->c, m->cells[ny][nx]);
}

void getDirectionSwimmer(struct p target, struct entity *e, struct map *m)
{
    char cellAtE = m->swimmerCells[e->p.y][e->p.x];
    char saved[m->eCount];
    for (int i = 0; i < m->eCount; i++)
    {
        saved[i] = m->swimmerCells[m->e[i].p.y][m->e[i].p.x];
        m->swimmerCells[m->e[i].p.y][m->e[i].p.x] = PLACEHOLDER;
    }

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
        if (costs[min->y][min->x] == -1 && min->x >= 1 && min->x < MAP_WIDTH - 1 && min->y >= 1 &&
            min->y < MAP_HEIGHT - 1)
        {
            costs[min->y][min->x] = root->key;

            if ((min->x == e->p.x && min->y == e->p.y))
            {
                break;
            }

            if (min->x >= 1 && min->x < MAP_WIDTH - 1 && min->y >= 1 && min->y < MAP_HEIGHT - 1 &&
                costs[min->y - 1][min->x - 1] < 0 &&
                (cost = root->key + getCost(e->c, m->swimmerCells[min->y - 1][min->x - 1])) > 0 &&
                cost != INT_MAX)
            {
                p = malloc(sizeof(struct p));
                p->y = min->y - 1;
                p->x = min->x - 1;
                cost += heuristic(p->x, p->y, e->p.x, e->p.y);
                root = insert(root, cost, p);
            }

            if (min->x >= 1 && min->x < MAP_WIDTH - 1 && min->y >= 1 && min->y < MAP_HEIGHT - 1 &&
                costs[min->y - 1][min->x] < 0 &&
                (cost = root->key + getCost(e->c, m->swimmerCells[min->y - 1][min->x])) > 0 &&
                cost != INT_MAX)
            {
                p = malloc(sizeof(struct p));
                p->y = min->y - 1;
                p->x = min->x;
                cost += heuristic(p->x, p->y, e->p.x, e->p.y);
                root = insert(root, cost, p);
            }

            if (min->x >= 1 && min->x < MAP_WIDTH - 1 && min->y >= 1 && min->y < MAP_HEIGHT - 1 &&
                costs[min->y - 1][min->x + 1] < 0 &&
                (cost = root->key + getCost(e->c, m->swimmerCells[min->y - 1][min->x + 1])) > 0 &&
                cost != INT_MAX)
            {
                p = malloc(sizeof(struct p));
                p->y = min->y - 1;
                p->x = min->x + 1;
                cost += heuristic(p->x, p->y, e->p.x, e->p.y);
                root = insert(root, cost, p);
            }

            if (min->x >= 1 && min->x < MAP_WIDTH - 1 && min->y >= 1 && min->y < MAP_HEIGHT - 1 &&
                costs[min->y][min->x - 1] < 0 &&
                (cost = root->key + getCost(e->c, m->swimmerCells[min->y][min->x - 1])) > 0 &&
                cost != INT_MAX)
            {
                p = malloc(sizeof(struct p));
                p->y = min->y;
                p->x = min->x - 1;
                cost += heuristic(p->x, p->y, e->p.x, e->p.y);
                root = insert(root, cost, p);
            }

            if (min->x >= 1 && min->x < MAP_WIDTH - 1 && min->y >= 1 && min->y < MAP_HEIGHT - 1 &&
                costs[min->y][min->x + 1] < 0 &&
                (cost = root->key + getCost(e->c, m->swimmerCells[min->y][min->x + 1])) > 0 &&
                cost != INT_MAX)
            {
                p = malloc(sizeof(struct p));
                p->y = min->y;
                p->x = min->x + 1;
                cost += heuristic(p->x, p->y, e->p.x, e->p.y);
                root = insert(root, cost, p);
            }

            if (min->x >= 1 && min->x < MAP_WIDTH - 1 && min->y >= 1 && min->y < MAP_HEIGHT - 1 &&
                costs[min->y + 1][min->x - 1] < 0 &&
                (cost = root->key + getCost(e->c, m->swimmerCells[min->y + 1][min->x - 1])) > 0 &&
                cost != INT_MAX)
            {
                p = malloc(sizeof(struct p));
                p->y = min->y + 1;
                p->x = min->x - 1;
                cost += heuristic(p->x, p->y, e->p.x, e->p.y);
                root = insert(root, cost, p);
            }

            if (min->x >= 1 && min->x < MAP_WIDTH - 1 && min->y >= 1 && min->y < MAP_HEIGHT - 1 &&
                costs[min->y + 1][min->x] < 0 &&
                (cost = root->key + getCost(e->c, m->swimmerCells[min->y + 1][min->x])) > 0 &&
                cost != INT_MAX)
            {
                p = malloc(sizeof(struct p));
                p->y = min->y + 1;
                p->x = min->x;
                cost += heuristic(p->x, p->y, e->p.x, e->p.y);
                root = insert(root, cost, p);
            }

            if (min->x >= 1 && min->x < MAP_WIDTH - 1 && min->y >= 1 && min->y < MAP_HEIGHT - 1 &&
                costs[min->y + 1][min->x + 1] < 0 &&
                (cost = root->key + getCost(e->c, m->swimmerCells[min->y + 1][min->x + 1])) > 0 &&
                cost != INT_MAX)
            {
                p = malloc(sizeof(struct p));
                p->y = min->y + 1;
                p->x = min->x + 1;
                cost += heuristic(p->x, p->y, e->p.x, e->p.y);
                root = insert(root, cost, p);
            }
        }
        free(root->data);
        root->data = NULL;
        root = deleteMin(root);
    }
    deleteAllData(root);

    if (getCost(e->c, m->swimmerCells[target.y][target.x]) == INT_MAX)
        costs[target.y][target.x] = INT_MAX;
    for (int i = 0; i < m->eCount; i++)
    {
        costs[m->e[i].p.y][m->e[i].p.x] = INT_MAX;
    }

    //return direction
    int min = INT_MAX - 10;
    int nx, ny;
    enum direction d = H;
    y = e->p.y;
    ny = y;
    x = e->p.x;
    nx = x;
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
    e->nextMove = d;
    char cellAtNewE = m->swimmerCells[ny][nx];
    m->swimmerCells[ny][nx] = PLACEHOLDER;
    m->swimmerCells[e->p.y][e->p.x] = cellAtE;
    y = ny;
    x = nx;
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
    m->swimmerCells[y][x] = cellAtNewE;
    e->nextMoveCost = getCost(e->c, m->swimmerCells[ny][nx]);
    for (int i = 0; i < m->eCount; i++)
    {
        m->swimmerCells[m->e[i].p.y][m->e[i].p.x] = saved[i];
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
        case PLACEHOLDER:
            return 100;
        default:
            return INT_MAX;
    }
}