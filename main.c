#include <stdio.h>
#include "map/map.h"
#include "map/grid.h"
#include "entity/entity.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>
#include "data/heap.h"

int main(int argc, char *argv[])
{
    int testMode = 0;
    int innerLoopIters = 0;
    int num = 10;
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "--test") && i + 1 < argc)
        {
            testMode = innerLoopIters = strtol(argv[i + 1], NULL, 10);
        }
        if (!strcmp(argv[i], "--numtrainers") && i + 1 < argc)
        {
            num = strtol(argv[i + 1], NULL, 10);
            if (num < 0) num = 0;
        }
    }
    do
    {
        int y = 0, x = 0;
        struct grid g;
        struct map *m;
        initGrid(&g, time(NULL));
        printf("main seed: %d\n", g.seed);
        m = getMap(&g, y, x);

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
        display(m);


        node *root = NULL;
        const int fps = 4;
        const int timescale = 1000 / (fps * m->e[0].thisMoveCost);
        struct timeval tv;
        int startTime;
        int time;
        gettimeofday(&tv, NULL);
        startTime = (1000 * tv.tv_sec) + (tv.tv_usec / 1000);

        //set initial
        for (int i = 0; i < m->eCount; i++)
        {
            m->e[i].getMove(&(m->e[i]), m);
            if (m->e[i].nextMove == H)
                m->e[i].thisMoveCost = m->e[0].thisMoveCost;
            //make the turn order more predictable for entities with same move cost with -i
            m->e[i].nextMoveTime = 1000 + m->e[i].nextMoveCost * timescale - i;
            root = insert(root, m->e[i].nextMoveTime, &(m->e[i]));
        }

        int iters = innerLoopIters;

        while (!testMode || iters--)
        {
            struct entity *e = (struct entity *) root->data;
            if (e->c == PC)
            {
                gettimeofday(&tv, NULL);
                time = (1000 * tv.tv_sec) + (tv.tv_usec / 1000) - startTime;
                int wait = e->nextMoveTime - time;
                if (e->nextMoveTime > time && !testMode)
                    usleep(wait * 1000);
                printf("\ntime: %d ms\n", e->nextMoveTime);
                if (!testMode)
                    display(m);
            }
            e->move(e, m);
            if (e->nextMove == H)
                e->nextMoveCost = m->e[0].thisMoveCost;
            e->nextMoveTime += e->nextMoveCost * timescale;
            printf("%c%d[%d][%d] ", e->c, e->thisMoveCost, e->p.y, e->p.x);
            root = deleteMin(root);
            root = insert(root, e->nextMoveTime, e);
            if (testMode)
            {
                for (int i = 0; i < m->eCount; i++)
                    for (int o = 0; o < m->eCount; o++)
                        if (i != o && m->e[i].p.y == m->e[o].p.y && m->e[i].p.x == m->e[o].p.x)
                        {
                            display(m);
                            printf("%c [%d][%d]\n", e->c, e->p.y, e->p.x);
                            printf("%c %c [%d][%d]\n", m->e[i].c, m->e[o].c, m->e[i].p.y, m->e[o].p.x);
                            abort();
                        }
            }
        }
        free(m->e);
        free(m);
        deleteAll(root);
    } while (--testMode);
}
