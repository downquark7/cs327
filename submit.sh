#!/usr/bin/sh
git --no-pager log > CHANGELOG
make clean
rm -rf nicely_evan.assignment-1.02/
mkdir nicely_evan.assignment-1.02
cp Makefile nicely_evan.assignment-1.02/
cp README nicely_evan.assignment-1.02/
cp CHANGELOG nicely_evan.assignment-1.02/
cp main.c nicely_evan.assignment-1.02/
cp -r map/ nicely_evan.assignment-1.02/map/
tar -czvf nicely_evan.assignment-1.02.tar.gz nicely_evan.assignment-1.02