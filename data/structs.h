//
// Created by enicely on 4/19/23.
//

#ifndef CS327_STRUCTS_H
#define CS327_STRUCTS_H

#include <string>
#include "csv.h"

extern std::string get_move_names(int id);

struct experience
{
    int growth_rate_id, level, experience;
};
struct moves
{
    int id;
    std::string identifier;
    int generation_id, type_id, power, pp, accuracy, priority, target_id, damage_class_id, effect_id, effect_chance, contest_type_id, contest_effect_id, super_contest_effect_id;
};
struct pokemon_struct
{
    int id;
    std::string identifier;
    int species_id, height, weight, base_experience, order, is_default;
    int level = 1;
};

struct pokemon_moves_struct
{
    int pokemon_id, version_group_id, move_id, pokemon_move_method_id, level, order;
};

struct move_names
{
    int move_id, local_language_id;
    std::string name;
};

struct pokemon_moves : pokemon_moves_struct
{
    explicit pokemon_moves(pokemon_moves_struct aStruct) : pokemon_moves_struct()
    {
        name = get_move_names(aStruct.move_id);
    }

    std::string name;
};

struct pokemon_species
{
    int id;
    std::string identifier;
    int generation_id, evolves_from_species_id, evolution_chain_id, color_id, shape_id, habitat_id, gender_rate, capture_rate, base_happiness, is_baby, hatch_counter, has_gender_differences, growth_rate_id, forms_switchable, is_legendary, is_mythical, order, conquest_order;
};
struct pokemon_stats
{
    int pokemon_id, stat_id, base_stat, effort;
};
struct pokemon_types
{
    int pokemon_id, type_id, slot;
};
struct stats
{
    int id, damage_class_id;
    std::string identifier;
    int is_battle_only, game_index;
};
struct type_names
{
    int type_id, local_language_id;
    std::string name;
};
struct types
{
    int id;
    std::string identifier;
    int generation_id, damage_class_id;
};

#endif //CS327_STRUCTS_H
