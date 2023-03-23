#include <ncurses.h>
#include "map/map.h"
#include "map/grid.h"
#include "entity/entity.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include "data/heap.h"
#include <time.h>

int testMode = 0;

int main(int argc, char *argv[])
{
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
        if (!strcmp(argv[i], "--norun"))
        {
            return 0;
        }
    }
    do
    {
        initscr();
        raw();
        noecho();
        curs_set(0);
        keypad(stdscr, TRUE);
        int y = 0, x = 0;
        struct grid g;
        struct map *m;
        initGrid(&g, time(NULL));
        m = getMap(&g, y, x);

        addEntities(num, m);
        display(m);

        node *root = NULL;
        const int fps = 100;
        const int timescale = 1000 / (fps * 10);
        struct timeval tv;
        int startTime;
        int time;
        gettimeofday(&tv, NULL);
        startTime = (1000 * tv.tv_sec) + (tv.tv_usec / 1000);

        //set initial
        for (int i = 0; i < m->eCount; i++)
        {
            m->e[i].nextMoveTime = i;
            root = insert(root, m->e[i].nextMoveTime, &(m->e[i]));
        }
        display(m);

        int iters = innerLoopIters;

        while (!testMode || iters--)
        {
            struct entity *e = (struct entity *) root->data;
            gettimeofday(&tv, NULL);
            time = (1000 * tv.tv_sec) + (tv.tv_usec / 1000) - startTime;
            int wait = e->nextMoveTime - time;
            if (testMode && e->nextMoveTime > time)
            {
                refresh();
                usleep(wait * 1000);
            }
            e->emove(e, m);
            e->nextMoveTime += e->nextMoveCost * timescale;
            root = deleteMin(root);
            root = insert(root, e->nextMoveTime, e);
        }
        free(m->e);
        free(m);
        deleteAll(root);
        endwin();
    } while (--testMode);
}
