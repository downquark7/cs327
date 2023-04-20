#include <ncurses.h>
#include "map/map.h"
#include "map/grid.h"
#include "entity/entity.h"
#include <cstdlib>
#include <unistd.h>
#include <sys/time.h>
#include <cstring>
#include "data/heap.h"
#include <ctime>
#include <iostream>
#include "data/csv.h"

int testMode = 0;

int main(int argc, char *argv[]) {
    srand(time(nullptr));
    csv::load();
//    for (int i = 0; i < 1; i++)
//        std::cout << a.pokemon_id << ", " << a.move_id << std::endl;

    int innerLoopIters = 0;
    int num = 10;
    int waitForDebug = 0;
    csv::load();

    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg == "--test" && i + 1 < argc)
        {
            testMode = innerLoopIters = strtol(argv[i + 1], nullptr, 10);
        } else if (arg == "--numtrainers" && i + 1 < argc)
        {
            num = strtol(argv[i + 1], nullptr, 10);
            if (num < 0) num = 0;
        } else if (arg == "--norun")
        {
            csv::join();
            return 0;
        } else if (arg == "--waitForDebug")
        {
            waitForDebug = 1;
        }
    }

    do
    {
        initscr();
        raw();
        noecho();
        curs_set(0);
        keypad(stdscr, TRUE);
        if (waitForDebug)
        {
            getch();
            getch();
            getch();
            waitForDebug = 0;
        }
        int y = 0, x = 0;
        struct grid g{};
        struct map *m;
        initGrid(&g, time(nullptr));
        m = getMap(&g, y, x);
        addEntities(num, m);
        display(m);

        m->root = nullptr;
        const int fps = 100;
        const int timescale = 1000 / (fps * 10);
        struct timeval tv;
        int startTime;
        int time;
        gettimeofday(&tv, nullptr);
        startTime = (1000 * tv.tv_sec) + (tv.tv_usec / 1000);

        //set initial
        for (int i = 0; i < m->eCount; i++)
        {
            m->e[i].nextMoveTime = i;
            m->root = insert(m->root, m->e[i].nextMoveTime, &(m->e[i]));
        }
        display(m);
        csv::join();

        int iters = innerLoopIters;

        while (!testMode || iters--)
        {
            auto *e = (struct entity *) m->root->data;
            gettimeofday(&tv, nullptr);
            time = (1000 * tv.tv_sec) + (tv.tv_usec / 1000) - startTime;
            int wait = e->nextMoveTime - time;
            if (testMode)
            {
                refresh();
                if (e->nextMoveTime > time)
                    usleep(wait * 1000);
            }
            e->emove(e, m);
            e->nextMoveTime += e->nextMoveCost * timescale;
            m->root = deleteMin(m->root);
            m->root = insert(m->root, e->nextMoveTime, e);
            if (e->nextMove == FLY)
            {
                e->nextMove = H;
                endwin();
                std::cout << "enter: yval xval\n";
                std::cin >> y >> x;
                initscr();
                raw();
                noecho();
                curs_set(0);
                keypad(stdscr, TRUE);
                m = getMap(&g, y, x);
                y = m->p.y;
                x = m->p.x;
                if (m->eCount == 0)
                {
                    addEntities(num, m, e);
                    for (int i = 0; i < m->eCount; i++)
                    {
                        m->e[i].nextMoveTime = i;
                        m->root = insert(m->root, m->e[i].nextMoveTime, &(m->e[i]));
                    }
                } else copyPC(m, e);
                char saved[m->eCount];
                for (int i = 1; i < m->eCount; i++)
                {
                    saved[i] = m->cells[m->e[i].p.y][m->e[i].p.x];
                    m->cells[m->e[i].p.y][m->e[i].p.x] = m->e[i].c;
                }
                while (m->cells[m->e[0].p.y][m->e[0].p.x] != ROAD)
                {
                    m->e[0].p.y = (rand() % (MAP_HEIGHT - 4)) + 2;
                    m->e[0].p.x = (rand() % (MAP_WIDTH - 4)) + 2;
                }
                for (int i = 1; i < m->eCount; i++)
                {
                    m->cells[m->e[i].p.y][m->e[i].p.x] = saved[i];
                }
                display(m);
            }
            if ((e == &(m->e[0]) && checkBounds(e->p)))
            {
                if (e->p.x == 0)
                {
                    e->p.x = MAP_WIDTH - 2;
                    x--;
                }
                if (e->p.y == 0)
                {
                    e->p.y = MAP_HEIGHT - 2;
                    y--;
                }
                if (e->p.x == MAP_WIDTH - 1)
                {
                    e->p.x = 1;
                    x++;
                }
                if (e->p.y == MAP_HEIGHT - 1)
                {
                    e->p.y = 1;
                    y++;
                }
                m = getMap(&g, y, x);
                if (m->eCount == 0)
                {
                    addEntities(num, m, e);
                    for (int i = 0; i < m->eCount; i++)
                    {
                        m->e[i].nextMoveTime = i;
                        m->root = insert(m->root, m->e[i].nextMoveTime, &(m->e[i]));
                    }
                } else copyPC(m, e);
                display(m);
            }
        }
        free(m->e);
        deleteAll(m->root);
        free(m);
        endwin();
    } while (--testMode);
}
