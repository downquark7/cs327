//
// Created by enicely on 4/13/23.
//

#ifndef CS327_POKEMON_H
#define CS327_POKEMON_H

#include <vector>
#include <string>
#include "csv.h"
#include "structs.h"

class pokemon {
public:
    pokemon(int level);

    pokemon();

    int id;
    std::string identifier;
    int species_id;
    int height;
    int weight;
    int base_experience;
    int order;
    int level;
    int base_stats[6];
    int ivs[6];
    int stats[6]; //hp, attack, defence, special-attack, special-defence, speed, accuracy, evasion
    bool shiny;
    bool gender;

    std::vector<pokemon_moves> moves;

    void levelUp();

    void calc();

};


#endif //CS327_POKEMON_H
