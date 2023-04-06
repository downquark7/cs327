//
// Created by downq on 4/6/2023.
//

#ifndef CS327_CSV_H
#define CS327_CSV_H

#include <vector>
#include <string>

class csv
{
public:
    struct experience
    {
        int growth_rate_id, level, experience;
    };
    std::vector<experience> experience_vector;

    void get_experience();

    struct moves
    {
        int id;
        std::string identifier;
        int generation_id, type_id, power, pp, accuracy, priority, target_id, damage_class_id, effect_id, effect_chance, contest_type_id, contest_effect_id, super_contest_effect_id;
    };
    std::vector<moves> moves_vector;

    void get_moves();

    struct pokemon
    {
        int id;
        std::string identifier;
        int species_id, height, weight, base_experience, order, is_default;
    };
    std::vector<pokemon> pokemon_vector;

    void get_pokemon();

    struct pokemon_moves
    {
        int pokemon_id, version_group_id, move_id, pokemon_move_method_id, level, order;
    };
    std::vector<pokemon_moves> pokemon_moves_vector;

    void get_pokemon_moves();

    struct pokemon_species
    {
        int id;
        std::string identifier;
        int generation_id, evolves_from_species_id, evolution_chain_id, color_id, shape_id, habitat_id, gender_rate, capture_rate, base_happiness, is_baby, hatch_counter, has_gender_differences, growth_rate_id, forms_switchable, is_legendary, is_mythical, order, conquest_order;
    };
    std::vector<pokemon_species> pokemon_species_vector;

    void get_pokemon_species();

    struct pokemon_stats
    {
        int pokemon_id, stat_id, base_stat, effort;
    };
    std::vector<pokemon_stats> pokemon_stats_vector;

    void get_pokemon_stats();

    struct pokemon_types
    {
        int pokemon_id, type_id, slot;
    };
    std::vector<pokemon_types> pokemon_types_vector;

    void get_pokemon_types();

    struct stats
    {
        int id, damage_class_id;
        std::string identifier;
        int is_battle_only, game_index;
    };
    std::vector<stats> stats_vector;

    void get_stats();

    struct type_names
    {
        int type_id, local_language_id;
        std::string name;
    };
    std::vector<type_names> type_names_vector;

    void get_type_names();

    void get_all();
private:
    static int stoi(const std::string &s);

};

#endif //CS327_CSV_H
