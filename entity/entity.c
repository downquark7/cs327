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

void addEntity(struct map *m, char entity)
{
    m->e = realloc(m->e, sizeof(struct entity) * ++m->eCount);
    m->e[m->eCount - 1].nextMove = H;
    m->e[m->eCount - 1].c = entity;
    m->e[m->eCount - 1].nextMoveCost = 0;
    m->e[m->eCount - 1].nextMoveTime = 0;
    setGetMove(m, entity);
    setMove(m, entity);
    place(m, entity);
}

void place(struct map *m, char entity)
{
    char saved[m->eCount];
    int i;
    for (i = 0; i < m->eCount; i++)
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
            } while (getCost(entity, m->cells[m->e[m->eCount - 1].p.y][m->e[m->eCount - 1].p.x]) > 1000 ||
                     m->cells[m->e[m->eCount - 1].p.y][m->e[m->eCount - 1].p.x] == 'P' ||
                     m->cells[m->e[m->eCount - 1].p.y][m->e[m->eCount - 1].p.x] == 'M');
            break;
    }
    for (i = 0; i < m->eCount; i++)
    {
        m->cells[m->e[i].p.y][m->e[i].p.x] = saved[i];
    }
}

void getMoveSwimmer(struct entity *e, struct map *m)
{
    //target PC
    getDirectionSwimmer(m->e[0].p, e, m);
}

void getMoveNPC(struct entity *e, struct map *m)
{
    //target PC
    getDirection(m->e[0].p, e, m);
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
    }
}

void doMove(struct entity *e)
{
    switch (e->nextMove)
    {
        case N:
            e->p.y = e->p.y - 1;
            return;
        case S:
            e->p.y = e->p.y + 1;
            return;
        case E:
            e->p.x = e->p.x + 1;
            return;
        case W:
            e->p.x = e->p.x - 1;
        case H:
            return;
        case NW:
            e->p.y = e->p.y - 1;
            e->p.x = e->p.x - 1;
            return;
        case NE:
            e->p.y = e->p.y - 1;
            return;
        case SW:
            e->p.y = e->p.y + 1;
            e->p.x = e->p.x - 1;
            return;
        case SE:
            e->p.y = e->p.y + 1;
            e->p.x = e->p.x + 1;
            return;
    }
}

void moveNPC(struct entity *e, struct map *m)
{
    char targetCell = getCell(e->nextMove, e->p, m);
    if (targetCell != ROAD || getCost(e->c, targetCell) > 100)
        e->getMove(e, m);

    doMove(e);
}

void movePC(struct entity *e, struct map *m)
{
    char targetCell = getCell(e->nextMove, e->p, m);
    if (getCost(e->c, targetCell) > 1000)
        e->nextMove = H;

    doMove(e);
}

void setGetMove(struct map *m, char entity)
{
    switch (entity)
    {
        case PC:
            return;
        case SWIMMER:
            m->e[m->eCount - 1].getMove = getMoveSwimmer;
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