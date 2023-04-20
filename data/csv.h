//
// Created by downq on 4/6/2023.
//

#ifndef CS327_CSV_H
#define CS327_CSV_H

#include "pokemon.h"
#include <vector>
#include <string>
#include <thread>

class pokemon;

class csv {
private:
    static int stoi(const std::string &s);

    static void thread_load_pokemon_moves();

    static void thread_load_everything_else();

public:
    static void load();

    static std::thread async;
//    static std::thread async2;

    static void join();

    struct experience {
        int growth_rate_id, level, experience;
    };
    static std::vector<experience> experience_vector;

    struct moves {
        int id;
        std::string identifier;
        int generation_id, type_id, power, pp, accuracy, priority, target_id, damage_class_id, effect_id, effect_chance, contest_type_id, contest_effect_id, super_contest_effect_id;
    };
    static std::vector<moves> moves_vector;

    struct pokemon_struct {
        int id;
        std::string identifier;
        int species_id, height, weight, base_experience, order, is_default;
        int level = 1;
    };
    static std::vector<pokemon_struct> pokemon_vector;

    static pokemon_struct get_pokemon();

    struct pokemon_moves {
        int pokemon_id, version_group_id, move_id, pokemon_move_method_id, level, order;
    };
    static std::vector<pokemon_moves> pokemon_moves_vector;

    static pokemon_moves get_pokemon_moves(pokemon *pokemon);

    struct pokemon_species {
        int id;
        std::string identifier;
        int generation_id, evolves_from_species_id, evolution_chain_id, color_id, shape_id, habitat_id, gender_rate, capture_rate, base_happiness, is_baby, hatch_counter, has_gender_differences, growth_rate_id, forms_switchable, is_legendary, is_mythical, order, conquest_order;
    };
    static std::vector<pokemon_species> pokemon_species_vector;

    struct pokemon_stats {
        int pokemon_id, stat_id, base_stat, effort;
    };
    static std::vector<pokemon_stats> pokemon_stats_vector;

    static __gnu_cxx::__normal_iterator<pokemon_stats *, std::vector<pokemon_stats>> get_pokemon_stats(int id);

    struct pokemon_types {
        int pokemon_id, type_id, slot;
    };
    static std::vector<pokemon_types> pokemon_types_vector;

    struct stats {
        int id, damage_class_id;
        std::string identifier;
        int is_battle_only, game_index;
    };
    static std::vector<stats> stats_vector;

    struct type_names {
        int type_id, local_language_id;
        std::string name;
    };
    static std::vector<type_names> type_names_vector;

    static void load_experience();

    static void load_moves();

    static void load_pokemon();

    static void load_pokemon_moves();

    static void load_pokemon_species();

    static void load_pokemon_stats();

    static void load_pokemon_types();

    static void load_stats();

    static void load_type_names();

    static void load_types();

    struct types {
        int id;
        std::string identifier;
        int generation_id, damage_class_id;
    };
    static std::vector<csv::types> types_vector;
};

#endif //CS327_CSV_H
