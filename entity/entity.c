//
// Created by downq on 2/20/2023.
//

#include "entity.h"
#include "costs.h"
#include <stdlib.h>

void clearMapEntities(struct map *m)
{
    m->e = NULL;
    m->eCount = 0;
}

void place(struct map *m, char entity);

void setGetMove(struct map *m, char entity);

void setMove(struct map *m, char entity);

char getCell(enum direction d, struct p p, struct map *m);

char getSwimmerCell(enum direction d, struct p p, struct map *m);

void addEntity(struct map *m, char entity)
{
    m->e = realloc(m->e, sizeof(struct entity) * ++m->eCount);
    m->e[m->eCount - 1].nextMove = H;
    m->e[m->eCount - 1].c = entity;
    m->e[m->eCount - 1].thisMoveCost = 10;
    m->e[m->eCount - 1].nextMoveCost = 10;
    m->e[m->eCount - 1].nextMoveTime = 0;
    setGetMove(m, entity);
    setMove(m, entity);
    place(m, entity);
}

void place(struct map *m, char entity)
{
    char saved[m->eCount];
    int i;
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
            } while (m->cells[m->e[m->eCount - 1].p.y][m->e[m->eCount - 1].p.x] != ROAD);
            break;
        default:
            do
            {
                m->e[m->eCount - 1].p.y = (rand() % (MAP_HEIGHT - 4)) + 2;
                m->e[m->eCount - 1].p.x = (rand() % (MAP_WIDTH - 4)) + 2;
            } while (getCost(entity, m->cells[m->e[m->eCount - 1].p.y][m->e[m->eCount - 1].p.x]) >=
                     getCost(entity, PLACEHOLDER) ||
                     m->cells[m->e[m->eCount - 1].p.y][m->e[m->eCount - 1].p.x] == 'C' ||
                     m->cells[m->e[m->eCount - 1].p.y][m->e[m->eCount - 1].p.x] == 'M');
            break;
    }
    for (i = 0; i < m->eCount - 1; i++)
    {
        m->cells[m->e[i].p.y][m->e[i].p.x] = saved[i];
    }
}

void setMoveCost(struct entity *e, struct map *m)
{
    if (e->c == SWIMMER)
        e->nextMoveCost = e->thisMoveCost =
                e->nextMove == H ? m->e[0].thisMoveCost : getCost(e->c, getSwimmerCell(e->nextMove, e->p, m));
    else
        e->nextMoveCost = e->thisMoveCost =
                e->nextMove == H ? m->e[0].thisMoveCost : getCost(e->c, getCell(e->nextMove, e->p, m));
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
    for (int i = 0; i < m->eCount; i++)
    {
        if (e != &(m->e[i]) && e->p.y == m->e[i].p.y && e->p.x == m->e[i].p.x)
            targetCell = PLACEHOLDER;
    }
    if (getCost(e->c, targetCell) >= getCost(e->c, PLACEHOLDER))
    {
        if (e->nextMove == E)
            e->nextMove = W;
        else
            e->nextMove = E;
    }
    targetCell = getCell(e->nextMove, e->p, m);
    for (int i = 0; i < m->eCount; i++)
    {
        if (e != &(m->e[i]) && e->p.y == m->e[i].p.y && e->p.x == m->e[i].p.x)
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
    int start = -1;
    char targetCell = getCell(e->nextMove, e->p, m);
    if (e->nextMove == H || targetCell != getCell(H, e->p, m))
    {
        e->nextMove = rand() % 10;
        start = e->nextMove;
        do
        {
            e->nextMove = (e->nextMove + 1) % 10;
            targetCell = getCell(e->nextMove, e->p, m);
            for (int i = 0; i < m->eCount; i++)
            {
                if (e != &(m->e[i]) && e->p.y == m->e[i].p.y && e->p.x == m->e[i].p.x)
                    targetCell = PLACEHOLDER;
            }

        } while (e->nextMove != start && (e->nextMove == H || targetCell != getCell(H, e->p, m)));
        if (e->nextMove == start && targetCell != getCell(H, e->p, m))
            e->nextMove = H;
    }
    setMoveCost(e, m);
}

void getMoveSwimmer(struct entity *e, struct map *m)
{
    enum direction d = e->nextMove;
    getDirectionSwimmer(m->e[0].p, e, m);
    if (e->nextMove != H)
        return;
    e->nextMove = d;

    int start = -1;
    char targetCell = getSwimmerCell(e->nextMove, e->p, m);
    if (e->nextMove == H || targetCell != getSwimmerCell(H, e->p, m))
    {
        e->nextMove = rand() % 10;
        start = e->nextMove;
        do
        {
            e->nextMove = (e->nextMove + 1) % 10;
            targetCell = getSwimmerCell(e->nextMove, e->p, m);
            for (int i = 0; i < m->eCount; i++)
            {
                if (e != &(m->e[i]) && e->p.y == m->e[i].p.y && e->p.x == m->e[i].p.x)
                    targetCell = PLACEHOLDER;
            }

        } while (e->nextMove != start && (e->nextMove == H || targetCell != getSwimmerCell(H, e->p, m)));
        if (e->nextMove == start && targetCell != getSwimmerCell(H, e->p, m))
            e->nextMove = H;
    }
    setMoveCost(e, m);
}

void getMoveExplorer(struct entity *e, struct map *m)
{
    int start = -1;
    char targetCell = getCell(e->nextMove, e->p, m);
    if (e->nextMove == H || getCost(e->c, targetCell) >= getCost(e->c, PLACEHOLDER))
    {
        e->nextMove = rand() % 10;
        start = e->nextMove;
        do
        {
            e->nextMove = (e->nextMove + 1) % 10;
            targetCell = getCell(e->nextMove, e->p, m);
            for (int i = 0; i < m->eCount; i++)
            {
                if (e != &(m->e[i]) && e->p.y == m->e[i].p.y && e->p.x == m->e[i].p.x)
                    targetCell = PLACEHOLDER;
            }

        } while (e->nextMove != start && (e->nextMove == H || getCost(e->c, targetCell) >= getCost(e->c, PLACEHOLDER)));
    }
    if (e->nextMove == start && getCost(e->c, targetCell) >= getCost(e->c, PLACEHOLDER))
        e->nextMove = H;
    setMoveCost(e, m);
}

void getMovePC(struct entity *e, struct map *m)
{
    getMoveSentry(e, m);
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