//
// Created by enicely on 4/13/23.
//

#include "pokemon.h"
#include <random>

pokemon::pokemon(int level) : pokemon::pokemon(csv::get_pokemon())
{
    pokemon::level = level;
}

pokemon::pokemon() : pokemon::pokemon(1)
{

}

pokemon::pokemon(pokemon_struct a)
{
    id = a.id;
    species_id = a.species_id;
    identifier = a.identifier;
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<> distribution(0, 15);

    auto iter = csv::get_pokemon_stats(id);
    for (int i = 0; i < 6; i++)
        base_stats[i] = iter++->base_stat;
    //hp, attack, defence, special-attack, special-defence, speed
    for (int i = 0; i < 6; i++)
        ivs[i] = distribution(engine);

    calc();

    std::uniform_int_distribution<> coinflip(0, 1);
    std::uniform_int_distribution<> shinydist(1, 8192);

    gender = coinflip(engine);
    shiny = shinydist(engine) == 1;

//    moves_future = std::async(std::launch::deferred, csv::get_pokemon_moves, this);
    moves = csv::get_pokemon_moves(this);
}

void pokemon::calc()
{
    //hp, attack, defence, special-attack, special-defence, speed
    stats[0] = ((base_stats[0] + ivs[0]) * 2 * level) / 100 + level + 10;
    for (int i = 1; i < 6; i++)
    {
        stats[i] = ((base_stats[i] + ivs[i]) * 2 * level) / 100 + 5;
    }
    currenthp = stats[0];
}

void pokemon::levelUp()
{
    level++;
    calc();
}
