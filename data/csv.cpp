//
// Created by downq on 4/5/2023.
//

#include "csv.h"
#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include <climits>
#include <valarray>
#include <random>

using namespace std;

std::vector<std::string> split(const std::string &s)
{
    std::vector<std::string> result;
    result.reserve(22);
    result.emplace_back("");
    std::stringstream ss(s);
    std::string substr;
    while (std::getline(ss, substr, ','))
    {
        result.push_back(substr);
    }
    result.emplace_back("");
    return result;
}

std::vector<experience> csv::experience_vector;
std::vector<moves> csv::moves_vector;
std::vector<pokemon_struct> csv::pokemon_vector;
std::vector<pokemon_moves_struct> csv::pokemon_moves_vector;
std::vector<pokemon_species> csv::pokemon_species_vector;
std::vector<pokemon_stats> csv::pokemon_stats_vector;
std::vector<pokemon_types> csv::pokemon_types_vector;
std::vector<stats> csv::stats_vector;
std::vector<type_names> csv::type_names_vector;
std::vector<types> csv::types_vector;
std::vector<move_names> csv::move_names_vector;

std::future<void> pokemon_moves_future;
std::future<void> experience_future;
std::future<void> moves_future;
std::future<void> move_names_future;
std::future<void> pokemon_future;
std::future<void> pokemon_species_future;
std::future<void> pokemon_stats_future;
std::future<void> pokemon_types_future;
std::future<void> stats_future;
std::future<void> type_names_future;
std::future<void> types_future;

int csv::stoi(const string &s)
{
    if (s.empty())
        return INT_MAX;
    return std::stoi(s);
}

string parse(int i)
{
    if (i == INT_MAX)
        return "";
    return to_string(i);
}

string parse(const string &s)
{
    return s;
}

ifstream getFile(const char *filename)
{
    string path = "/share/cs327/pokedex/pokedex/data/csv/";
    ifstream file(path + filename);
    if (!file.is_open())
    {
        path = string(getenv("HOME")) + "/.poke327/pokedex/pokedex/data/csv/";
        file.open(path + filename);
    }
    if (!file.is_open())
    {
        cout << "Could not find file " << filename << "... exiting\n";
        abort();
    }
    return file;
}

void csv::load_experience()
{
    ifstream file = getFile("experience.csv");
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        experience data;
        auto match = split(line);
        if (match.empty())
            break;
        data.growth_rate_id = stoi(match[1]);
        data.level = stoi(match[2]);
        data.experience = stoi(match[3]);
        experience_vector.push_back(data);
    }
    file.close();
    experience_vector.shrink_to_fit();
#ifdef DEBUG
    cout << "growth_rate_id,level,experience\n";
    for (const auto &data: experience_vector)
        cout << parse(data.growth_rate_id) << ',' << parse(data.level) << ',' << parse(data.experience) << '\n';
#endif
}

void csv::load_moves()
{
    ifstream file = getFile("moves.csv");
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        moves data;
        auto match = split(line);
        if (match.empty())
            break;
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
    file.close();
    moves_vector.shrink_to_fit();
#ifdef DEBUG
    cout
            << "id,identifier,generation_id,type_id,power,pp,accuracy,priority,target_id,damage_class_id,effect_id,effect_chance,contest_type_id,contest_effect_id,super_contest_effect_id\n";
    for (const auto &data: moves_vector)
        cout << parse(data.id) << ',' << parse(data.identifier) << ',' << parse(data.generation_id) << ','
             << parse(data.type_id) << ',' << parse(data.power) << ',' << parse(data.pp) << ',' << parse(data.accuracy)
             << ',' << parse(data.priority) << ',' << parse(data.target_id) << ',' << parse(data.damage_class_id) << ','
             << parse(data.effect_id) << ',' << parse(data.effect_chance) << ',' << parse(data.contest_type_id) << ','
             << parse(data.contest_effect_id) << ',' << parse(data.super_contest_effect_id) << '\n';
#endif
}

void csv::load_pokemon()
{
    ifstream file = getFile("pokemon.csv");
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        pokemon_struct data;
        auto match = split(line);
        if (match.empty())
            break;
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
    file.close();
    pokemon_vector.shrink_to_fit();
#ifdef DEBUG
    cout << "id,identifier,species_id,height,weight,base_experience,order,is_default\n";
    for (const auto &data: pokemon_vector)
        cout << parse(data.id) << ',' << parse(data.identifier) << ',' << parse(data.species_id) << ','
             << parse(data.height) << ',' << parse(data.weight) << ',' << parse(data.base_experience) << ','
             << parse(data.order) << ',' << parse(data.is_default) << '\n';
#endif
}

void csv::load_pokemon_moves()
{
    ifstream file = getFile("pokemon_moves.csv");
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        pokemon_moves_struct data;
        auto match = split(line);
        if (match.empty())
            break;
        data.pokemon_id = stoi(match[1]);
        data.version_group_id = stoi(match[2]);
        data.move_id = stoi(match[3]);
        data.pokemon_move_method_id = stoi(match[4]);
        data.level = stoi(match[5]);
        data.order = stoi(match[6]);
        pokemon_moves_vector.push_back(data);
    }
    file.close();
    pokemon_moves_vector.shrink_to_fit();
#ifdef DEBUG
    cout << "pokemon_id,version_group_id,move_id,pokemon_move_method_id,level,order\n";
    for (const auto &data: pokemon_moves_vector)
        cout << parse(data.pokemon_id) << ',' << parse(data.version_group_id) << ',' << parse(data.move_id) << ','
             << parse(data.pokemon_move_method_id) << ',' << parse(data.level) << ',' << parse(data.order) << '\n';
#endif
}

void csv::load_pokemon_species()
{
    ifstream file = getFile("pokemon_species.csv");
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        struct pokemon_species data;
        auto match = split(line);
        if (match.empty())
            break;
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
    file.close();
    pokemon_species_vector.shrink_to_fit();
#ifdef DEBUG
    cout
            << "id,identifier,generation_id,evolves_from_species_id,evolution_chain_id,color_id,shape_id,habitat_id,gender_rate,capture_rate,base_happiness,is_baby,hatch_counter,has_gender_differences,growth_rate_id,forms_switchable,is_legendary,is_mythical,order,conquest_order\n";
    for (const auto &data: pokemon_species_vector)
        cout << parse(data.id) << ',' << parse(data.identifier) << ',' << parse(data.generation_id) << ','
             << parse(data.evolves_from_species_id) << ',' << parse(data.evolution_chain_id) << ','
             << parse(data.color_id) << ',' << parse(data.shape_id) << ',' << parse(parse(data.habitat_id)) << ','
             << parse(data.gender_rate) << ',' << parse(data.capture_rate) << ',' << parse(data.base_happiness) << ','
             << parse(data.is_baby) << ',' << parse(data.hatch_counter) << ',' << parse(data.has_gender_differences)
             << ',' << parse(data.growth_rate_id) << ',' << parse(data.forms_switchable) << ','
             << parse(data.is_legendary) << ',' << parse(data.is_mythical) << ',' << parse(data.order) << ','
             << parse(data.conquest_order) << '\n';
#endif
}

void csv::load_pokemon_stats()
{
    ifstream file = getFile("pokemon_stats.csv");
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        pokemon_stats data;
        auto match = split(line);
        if (match.empty())
            break;
        data.pokemon_id = stoi(match[1]);
        data.stat_id = stoi(match[2]);
        data.base_stat = stoi(match[3]);
        data.effort = stoi(match[4]);
        pokemon_stats_vector.push_back(data);
    }
    file.close();
    pokemon_stats_vector.shrink_to_fit();
#ifdef DEBUG
    cout << "pokemon_id,stat_id,base_stat,effort\n";
    for (const auto &data: pokemon_stats_vector)
        cout << parse(data.pokemon_id) << ',' << parse(data.stat_id) << ',' << parse(data.base_stat) << ','
             << parse(data.effort) << '\n';
#endif
}

void csv::load_pokemon_types()
{
    ifstream file = getFile("pokemon_types.csv");
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        pokemon_types data;
        auto match = split(line);
        if (match.empty())
            break;
        data.pokemon_id = stoi(match[1]);
        data.type_id = stoi(match[2]);
        data.slot = stoi(match[3]);
        pokemon_types_vector.push_back(data);
    }
    file.close();
    pokemon_types_vector.shrink_to_fit();
#ifdef DEBUG
    cout << "pokemon_id,type_id,slot\n";
    for (const auto &data: pokemon_types_vector)
        cout << parse(data.pokemon_id) << ',' << parse(data.type_id) << ',' << parse(data.slot) << '\n';
#endif
}

void csv::load_stats()
{
    ifstream file = getFile("stats.csv");
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        stats data;
        auto match = split(line);
        if (match.empty())
            break;
        data.id = stoi(match[1]);
        data.damage_class_id = stoi(match[2]);
        data.identifier = match[3];
        data.is_battle_only = stoi(match[4]);
        data.game_index = stoi(match[5]);
        stats_vector.push_back(data);
    }
    file.close();
    stats_vector.shrink_to_fit();
#ifdef DEBUG
    cout << "id,damage_class_id,identifier,is_battle_only,game_index\n";
    for (const auto &data: stats_vector)
        cout << parse(data.id) << ',' << parse(data.damage_class_id) << ',' << parse(data.identifier) << ','
             << parse(data.is_battle_only) << ',' << parse(data.game_index) << '\n';
#endif
}

void csv::load_types()
{
    ifstream file = getFile("types.csv");
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        types data;
        auto match = split(line);
        if (match.empty())
            break;
        data.id = stoi(match[1]);
        data.identifier = match[2];
        data.generation_id = stoi(match[3]);
        data.damage_class_id = stoi(match[4]);
        types_vector.push_back(data);
    }
    file.close();
    types_vector.shrink_to_fit();
#ifdef DEBUG
    cout << "id,identifier,generation_id,damage_class_id\n";
    for (const auto &data: stats_vector)
        cout << parse(data.id) << ',' << parse(data.damage_class_id) << ',' << parse(data.identifier) << ','
             << parse(data.is_battle_only) << ',' << parse(data.game_index) << '\n';
#endif
}

void csv::load_type_names()
{
    ifstream file = getFile("type_names.csv");
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        type_names data;
        auto match = split(line);
        if (match.empty())
            break;
        data.type_id = stoi(match[1]);
        data.local_language_id = stoi(match[2]);
        data.name = match[3];
        type_names_vector.push_back(data);
    }
    file.close();
    type_names_vector.shrink_to_fit();
#ifdef DEBUG
    cout << "type_id,local_language_id,name\n";
    for (const auto &data: type_names_vector)
        cout << parse(data.type_id) << ',' << parse(data.local_language_id) << ',' << parse(data.name) << '\n';
#endif
}

void csv::load()
{
#ifdef DEBUG
    csv::load_pokemon_moves();
    exit(0);
//    csv::load_pokemon();
//    csv::load_experience();
//    csv::load_moves();
//    csv::load_move_names();
//    csv::load_pokemon_species();
//    csv::load_pokemon_stats();
//    csv::load_pokemon_types();
//    csv::load_stats();
//    csv::load_type_names();
//    csv::load_types();
#else
    auto policy = launch::deferred;
    pokemon_moves_future = async(launch::async, &csv::load_pokemon_moves);
    pokemon_future = async(launch::async, &csv::load_pokemon);
    experience_future = async(policy, &csv::load_experience);
    moves_future = async(policy, &csv::load_moves);
    move_names_future = async(policy, &csv::load_move_names);
    pokemon_species_future = async(policy, &csv::load_pokemon_species);
    pokemon_stats_future = async(policy, &csv::load_pokemon_stats);
    pokemon_types_future = async(policy, &csv::load_pokemon_types);
    stats_future = async(policy, &csv::load_stats);
    type_names_future = async(policy, &csv::load_type_names);
    types_future = async(policy, &csv::load_types);
#endif
}

vector<pokemon_moves> csv::get_pokemon_moves(pokemon *pokemon)
{
    pokemon_moves_future.wait();
    vector<pokemon_moves> output;
    int id = pokemon->species_id;
    int level = pokemon->level;
    vector<pokemon_moves_struct> vector;
    auto first = lower_bound(pokemon_moves_vector.begin(), pokemon_moves_vector.end(), id,
                             [](const auto &a, const auto b)
                             { return a.pokemon_id < b; });
    id = first->pokemon_id;
    auto last = upper_bound(pokemon_moves_vector.begin(), pokemon_moves_vector.end(), id,
                            [](const auto a, const auto &b)
                            { return a < b.pokemon_id; });
    while (vector.size() == 0)
    {
        copy_if(first, last, back_inserter(vector), [&level](const auto &a)
        { return a.pokemon_move_method_id == 1 && a.level <= level; });
        pokemon->levelUp();
        level = pokemon->level;
    }
    random_device rd;
    default_random_engine engine(rd());
    uniform_int_distribution<> distribution(0, vector.size() - 1);
    int index = distribution(engine);
    output.emplace_back(vector[index]);
    if (vector.size() == 1)
        return output;
    int index2 = index;
    while (index2 == index)
        index2 = distribution(engine);
    output.emplace_back(vector[index2]);
    return output;
}

__gnu_cxx::__normal_iterator<pokemon_stats *, vector<pokemon_stats>> csv::get_pokemon_stats(int id)
{
    pokemon_stats_future.wait();
    return lower_bound(pokemon_stats_vector.begin(), pokemon_stats_vector.end(), id, [](const auto &a, const auto b)
    { return a.pokemon_id < b; });
}

std::string get_move_names(int id)
{
    move_names_future.wait();
    auto start = lower_bound(csv::move_names_vector.begin(), csv::move_names_vector.end(), id,
                             [](const auto &a, const auto b)
                             { return a.move_id < b; });
    while (start->local_language_id != 9) start++;
    return start->name;
}

pokemon_struct csv::get_pokemon()
{
    pokemon_future.wait();
    random_device rd;
    default_random_engine engine(rd());
    uniform_int_distribution<> distribution(0, pokemon_vector.size() - 1);
    return pokemon_vector[distribution(engine)];
}

void csv::load_move_names()
{
    ifstream file = getFile("move_names.csv");
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        move_names data;
        auto match = split(line);
        if (match.empty())
            break;
        data.move_id = stoi(match[1]);
        data.local_language_id = stoi(match[2]);
        data.name = match[3];
        move_names_vector.push_back(data);
    }
    file.close();
    move_names_vector.shrink_to_fit();
#ifdef DEBUG
    cout << "move_id,local_language_id,name\n";
    for (const auto &data: move_names_vector)
        cout << parse(data.move_id) << ',' << parse(data.local_language_id) << ',' << parse(data.name) << '\n';
#endif
}

