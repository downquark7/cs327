//
// Created by downq on 4/6/2023.
//

#ifndef CS327_CSV_H
#define CS327_CSV_H

#include "pokemon.h"
#include "structs.h"
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
    static void join();
    static std::vector<experience> experience_vector;
    static std::vector<moves> moves_vector;
    static std::vector<pokemon_struct> pokemon_vector;
    static pokemon_struct get_pokemon();
    static std::vector<pokemon_moves> pokemon_moves_vector;
    static pokemon_moves get_pokemon_moves(pokemon *pokemon);
    static std::vector<pokemon_species> pokemon_species_vector;
    static std::vector<pokemon_stats> pokemon_stats_vector;
    static __gnu_cxx::__normal_iterator<pokemon_stats *, std::vector<pokemon_stats>> get_pokemon_stats(int id);
    static std::vector<pokemon_types> pokemon_types_vector;
    static std::vector<stats> stats_vector;
    static std::vector<type_names> type_names_vector;
    static std::vector<types> types_vector;
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
};

#endif //CS327_CSV_H
