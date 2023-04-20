//
// Created by downq on 2/20/2023.
//

#include <ncurses.h>
#include "entity.h"
#include "battle.h"
#include "costs.h"
#include "building.h"
#include "trainerlist.h"
#include <random>

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

void addEntities(int num, struct map *m)
{
    srand(m->seed);
    addEntity(m, PC);
    if (num > 0)
        addEntity(m, RIVAL);
    if (num > 1)
        addEntity(m, HIKER);

    for (int i = 2; i < num; i++)
        switch (rand() % 7)
        {
            case 0:
                addEntity(m, RIVAL);
                break;
            case 1:
                addEntity(m, HIKER);
                break;
            case 2:
                addEntity(m, PACER);
                break;
            case 3:
                addEntity(m, WANDERER);
                break;
            case 4:
                addEntity(m, SENTRY);
                break;
            case 5:
                addEntity(m, EXPLORER);
                break;
            case 6:
                addEntity(m, SWIMMER);
                break;
        }
}

void addEntities(int num, struct map *m, struct entity *e)
{
    srand(m->seed);
    transferEntity(m, e);
    if (num > 0)
        addEntity(m, RIVAL);
    if (num > 1)
        addEntity(m, HIKER);

    for (int i = 2; i < num; i++)
        switch (rand() % 7)
        {
            case 0:
                addEntity(m, RIVAL);
                break;
            case 1:
                addEntity(m, HIKER);
                break;
            case 2:
                addEntity(m, PACER);
                break;
            case 3:
                addEntity(m, WANDERER);
                break;
            case 4:
                addEntity(m, SENTRY);
                break;
            case 5:
                addEntity(m, EXPLORER);
                break;
            case 6:
                addEntity(m, SWIMMER);
                break;
        }
}

int transferEntity(struct map *m, struct entity *e)
{
    m->e = static_cast<struct entity *>(realloc(m->e, sizeof(struct entity) * ++m->eCount));
    m->e[m->eCount - 1].nextMove = H;
    m->e[m->eCount - 1].nextMoveCost = 10;
    m->e[m->eCount - 1].emove = e->emove;
    m->e[m->eCount - 1].c = e->c;
    m->e[m->eCount - 1].p.x = e->p.x;
    m->e[m->eCount - 1].p.y = e->p.y;
    for (int i = 0; i < 6; i++)
        m->e[0].party[i] = (struct pokemon *) e->party[i];
    return 0;
}

int copyPC(struct map *m, struct entity *e)
{
    m->e[0].nextMove = H;
    m->e[0].nextMoveCost = 10;
    m->e[0].emove = e->emove;
    m->e[0].c = e->c;
    m->e[0].p.x = e->p.x;
    m->e[0].p.y = e->p.y;
    for (int i = 0; i < 6; i++)
        m->e[0].party[i] = (struct pokemon *) e->party[i];
    return 0;
}

int addEntity(struct map *m, char entity)
{
    m->e = static_cast<struct entity *>(realloc(m->e, sizeof(struct entity) * ++m->eCount));
    m->e[m->eCount - 1].nextMove = H;
    m->e[m->eCount - 1].c = entity;
    m->e[m->eCount - 1].nextMoveCost = 10;
    m->e[m->eCount - 1].nextMoveTime = 0;
    setGetMove(m, entity);
    setMove(m, entity);
    if (place(m, entity))
    {
        m->e = static_cast<struct entity *>(realloc(m->e, sizeof(struct entity) * --m->eCount));
        return 1;
    }
    for (int i = 0; i < 6; i++)
        m->e[m->eCount - 1].party[i] = (struct pokemon *) nullptr;
    if (m->eCount > 1)
    {
        int dist = abs(m->p.y) + abs(m->p.x);
        int level = dist < 3 ? 1 : dist > 200 ? (rand() % (100 - ((dist - 200) / 2) + 1)) + ((dist - 200) / 2) :
                                   (rand() % (dist / 2)) + 1;
        int i = 0;
        while (i < 6 && (i == 0 || rand() % 100 < 60))
        {
            m->e[m->eCount - 1].party[i] = new pokemon(level);
            i++;
        }
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
                      m->cells[m->e[m->eCount - 1].p.y][m->e[m->eCount - 1].p.x] == 'M' ||
                      m->cells[m->e[m->eCount - 1].p.y][m->e[m->eCount - 1].p.x] == ROAD));
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
    } else
    {
        e->nextMoveCost = getCost(e->c, getCell(e->nextMove, e->p, m));
    }

    if (e->nextMoveCost >= getCost(e->c, PLACEHOLDER))
        e->nextMoveCost = 10;
}

int checkBounds(struct p p)
{
    if (p.y < 1) return 1;
    if (p.x < 1) return 1;
    if (p.y > MAP_HEIGHT - 2) return 1;
    if (p.x > MAP_WIDTH - 2) return 1;
    return 0;
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
    if (checkBounds(np))
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
    if (getCost(e->c, targetCell) >= getCost(e->c, PLACEHOLDER) || checkBounds(np))
    {
        e->nextMove = H;
    }
    setMoveCost(e, m);
}

void getMoveWanderer(struct entity *e, struct map *m)
{
    char targetCell = getCell(e->nextMove, e->p, m);
    struct p np = getP(e->nextMove, e->p);
    if (checkBounds(np))
        e->nextMove = H;
    else
        for (int i = 0; i < m->eCount; i++)
        {
            if (e != &(m->e[i]) && np.y == m->e[i].p.y && np.x == m->e[i].p.x)
                targetCell = PLACEHOLDER;
        }
    if (e->nextMove == H || targetCell != getCell(H, e->p, m))
    {
        e->nextMove = static_cast<direction>(rand() % H);
        int start = e->nextMove;
        do
        {
            e->nextMove = static_cast<direction>((e->nextMove + 1) % H);
            targetCell = getCell(e->nextMove, e->p, m);
            np = getP(e->nextMove, e->p);
            for (int i = 0; i < m->eCount; i++)
            {
                if (e != &(m->e[i]) && np.y == m->e[i].p.y && np.x == m->e[i].p.x)
                    targetCell = PLACEHOLDER;
            }
        } while (e->nextMove != start && (e->nextMove == H || targetCell != getCell(H, e->p, m)));
    }
    if (targetCell != getCell(H, e->p, m) || checkBounds(np))
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
    if (checkBounds(np))
        e->nextMove = H;
    else
        for (int i = 0; i < m->eCount; i++)
        {
            if (e != &(m->e[i]) && np.y == m->e[i].p.y && np.x == m->e[i].p.x)
                targetCell = PLACEHOLDER;
        }
    if (e->nextMove == H || targetCell != WATER)
    {
        e->nextMove = static_cast<direction>(rand() % H);
        int start = e->nextMove;
        do
        {
            e->nextMove = static_cast<direction>((e->nextMove + 1) % H);
            targetCell = getSwimmerCell(e->nextMove, e->p, m);
            np = getP(e->nextMove, e->p);
            for (int i = 0; i < m->eCount; i++)
            {
                if (e != &(m->e[i]) && np.y == m->e[i].p.y && np.x == m->e[i].p.x)
                    targetCell = PLACEHOLDER;
            }

        } while (e->nextMove != start && (e->nextMove == H || targetCell != WATER));
        if (targetCell != WATER || checkBounds(np))
            e->nextMove = H;
    }
    setMoveCost(e, m);
}

void getMoveExplorer(struct entity *e, struct map *m)
{
    char targetCell = getCell(e->nextMove, e->p, m);
    struct p np = getP(e->nextMove, e->p);
    if (checkBounds(np))
        e->nextMove = H;
    else
        for (int i = 0; i < m->eCount; i++)
        {
            if (e != &(m->e[i]) && np.y == m->e[i].p.y && np.x == m->e[i].p.x)
                targetCell = PLACEHOLDER;
        }
    if (e->nextMove == H || getCost(e->c, targetCell) >= getCost(e->c, PLACEHOLDER))
    {
        e->nextMove = static_cast<direction>(rand() % H);
        int start = e->nextMove;
        do
        {
            e->nextMove = static_cast<direction>((e->nextMove + 1) % H);
            targetCell = getCell(e->nextMove, e->p, m);
            np = getP(e->nextMove, e->p);
            for (int i = 0; i < m->eCount; i++)
            {
                if (e != &(m->e[i]) && np.y == m->e[i].p.y && np.x == m->e[i].p.x)
                    targetCell = PLACEHOLDER;
            }

        } while (e->nextMove != start &&
                 (e->nextMove == H || getCost(e->c, targetCell) >= getCost(e->c, PLACEHOLDER) ||
                  checkBounds(np)));
    }
    if (getCost(e->c, targetCell) >= getCost(e->c, PLACEHOLDER) || checkBounds(np))
        e->nextMove = H;
    setMoveCost(e, m);
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
        default:
            break;
    }
    if (e->c != PC)
    {
        if (e->p.y < 1)
        {
            mvprintw(4, 0, "\n%c[%d][%d]\n", e->c, e->p.y, e->p.x);
            refresh();
            abort();
        }
        if (e->p.x < 1)
        {
            mvprintw(4, 0, "\n%c[%d][%d]\n", e->c, e->p.y, e->p.x);
            refresh();
            abort();
        }
        if (e->p.y > MAP_HEIGHT - 2)
        {
            mvprintw(4, 0, "\n%c[%d][%d]\n", e->c, e->p.y, e->p.x);
            refresh();
            abort();
        }
        if (e->p.x > MAP_WIDTH - 2)
        {
            mvprintw(4, 0, "\n%c[%d][%d]\n", e->c, e->p.y, e->p.x);
            refresh();
            abort();
        }
    }
}

extern int testMode;

void moveNPC(struct entity *e, struct map *m)
{
    int didBattle = 0;
    if ((e->p.y - m->e[0].p.y) * (e->p.y - m->e[0].p.y) + (e->p.x - m->e[0].p.x) * (e->p.x - m->e[0].p.x) < 3)
    {
        enterBattle(e, m);
        clear();
        display(m);
        didBattle = 1;
    }
    if (!didBattle)
    {
        mvaddch(e->p.y + 1, e->p.x, m->cells[e->p.y][e->p.x]);
        e->getMove(e, m);
        doMove(e);
        mvaddch(e->p.y + 1, e->p.x, e->c);
        if ((e->p.y - m->e[0].p.y) * (e->p.y - m->e[0].p.y) + (e->p.x - m->e[0].p.x) * (e->p.x - m->e[0].p.x) < 3)
        {
            enterBattle(e, m);
            clear();
            display(m);
        }
    }
}

void defeated(struct entity *e, struct map *m)
{
    if (getCell(H, e->p, m) == ROAD || getCell(H, e->p, m) == 'C' || getCell(H, e->p, m) == 'M')
    {
        mvaddch(e->p.y + 1, e->p.x, m->cells[e->p.y][e->p.x]);
        if (e->c != SWIMMER)
            getMoveExplorer(e, m);
        else
        {
            char targetCell = getSwimmerCell(e->nextMove, e->p, m);
            struct p np = getP(e->nextMove, e->p);
            if (checkBounds(np))
                e->nextMove = H;
            else
                for (int i = 0; i < m->eCount; i++)
                {
                    if (e != &(m->e[i]) && np.y == m->e[i].p.y && np.x == m->e[i].p.x)
                        targetCell = PLACEHOLDER;
                }
            if (e->nextMove == H || targetCell != WATER)
            {
                e->nextMove = static_cast<direction>(rand() % H);
                int start = e->nextMove;
                do
                {
                    e->nextMove = static_cast<direction>((e->nextMove + 1) % H);
                    targetCell = getSwimmerCell(e->nextMove, e->p, m);
                    np = getP(e->nextMove, e->p);
                    for (int i = 0; i < m->eCount; i++)
                    {
                        if (e != &(m->e[i]) && np.y == m->e[i].p.y && np.x == m->e[i].p.x)
                            targetCell = PLACEHOLDER;
                    }

                } while (e->nextMove != start && (e->nextMove == H || targetCell != WATER));
                if (targetCell != WATER || checkBounds(np))
                    e->nextMove = H;
            }
            setMoveCost(e, m);
        }
        doMove(e);
        mvaddch(e->p.y + 1, e->p.x, e->c);
    } else e->nextMoveCost = 1000;
}

char getRandomInput()
{
    refresh();
    char characters[] = {'y', '8', 'k', '9', 'u', '6', 'l', '3', 'n', '2', 'j', '1', 'b', '4', 'h', '5', ' ', '.',
                         '>', 't'};
    return characters[rand() % sizeof(characters)];
}

void movePC(struct entity *e, struct map *m)
{
    refresh();
    if (getCell(H, e->p, m) == TALL_GRASS && rand() % 10 == 0)
    {
        struct entity encounter;
        encounter.c = WILD;
        encounter.party[1] = nullptr;
        int dist = abs(m->p.y) + abs(m->p.x);
        int level = dist < 3 ? 1 : dist > 200 ? (rand() % (100 - ((dist - 200) / 2) + 1)) + ((dist - 200) / 2) :
                                   (rand() % (dist / 2)) + 1;
        encounter.party[0] = new pokemon(level);
        enterBattle(&encounter, m);
        clear();
        display(m);
    }
    e->nextMove = H;
    while (e->nextMove == H)
    {
        switch (testMode ? getRandomInput() : getch())
        {
            case '7':
            case 'y':
                e->nextMove = NW;
                break;
            case '8':
            case 'k':
                e->nextMove = N;
                break;
            case '9':
            case 'u':
                e->nextMove = NE;
                break;
            case '6':
            case 'l':
                e->nextMove = E;
                break;
            case '3':
            case 'n':
                e->nextMove = SE;
                break;
            case '2':
            case 'j':
                e->nextMove = S;
                break;
            case '1':
            case 'b':
                e->nextMove = SW;
                break;
            case '4':
            case 'h':
                e->nextMove = W;
                break;
            case '5':
            case ' ':
            case '.':
                e->nextMove = REST;
                break;
            case 'q':
                e->nextMove = QUIT;
                endwin();
                exit(0);
            case '>':
                if (!enterBuilding(getCell(H, e->p, m)))
                {
                    display(m);
                }
                break;
            case 't':
                enterList(m);
                clear();
                display(m);
                break;
            case 'f':
                e->nextMove = FLY;
                e->nextMoveCost = 0;
                return;
        }
        if (e->nextMove < H || e->nextMove == REST)
        {
            char targetCell = getCell(e->nextMove, e->p, m);
            struct p np = getP(e->nextMove, e->p);
            if (e->nextMove != H && e->nextMove != REST)
            {
                for (int i = 0; i < m->eCount; i++)
                {
                    if (e != &(m->e[i]) && np.y == m->e[i].p.y && np.x == m->e[i].p.x)
                        targetCell = PLACEHOLDER;
                }
            }
            if (getCost(e->c, targetCell) >= getCost(e->c, PLACEHOLDER))
                e->nextMove = H;
        }
    }
    setMoveCost(e, m);
    mvaddch(e->p.y + 1, e->p.x, m->cells[e->p.y][e->p.x]);
    doMove(e);
    mvaddch(e->p.y + 1, e->p.x, e->c);
}

void setGetMove(struct map *m, char entity)
{
    switch (entity)
    {
        case PC:
            m->e[m->eCount - 1].getMove = getMoveSentry;
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
            m->e[m->eCount - 1].emove = movePC;
            return;
        default:
            m->e[m->eCount - 1].emove = moveNPC;
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
        default:
            break;
    }
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
        case NW:
            return m->cells[p.y - 1][p.x - 1];
        case NE:
            return m->cells[p.y - 1][p.x + 1];
        case SW:
            return m->cells[p.y + 1][p.x - 1];
        case SE:
            return m->cells[p.y + 1][p.x + 1];
        default:
            return m->cells[p.y][p.x];
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