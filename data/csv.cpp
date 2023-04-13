//
// Created by downq on 4/5/2023.
//

#include "csv.h"
#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include <climits>
#include <thread>

using namespace std;

std::vector<csv::experience> csv::experience_vector;
std::vector<csv::moves> csv::moves_vector;
std::vector<csv::pokemon> csv::pokemon_vector;
std::vector<csv::pokemon_moves> csv::pokemon_moves_vector;
std::vector<csv::pokemon_species> csv::pokemon_species_vector;
std::vector<csv::pokemon_stats> csv::pokemon_stats_vector;
std::vector<csv::pokemon_types> csv::pokemon_types_vector;
std::vector<csv::stats> csv::stats_vector;
std::vector<csv::type_names> csv::type_names_vector;
std::thread csv::async;
std::thread csv::async2;

int csv::stoi(const string &s) {
    if (s.empty())
        return INT_MAX;
    return std::stoi(s);
}

string parse(int i) {
    if (i == INT_MAX)
        return "";
    return to_string(i);
}

string parse(const string &s) {
    return s;
}

ifstream getFile(const char *filename) {
    string path = "/share/cs327/pokedex/pokedex/data/csv/";
    ifstream file(path + filename);
    if (!file.is_open()) {
        path = string(getenv("HOME")) + "/.poke327/pokedex/pokedex/data/csv/";
        file.open(path + filename);
    }
    if (!file.is_open()) {
        cout << "Could not find file... exiting\n";
        abort();
    }
    return file;
}

void csv::get_experience() {
    ifstream file = getFile("experience.csv");
    string line;
    regex pattern("(-?\\d*),(-?\\d*),(-?\\d*)", std::regex_constants::ECMAScript | std::regex_constants::optimize);
    smatch match;
    while (getline(file, line)) {
        struct experience data;
        if (regex_match(line, match, pattern, std::regex_constants::match_continuous)) {
            data.growth_rate_id = stoi(match[1]);
            data.level = stoi(match[2]);
            data.experience = stoi(match[3]);
            experience_vector.push_back(data);
        }
    }
    file.close();
#ifdef DEBUG
    cout << "growth_rate_id,level,experience\n";
    for (const auto &data: experience_vector)
        cout << parse(data.growth_rate_id) << ',' << parse(data.level) << ',' << parse(data.experience) << '\n';
#endif
}

void csv::get_moves() {
    ifstream file = getFile("moves.csv");
    string line;
    regex pattern(
            "(-?\\d*),([\\w-]*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*)",
            std::regex_constants::ECMAScript | std::regex_constants::optimize);
    smatch match;
    while (getline(file, line)) {
        struct moves data;
        if (regex_match(line, match, pattern, std::regex_constants::match_continuous)) {
            data.id = stoi(match[1]);
            data.identifier = match[2];
            data.generation_id = stoi(match[3]);
            data.type_id = stoi(match[4]);
            data.power = stoi(match[5]);
            data.pp = stoi(match[6]);
            data.accuracy = stoi(match[7]);
            data.priority = stoi(match[8]);
            data.target_id = stoi(match[9]);
            data.damage_class_id = stoi(match[10]);
            data.effect_id = stoi(match[11]);
            data.effect_chance = stoi(match[12]);
            data.contest_type_id = stoi(match[13]);
            data.contest_effect_id = stoi(match[14]);
            data.super_contest_effect_id = stoi(match[15]);
            moves_vector.push_back(data);
        }
    }
    file.close();
#ifdef DEBUG
    cout
            << "id,identifier,generation_id,type_id,power,pp,accuracy,priority,target_id,damage_class_id,effect_id,effect_chance,contest_type_id,contest_effect_id,super_contest_effect_id\n";
    for (const auto &data: moves_vector)
        cout << parse(data.id) << ',' << parse(data.identifier) << ',' << parse(data.generation_id) << ','
             << parse(data.type_id) << ','
             << parse(data.power) << ',' << parse(data.pp) << ',' << parse(data.accuracy) << ',' << parse(data.priority)
             << ',' << parse(data.target_id)
             << ',' << parse(data.damage_class_id) << ',' << parse(data.effect_id) << ',' << parse(data.effect_chance)
             << ','
             << parse(data.contest_type_id) << ',' << parse(data.contest_effect_id) << ','
             << parse(data.super_contest_effect_id) << '\n';
#endif
}

void csv::get_pokemon() {
    ifstream file = getFile("pokemon.csv");
    string line;
    regex pattern("(-?\\d*),(.*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*)",
                  std::regex_constants::ECMAScript | std::regex_constants::optimize);
    smatch match;
    while (getline(file, line)) {
        struct pokemon data;
        if (regex_match(line, match, pattern, std::regex_constants::match_continuous)) {
            data.id = stoi(match[1]);
            data.identifier = match[2];
            data.species_id = stoi(match[3]);
            data.height = stoi(match[4]);
            data.weight = stoi(match[5]);
            data.base_experience = stoi(match[6]);
            data.order = stoi(match[7]);
            data.is_default = stoi(match[8]);
            pokemon_vector.push_back(data);
        }
    }
    file.close();
#ifdef DEBUG
    cout << "id,identifier,species_id,height,weight,base_experience,order,is_default\n";
    for (const auto &data: pokemon_vector)
        cout << parse(data.id) << ',' << parse(data.identifier) << ',' << parse(data.species_id) << ','
             << parse(data.height) << ',' << parse(data.weight)
             << ',' << parse(data.base_experience) << ',' << parse(data.order) << ',' << parse(data.is_default) << '\n';
#endif
}

void csv::get_pokemon_moves() {
    ifstream file = getFile("pokemon_moves.csv");
    string line;
    regex pattern("(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*)",
                  std::regex_constants::ECMAScript | std::regex_constants::optimize);
    smatch match;
    while (getline(file, line)) {
        struct pokemon_moves data;
        if (regex_match(line, match, pattern, std::regex_constants::match_continuous)) {
            data.pokemon_id = stoi(match[1]);
            data.version_group_id = stoi(match[2]);
            data.move_id = stoi(match[3]);
            data.pokemon_move_method_id = stoi(match[4]);
            data.level = stoi(match[5]);
            data.order = stoi(match[6]);
            pokemon_moves_vector.push_back(data);
        }
    }
#ifdef DEBUG
    cout << "pokemon_id,version_group_id,move_id,pokemon_move_method_id,level,order\n";
    for (const auto &data: pokemon_moves_vector)
        cout << parse(data.pokemon_id) << ',' << parse(data.version_group_id) << ',' << parse(data.move_id) << ','
             << parse(data.pokemon_move_method_id) << ',' << parse(data.level) << ',' << parse(parse(data.order))
             << '\n';
#endif
}

void csv::get_pokemon_species() {
    ifstream file = getFile("pokemon_species.csv");
    string line;
    regex pattern(
            "(-?\\d*),([^,]*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*)",
            std::regex_constants::ECMAScript | std::regex_constants::optimize);
    smatch match;
    while (getline(file, line)) {
        struct pokemon_species data;
        if (regex_match(line, match, pattern, std::regex_constants::match_continuous)) {
            data.id = stoi(match[1]);
            data.identifier = match[2];
            data.generation_id = stoi(match[3]);
            data.evolves_from_species_id = stoi(match[4]);
            data.evolution_chain_id = stoi(match[5]);
            data.color_id = stoi(match[6]);
            data.shape_id = stoi(match[7]);
            data.habitat_id = stoi(match[8]);
            data.gender_rate = stoi(match[9]);
            data.capture_rate = stoi(match[10]);
            data.base_happiness = stoi(match[11]);
            data.is_baby = stoi(match[12]);
            data.hatch_counter = stoi(match[13]);
            data.has_gender_differences = stoi(match[14]);
            data.growth_rate_id = stoi(match[15]);
            data.forms_switchable = stoi(match[16]);
            data.is_legendary = stoi(match[17]);
            data.is_mythical = stoi(match[18]);
            data.order = stoi(match[19]);
            data.conquest_order = stoi(match[20]);
            pokemon_species_vector.push_back(data);
        }
    }
    file.close();
#ifdef DEBUG
    cout
            << "id,identifier,generation_id,evolves_from_species_id,evolution_chain_id,color_id,shape_id,habitat_id,gender_rate,capture_rate,base_happiness,is_baby,hatch_counter,has_gender_differences,growth_rate_id,forms_switchable,is_legendary,is_mythical,order,conquest_order\n";
    for (const auto &data: pokemon_species_vector)
        cout << parse(data.id) << ',' << parse(data.identifier) << ',' << parse(data.generation_id) << ','
             << parse(data.evolves_from_species_id) << ',' << parse(data.evolution_chain_id) << ','
             << parse(data.color_id) << ','
             << parse(data.shape_id) << ',' << parse(parse(data.habitat_id)) << ',' << parse(data.gender_rate) << ','
             << parse(data.capture_rate)
             << ',' << parse(data.base_happiness) << ',' << parse(data.is_baby) << ',' << parse(data.hatch_counter)
             << ','
             << parse(data.has_gender_differences) << ',' << parse(data.growth_rate_id) << ','
             << parse(data.forms_switchable) << ','
             << parse(data.is_legendary) << ',' << parse(data.is_mythical) << ',' << parse(data.order) << ','
             << parse(data.conquest_order)
             << '\n';
#endif
}

void csv::get_pokemon_stats() {
    ifstream file = getFile("pokemon_stats.csv");
    string line;
    regex pattern("(-?\\d*),(-?\\d*),(-?\\d*),(-?\\d*)",
                  std::regex_constants::ECMAScript | std::regex_constants::optimize);
    smatch match;
    while (getline(file, line)) {
        struct pokemon_stats data;
        if (regex_match(line, match, pattern, std::regex_constants::match_continuous)) {
            data.pokemon_id = stoi(match[1]);
            data.stat_id = stoi(match[2]);
            data.base_stat = stoi(match[3]);
            data.effort = stoi(match[4]);
            pokemon_stats_vector.push_back(data);
        }
    }
    file.close();
#ifdef DEBUG
    cout << "pokemon_id,stat_id,base_stat,effort\n";
    for (const auto &data: pokemon_stats_vector)
        cout << parse(data.pokemon_id) << ',' << parse(data.stat_id) << ',' << parse(data.base_stat) << ','
             << parse(data.effort) << '\n';
#endif
}

void csv::get_pokemon_types() {
    ifstream file = getFile("pokemon_types.csv");
    string line;
    regex pattern("(-?\\d*),(-?\\d*),(-?\\d*)", std::regex_constants::ECMAScript | std::regex_constants::optimize);
    smatch match;
    while (getline(file, line)) {
        struct pokemon_types data;
        if (regex_match(line, match, pattern, std::regex_constants::match_continuous)) {
            data.pokemon_id = stoi(match[1]);
            data.type_id = stoi(match[2]);
            data.slot = stoi(match[3]);
            pokemon_types_vector.push_back(data);
        }
    }
    file.close();
#ifdef DEBUG
    cout << "pokemon_id,type_id,slot\n";
    for (const auto &data: pokemon_types_vector)
        cout << parse(data.pokemon_id) << ',' << parse(data.type_id) << ',' << parse(data.slot) << '\n';
#endif
}

void csv::get_stats() {
    ifstream file = getFile("stats.csv");
    string line;
    regex pattern("(-?\\d*),(-?\\d*),([^,]*),(-?\\d*),(-?\\d*)",
                  std::regex_constants::ECMAScript | std::regex_constants::optimize);
    smatch match;
    while (getline(file, line)) {
        struct stats data;
        if (regex_match(line, match, pattern, std::regex_constants::match_continuous)) {
            data.id = stoi(match[1]);
            data.damage_class_id = stoi(match[2]);
            data.identifier = match[3];
            data.is_battle_only = stoi(match[4]);
            data.game_index = stoi(match[5]);
            stats_vector.push_back(data);
        }
    }
    file.close();
#ifdef DEBUG
    cout << "id,damage_class_id,identifier,is_battle_only,game_index\n";
    for (const auto &data: stats_vector)
        cout << parse(data.id) << ',' << parse(data.damage_class_id) << ',' << parse(data.identifier) << ','
             << parse(data.is_battle_only) << ','
             << parse(data.game_index) << '\n';
#endif
}

void csv::get_type_names() {
    ifstream file = getFile("type_names.csv");
    string line;
    regex pattern("(-?\\d*),(-?\\d*),([^-]*)", std::regex_constants::ECMAScript | std::regex_constants::optimize);
    smatch match;
    while (getline(file, line)) {
        struct type_names data;
        if (regex_match(line, match, pattern, std::regex_constants::match_continuous)) {
            data.type_id = stoi(match[1]);
            data.local_language_id = stoi(match[2]);
            data.name = match[3];
            type_names_vector.push_back(data);
        }
    }
    file.close();
#ifdef DEBUG
    cout << "type_id,local_language_id,name\n";
    for (const auto &data: type_names_vector)
        cout << parse(data.type_id) << ',' << parse(data.local_language_id) << ',' << parse(data.name) << '\n';
#endif
}

void thread_get_pokemon_moves() {
    csv::get_pokemon_moves();
}

void thread_get_everything_else() {
    csv::get_experience();
    csv::get_moves();
    csv::get_pokemon();
    csv::get_pokemon_species();
    csv::get_pokemon_stats();
    csv::get_pokemon_types();
    csv::get_stats();
    csv::get_type_names();
}


void csv::load() {
    async = std::thread(thread_get_pokemon_moves);
    async2 = std::thread(thread_get_everything_else);
}

void csv::join() {
    async.join();
    async2.join();
}


