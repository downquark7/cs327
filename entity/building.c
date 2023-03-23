//
// Created by downq on 3/22/2023.
//

#include "building.h"
#include <menu.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

int buildingTest()
{
    refresh();
    int characters[] = {KEY_DOWN, KEY_UP, 27, ' ', 'q', KEY_ENTER};
    return characters[rand() % 6];
}

int enterBuilding(char cell)
{
    switch (cell)
    {
        case 'C':
            break;
        case 'M':
            break;
        default:
            return 1;
    }
    clear();
    char *choices[] = {"Choice 1", "Choice 2", "Choice 3", "Choice 4", "Exit"};
    ITEM **my_items;
    int c = 0;
    MENU *my_menu;
    int n_choices, i;

    n_choices = ARRAY_SIZE(choices);
    my_items = (ITEM **) calloc(n_choices + 1, sizeof(ITEM *));

    for (i = 0; i < n_choices; ++i)
        my_items[i] = new_item(choices[i], choices[i]);
    my_items[n_choices] = (ITEM *) NULL;

    my_menu = new_menu((ITEM **) my_items);
    menu_opts_off(my_menu, O_ONEVALUE);
    post_menu(my_menu);
    extern int testMode;

    while (c != 27 && (c = testMode ? buildingTest() : getch()))
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
                menu_driver(my_menu, REQ_TOGGLE_ITEM);
                if (!item_value(my_items[4]))
                    break;
            case 27:
            case 'q':
                c = 27;
                break;
        }
    }

    for (i = 0; i < n_choices + 1; ++i)
        free_item(my_items[i]);
    free_menu(my_menu);
    return 0;
}