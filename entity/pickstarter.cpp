//
// Created by enicely on 4/19/23.
//

#include "pickstarter.h"
#include <menu.h>
#include <iostream>
#include "entity.h"
#include "../map/map.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

int starterTest() {
    int characters[] = {KEY_DOWN, KEY_UP, 27, ' ', KEY_ENTER};
    return characters[rand() % 5];
}

extern int testMode;

void enterSelect(struct entity *e) {
    clear();
    pokemon_struct array[] = {csv::get_pokemon(), csv::get_pokemon(), csv::get_pokemon()};
    const char *choices[] = {"choose starter pokemon:", array[0].identifier.c_str(), array[1].identifier.c_str(),
                             array[2].identifier.c_str()};
    ITEM **my_items;
    int c = 2;
    MENU *my_menu;
    int n_choices, i;

    n_choices = ARRAY_SIZE(choices);
    my_items = (ITEM **) calloc(n_choices + 1, sizeof(ITEM *));

    for (i = 0; i < n_choices; ++i)
        my_items[i] = new_item(choices[i], nullptr);
    my_items[n_choices] = (ITEM *) NULL;

    my_menu = new_menu((ITEM **) my_items);
    post_menu(my_menu);

    while (c != 27 && (c = (testMode ? starterTest() : getch()))) {
        switch (c) {
            case KEY_DOWN:
                menu_driver(my_menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(my_menu, REQ_UP_ITEM);
                break;
            case KEY_ENTER:
            case ' ':
                if (1 <= item_index(current_item(my_menu)) && item_index(current_item(my_menu)) <= 3) {
                    c = 27;
                    e->party[0] = new pokemon(array[item_index(current_item(my_menu)) - 1]);
                }
                break;
        }
    }
    unpost_menu(my_menu);
    free_menu(my_menu);
    for (i = 0; i < n_choices + 1; ++i)
        free_item(my_items[i]);
    free(my_items);
}
