//
// Created by downq on 2/20/2023.
//

#include "entity.h"
#include "costs.h"
#include <stdlib.h>
#include <stdio.h>

void clearMapEntities(struct map *m)
{
    m->e = NULL;
    m->eCount = 0;
}

int place(struct map *m, char entity);

void setGetMove(struct map *m, char entity);

void setMove(struct map *m, char entity);

char getCell(enum direction d, struct p p, struct map *m);

struct p getP(enum direction d, struct p p);

char getSwimmerCell(enum direction d, struct p p, struct map *m);

int addEntity(struct map *m, char entity)
{
    m->e = realloc(m->e, sizeof(struct entity) * ++m->eCount);
    m->e[m->eCount - 1].nextMove = H;
    m->e[m->eCount - 1].c = entity;
    m->e[m->eCount - 1].thisMoveCost = 10;
    m->e[m->eCount - 1].nextMoveCost = 10;
    m->e[m->eCount - 1].nextMoveTime = 0;
    setGetMove(m, entity);
    setMove(m, entity);
    if (place(m, entity))
    {
        m->e = realloc(m->e, sizeof(struct entity) * --m->eCount);
        return 1;
    }
    return 0;
}

int place(struct map *m, char entity)
{
    char saved[m->eCount];
    int i;
    int tries = 1000;
    for (i = 0; i < m->eCount - 1; i++)
    {
        saved[i] = m->cells[m->e[i].p.y][m->e[i].p.x];
        m->cells[m->e[i].p.y][m->e[i].p.x] = m->e[i].c;
    }
    switch (entity)
    {
        case PC:
            do
            {
                m->e[m->eCount - 1].p.y = (rand() % (MAP_HEIGHT - 4)) + 2;
                m->e[m->eCount - 1].p.x = (rand() % (MAP_WIDTH - 4)) + 2;
            } while (m->cells[m->e[m->eCount - 1].p.y][m->e[m->eCount - 1].p.x] != ROAD && tries--);
            break;
        default:
            do
            {
                m->e[m->eCount - 1].p.y = (rand() % (MAP_HEIGHT - 4)) + 2;
                m->e[m->eCount - 1].p.x = (rand() % (MAP_WIDTH - 4)) + 2;
            } while (tries-- &&
                     (getCost(entity, m->cells[m->e[m->eCount - 1].p.y][m->e[m->eCount - 1].p.x]) >=
                      getCost(entity, PLACEHOLDER) ||
                      m->cells[m->e[m->eCount - 1].p.y][m->e[m->eCount - 1].p.x] == 'C' ||
                      m->cells[m->e[m->eCount - 1].p.y][m->e[m->eCount - 1].p.x] == 'M'));
            break;
    }
    for (i = 0; i < m->eCount - 1; i++)
    {
        m->cells[m->e[i].p.y][m->e[i].p.x] = saved[i];
    }
    return tries <= 0;
}

void setMoveCost(struct entity *e, struct map *m)
{
    if (e->c == SWIMMER)
    {
        e->nextMoveCost = getCost(e->c, getSwimmerCell(e->nextMove, e->p, m));
        e->thisMoveCost = getCost(e->c, getSwimmerCell(H, e->p, m));
    } else
    {
        e->nextMoveCost = getCost(e->c, getCell(e->nextMove, e->p, m));
        e->thisMoveCost = getCost(e->c, getCell(H, e->p, m));
    }

    if (e->nextMoveCost >= getCost(e->c, PLACEHOLDER))
        e->nextMoveCost = m->e[0].thisMoveCost;

    if (e->thisMoveCost >= getCost(e->c, PLACEHOLDER))
        e->thisMoveCost = m->e[0].thisMoveCost;
}

void getMoveNPC(struct entity *e, struct map *m)
{
    //target PC
    getDirection(m->e[0].p, e, m);
}

void getMoveSentry(struct entity *e, struct map *m)
{
    //sentry does not move
}

void getMovePacer(struct entity *e, struct map *m)
{
    char targetCell = getCell(e->nextMove, e->p, m);
    struct p np = getP(e->nextMove, e->p);
    if (np.y == e->p.y && np.x == e->p.y)
        e->nextMove = H;
    else
        for (int i = 0; i < m->eCount; i++)
        {
            if (e != &(m->e[i]) && np.y == m->e[i].p.y && np.x == m->e[i].p.x)
                targetCell = PLACEHOLDER;
        }
    if (e->nextMove == H || getCost(e->c, targetCell) >= getCost(e->c, PLACEHOLDER))
    {
        if (e->nextMove == E)
            e->nextMove = W;
        else
            e->nextMove = E;
    }
    targetCell = getCell(e->nextMove, e->p, m);
    np = getP(e->nextMove, e->p);
    for (int i = 0; i < m->eCount; i++)
    {
        if (e != &(m->e[i]) && np.y == m->e[i].p.y && np.x == m->e[i].p.x)
            targetCell = PLACEHOLDER;
    }
    if (getCost(e->c, targetCell) >= getCost(e->c, PLACEHOLDER))
    {
        e->nextMove = H;
    }
    setMoveCost(e, m);
}

void getMoveWanderer(struct entity *e, struct map *m)
{
    char targetCell = getCell(e->nextMove, e->p, m);
    struct p np = getP(e->nextMove, e->p);
    if (np.y == e->p.y && np.x == e->p.y)
        e->nextMove = H;
    else
        for (int i = 0; i < m->eCount; i++)
        {
            if (e != &(m->e[i]) && np.y == m->e[i].p.y && np.x == m->e[i].p.x)
                targetCell = PLACEHOLDER;
        }
    if (e->nextMove == H || targetCell != getCell(H, e->p, m))
    {
        e->nextMove = rand() % 10;
        int start = e->nextMove;
        do
        {
            e->nextMove = (e->nextMove + 1) % 10;
            targetCell = getCell(e->nextMove, e->p, m);
            np = getP(e->nextMove, e->p);
            for (int i = 0; i < m->eCount; i++)
            {
                if (e != &(m->e[i]) && np.y == m->e[i].p.y && np.x == m->e[i].p.x)
                    targetCell = PLACEHOLDER;
            }
        } while (e->nextMove != start && (e->nextMove == H || targetCell != getCell(H, e->p, m)));
    }
    if (targetCell != getCell(H, e->p, m))
        e->nextMove = H;
    setMoveCost(e, m);
}

void getMoveSwimmer(struct entity *e, struct map *m)
{
    enum direction d = e->nextMove;
    getDirectionSwimmer(m->e[0].p, e, m);
    if (e->nextMove != H)
        return;
    e->nextMove = d;

    char targetCell = getSwimmerCell(e->nextMove, e->p, m);
    struct p np = getP(e->nextMove, e->p);
    if (np.y == e->p.y && np.x == e->p.y)
        e->nextMove = H;
    else
        for (int i = 0; i < m->eCount; i++)
        {
            if (e != &(m->e[i]) && np.y == m->e[i].p.y && np.x == m->e[i].p.x)
                targetCell = PLACEHOLDER;
        }
    if (e->nextMove == H || targetCell != WATER)
    {
        e->nextMove = rand() % 10;
        int start = e->nextMove;
        do
        {
            e->nextMove = (e->nextMove + 1) % 10;
            targetCell = getSwimmerCell(e->nextMove, e->p, m);
            np = getP(e->nextMove, e->p);
            for (int i = 0; i < m->eCount; i++)
            {
                if (e != &(m->e[i]) && np.y == m->e[i].p.y && np.x == m->e[i].p.x)
                    targetCell = PLACEHOLDER;
            }

        } while (e->nextMove != start && (e->nextMove == H || targetCell != WATER));
        if (targetCell != WATER)
            e->nextMove = H;
    }
    setMoveCost(e, m);
}

void getMoveExplorer(struct entity *e, struct map *m)
{
    char targetCell = getCell(e->nextMove, e->p, m);
    struct p np = getP(e->nextMove, e->p);
    if (np.y == e->p.y && np.x == e->p.y)
        e->nextMove = H;
    else
        for (int i = 0; i < m->eCount; i++)
        {
            if (e != &(m->e[i]) && np.y == m->e[i].p.y && np.x == m->e[i].p.x)
                targetCell = PLACEHOLDER;
        }
    if (e->nextMove == H || getCost(e->c, targetCell) >= getCost(e->c, PLACEHOLDER))
    {
        e->nextMove = rand() % 10;
        int start = e->nextMove;
        do
        {
            e->nextMove = (e->nextMove + 1) % 10;
            targetCell = getCell(e->nextMove, e->p, m);
            np = getP(e->nextMove, e->p);
            for (int i = 0; i < m->eCount; i++)
            {
                if (e != &(m->e[i]) && np.y == m->e[i].p.y && np.x == m->e[i].p.x)
                    targetCell = PLACEHOLDER;
            }

        } while (e->nextMove != start &&
                 (e->nextMove == H || getCost(e->c, targetCell) >= getCost(e->c, PLACEHOLDER)));
    }
    if (getCost(e->c, targetCell) >= getCost(e->c, PLACEHOLDER))
        e->nextMove = H;
    setMoveCost(e, m);
}

void getMovePC(struct entity *e, struct map *m)
{
    getMoveExplorer(e, m);
}

void doMove(struct entity *e)
{
    switch (e->nextMove)
    {
        case N:
            e->p.y = e->p.y - 1;
            break;
        case S:
            e->p.y = e->p.y + 1;
            break;
        case E:
            e->p.x = e->p.x + 1;
            break;
        case W:
            e->p.x = e->p.x - 1;
        case H:
            break;
        case NW:
            e->p.y = e->p.y - 1;
            e->p.x = e->p.x - 1;
            break;
        case NE:
            e->p.y = e->p.y - 1;
            e->p.x = e->p.x + 1;
            break;
        case SW:
            e->p.y = e->p.y + 1;
            e->p.x = e->p.x - 1;
            break;
        case SE:
            e->p.y = e->p.y + 1;
            e->p.x = e->p.x + 1;
            break;
    }
    if (e->p.y < 1) e->p.y = 1;
    if (e->p.x < 1) e->p.x = 1;
    if (e->p.y > MAP_HEIGHT - 2) e->p.y = MAP_HEIGHT - 2;
    if (e->p.x > MAP_WIDTH - 2) e->p.x = MAP_WIDTH - 2;
}

void moveNPC(struct entity *e, struct map *m)
{
    e->getMove(e, m);
    doMove(e);
}

void movePC(struct entity *e, struct map *m)
{
    char targetCell = getCell(e->nextMove, e->p, m);
    struct p np = getP(e->nextMove, e->p);
    for (int i = 0; i < m->eCount; i++)
    {
        if (e != &(m->e[i]) && np.y == m->e[i].p.y && np.x == m->e[i].p.x)
            targetCell = PLACEHOLDER;
    }
    if (getCost(e->c, targetCell) >= getCost(e->c, PLACEHOLDER))
        e->nextMove = H;

    doMove(e);
}

void setGetMove(struct map *m, char entity)
{
    switch (entity)
    {
        case PC:
            m->e[m->eCount - 1].getMove = getMovePC;
            return;
        case PACER:
            m->e[m->eCount - 1].getMove = getMovePacer;
            return;
        case WANDERER:
            m->e[m->eCount - 1].getMove = getMoveWanderer;
            return;
        case SWIMMER:
            m->e[m->eCount - 1].getMove = getMoveSwimmer;
            return;
        case SENTRY:
            m->e[m->eCount - 1].getMove = getMoveSentry;
            return;
        case EXPLORER:
            m->e[m->eCount - 1].getMove = getMoveExplorer;
            return;
        default:
            m->e[m->eCount - 1].getMove = getMoveNPC;
            return;
    }
}

void setMove(struct map *m, char entity)
{
    switch (entity)
    {
        case PC:
            m->e[m->eCount - 1].move = movePC;
            return;
        default:
            m->e[m->eCount - 1].move = moveNPC;
            return;
    }
}

struct p getP(enum direction d, struct p p)
{
    switch (d)
    {
        case N:
            p.y = p.y - 1;
            break;
        case S:
            p.y = p.y + 1;
            break;
        case E:
            p.x = p.x + 1;
            break;
        case W:
            p.x = p.x - 1;
        case H:
            break;
        case NW:
            p.y = p.y - 1;
            p.x = p.x - 1;
            break;
        case NE:
            p.y = p.y - 1;
            p.x = p.x + 1;
            break;
        case SW:
            p.y = p.y + 1;
            p.x = p.x - 1;
            break;
        case SE:
            p.y = p.y + 1;
            p.x = p.x + 1;
            break;
    }
    if (p.y < 1) p.y = 1;
    if (p.x < 1) p.x = 1;
    if (p.y > MAP_HEIGHT - 2) p.y = MAP_HEIGHT - 2;
    if (p.x > MAP_WIDTH - 2) p.x = MAP_WIDTH - 2;
    return p;
}


char getCell(enum direction d, struct p p, struct map *m)
{
    switch (d)
    {
        case N:
            return m->cells[p.y - 1][p.x];
        case S:
            return m->cells[p.y + 1][p.x];
        case E:
            return m->cells[p.y][p.x + 1];
        case W:
            return m->cells[p.y][p.x - 1];
        case H:
            return m->cells[p.y][p.x];
        case NW:
            return m->cells[p.y - 1][p.x - 1];
        case NE:
            return m->cells[p.y - 1][p.x + 1];
        case SW:
            return m->cells[p.y + 1][p.x - 1];
        case SE:
            return m->cells[p.y + 1][p.x + 1];
        default:
            return 0;
    }
}

char getSwimmerCell(enum direction d, struct p p, struct map *m)
{
    switch (d)
    {
        case N:
            return m->swimmerCells[p.y - 1][p.x];
        case S:
            return m->swimmerCells[p.y + 1][p.x];
        case E:
            return m->swimmerCells[p.y][p.x + 1];
        case W:
            return m->swimmerCells[p.y][p.x - 1];
        case H:
            return m->swimmerCells[p.y][p.x];
        case NW:
            return m->swimmerCells[p.y - 1][p.x - 1];
        case NE:
            return m->swimmerCells[p.y - 1][p.x + 1];
        case SW:
            return m->swimmerCells[p.y + 1][p.x - 1];
        case SE:
            return m->swimmerCells[p.y + 1][p.x + 1];
        default:
            return 0;
    }
}