//
// Created by enicely on 4/13/23.
//

#include "pokemon.h"
#include "csv.h"

pokemon::pokemon(int level) {
    pokemon::level = level;
    auto iter = csv::get_pokemon_stats(id);
    for (int i = 0; i < 6; i++)
        base_stats[i] = iter++->base_stat;
}

pokemon::pokemon() : pokemon::pokemon(1) {}

void pokemon::calc() {
    for (int i = 0; i < 8; i++) {

    }
}

void pokemon::levelUp() {
    level++;
    calc();
}
