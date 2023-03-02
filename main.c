#include <stdio.h>
#include "map/map.h"
#include "map/grid.h"
#include "entity/entity.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "data/heap.h"

int main(int argc, char *argv[])
{
    while (1)
    {
        int y = 0, x = 0;
        struct grid g;
        struct map *m;
        initGrid(&g, time(NULL));
        printf("main seed: %d\n", g.seed);
        m = getMap(&g, y, x);

        srand(m->seed);
        addEntity(m, PC);
        addEntity(m, HIKER);
        addEntity(m, RIVAL);
        addEntity(m, PACER);
        addEntity(m, WANDERER);
        addEntity(m, SENTRY);
        addEntity(m, EXPLORER);
        addEntity(m, SWIMMER);
        display(m);


        node *root = NULL;
        const int fps = 1;
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
            m->e[i].nextMoveTime = m->e[i].thisMoveCost * timescale - i;
            root = insert(root, m->e[i].nextMoveTime, &(m->e[i]));
        }

        int iters = 1000;

        while (iters--)
        {
            struct entity *e = (struct entity *) root->data;
            gettimeofday(&tv, NULL);
            time = (1000 * tv.tv_sec) + (tv.tv_usec / 1000) - startTime;
            int wait = e->nextMoveTime - time;
            if (e->nextMoveTime > time)
                usleep(wait * 1000);
            e->move(e, m);
            if (e->c == PC)
            {
                printf("\ntime: %d ms\n", e->nextMoveTime);
                display(m);
            }
            if (e->nextMove == H)
                e->nextMoveCost = m->e[0].thisMoveCost;
            e->nextMoveTime += e->nextMoveCost * timescale;
            printf("%c%d ", e->c, e->thisMoveCost);
            root = deleteMin(root);
            root = insert(root, e->nextMoveTime, e);
        }
        free(m->e);
        free(m);
        deleteAll(root);
    }
}
