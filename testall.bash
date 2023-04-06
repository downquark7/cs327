#!/bin/bash

# Run main for each CSV file in parallel using GNU Parallel
echo "Running main for all CSV files..."
ls data/csv/*.csv | parallel -j0 "echo Running main for {}; ./main {} > output/{}.out"

# Compare output files to original CSV files
echo "Comparing output files to original CSV files..."
for csv_file in data/csv/*.csv; do
    filename=$(basename $csv_file)
    diff $csv_file output/$filename.out
done
