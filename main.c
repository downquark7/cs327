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
    int y = 0, x = 0;
    struct grid g;
    struct map *m;
    initGrid(&g, 445414);//time(NULL));
    printf("main seed: %d\n", g.seed);
    m = getMap(&g, y, x);

    srand(m->seed);
    addEntity(m, PC);
    addEntity(m, HIKER);
    addEntity(m, RIVAL);
    addEntity(m, SWIMMER);
    display(m);


    node *root = NULL;
    const int fps = 1;
    const int timescale = 1000000 / (fps * m->e[0].thisMoveCost);
    struct timeval tv;
    uint64_t startTime;
    uint64_t time;
    gettimeofday(&tv, NULL);
    startTime = 1000000 * tv.tv_sec + tv.tv_usec;

    //set initial
    for (int i = 0; i < m->eCount; i++)
    {
        m->e[i].getMove(&(m->e[i]), m);
        if (m->e[i].nextMove == H)
            m->e[i].thisMoveCost = m->e[0].thisMoveCost;
        m->e[i].nextMoveTime = m->e[i].thisMoveCost * timescale;
        root = insert(root, m->e[i].nextMoveTime, &(m->e[i]));
    }

    while (1)
    {
        struct entity *e = (struct entity *) root->data;
        gettimeofday(&tv, NULL);
        time = 1000000 * tv.tv_sec + tv.tv_usec - startTime;
        uint64_t wait = e->nextMoveTime - time;
        if (e->nextMoveTime > time)
            usleep(wait);
        e->move(e, m);
        if (e->nextMove == H)
            e->thisMoveCost = m->e[0].thisMoveCost;
        e->nextMoveTime += e->nextMoveCost * timescale;
        if (e->c == PC)
        {
            printf(" updated\ttime: %.2f\n", time / 1000000.0);
            display(m);
        }
        printf("%c", e->c);
        root = deleteMin(root);
        root = insert(root, e->nextMoveTime, e);
    }
    free(m->e);
    free(m);
    deleteAll(root);
}
