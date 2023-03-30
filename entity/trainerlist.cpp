//
// Created by downq on 3/22/2023.
//

#include "trainerlist.h"
#include <menu.h>
#include <stdlib.h>
#include "entity.h"

void distanceToString(char *output, struct p p1, struct p p2);

int trainerlistTest()
{
    refresh();
    int characters[] = {KEY_DOWN, KEY_UP, 27, ' ', 'q', KEY_ENTER};
    return characters[rand() % 6];
}

extern int testMode;

void enterList(struct map *m)
{
    clear();
    ITEM **my_items;
    int c = 1;
    MENU *my_menu;
    int num_trainers, i;
    num_trainers = m->eCount - 1;
    my_items = (ITEM **) calloc(num_trainers + 1, sizeof(ITEM *));
    char *string = static_cast<char *>(malloc(num_trainers * 23));
    char *pointer = string;

    for (i = 0; i < num_trainers; ++i)
    {
        pointer[0] = m->e[i + 1].c;
        pointer[1] = 0;
        distanceToString(pointer + 2, m->e[0].p, m->e[i + 1].p);
        my_items[i] = new_item(pointer, pointer + 2);
        pointer += 23;
    }
    my_items[num_trainers] = (ITEM *) NULL;

    my_menu = new_menu((ITEM **) my_items);
    post_menu(my_menu);

    while (c != 27 && (c = testMode ? trainerlistTest() : getch()))
    {
        switch (c)
        {
            case KEY_DOWN:
                menu_driver(my_menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(my_menu, REQ_UP_ITEM);
                break;
            case 27:
            case 'q':
            case ' ':
            case KEY_ENTER:
                c = 27;
                break;
        }
    }

    unpost_menu(my_menu);
    free_menu(my_menu);
    for (i = 0; i < num_trainers + 1; ++i)
        free_item(my_items[i]);
    free(my_items);
    free(string);
}

int clip99(int n)
{
    return n > 99 ? 99 : n < -99 ? -99 : n;
}

void distanceToString(char *output, struct p p1, struct p p2)
{
    int y = clip99(p2.y - p1.y);
    int x = clip99(p2.x - p1.x);
    if (x == 0 && y == 0)
    {
        sprintf(output, "impossible");
    } else if (x > 0 && y == 0)
    {
        sprintf(output, "%d east", x);
    } else if (x < 0 && y == 0)
    {
        sprintf(output, "%d west", -x);
    } else if (x == 0 && y > 0)
    {
        sprintf(output, "%d north", y);
    } else if (x == 0 && y < 0)
    {
        sprintf(output, "%d south", -y);
    } else if (x > 0 && y > 0)
    {
        sprintf(output, "%d north and %d east", y, x);
    } else if (x > 0 && y < 0)
    {
        sprintf(output, "%d south and %d east", -y, x);
    } else if (x < 0 && y > 0)
    {
        sprintf(output, "%d north and %d west", y, -x);
    } else if (x < 0 && y < 0)
    {
        sprintf(output, "%d south and %d west", -y, -x);
    }
}