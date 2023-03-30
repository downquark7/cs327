//
// Created by downq on 3/23/2023.
//

#include "battle.h"
#include <menu.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

int battleTest()
{
    int characters[] = {KEY_DOWN, KEY_UP, 27, ' ', 'q', KEY_ENTER};
    return characters[rand() % 6];
}

extern int testMode;

int enterBattle(struct entity *e, struct map *m)
{
    clear();
    const char *choices[] = {"battle opt 1", "battle opt 2", "battle opt 3", "battle opt 4", "Exit"};
    ITEM **my_items;
    int c = 2;
    MENU *my_menu;
    int n_choices, i;

    n_choices = ARRAY_SIZE(choices);
    my_items = (ITEM **) calloc(n_choices + 1, sizeof(ITEM *));

    for (i = 0; i < n_choices; ++i)
        my_items[i] = new_item(choices[i], choices[i]);
    my_items[n_choices] = (ITEM *) NULL;

    my_menu = new_menu((ITEM **) my_items);
    post_menu(my_menu);

    while (c != 27 && (c = (testMode ? battleTest() : getch())))
    {
        switch (c)
        {
            case KEY_DOWN:
                menu_driver(my_menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(my_menu, REQ_UP_ITEM);
                break;
            case KEY_ENTER:
            case ' ':
            case 27:
            case 'q':
                c = 27;
                break;
        }
    }
    unpost_menu(my_menu);
    free_menu(my_menu);
    for (i = 0; i < n_choices + 1; ++i)
        free_item(my_items[i]);
    free(my_items);
    e->emove = defeated;
    return 0;
}