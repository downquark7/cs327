#!/bin/bash

for arg in experience moves pokemon pokemon_moves pokemon_species pokemon_stats pokemon_types stats type_names; do
    echo "Running main with argument: $arg"
    ./main $arg > $arg.txt

    echo "Comparing output to original CSV: $arg.csv"
    diff $arg.txt /share/pokedex/pokedex/data/csv/$arg.csv
done
