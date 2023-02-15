#!/usr/bin/sh
rm -rf nicely_evan.assignment-1.03/
git --no-pager log >CHANGELOG
make clean
mkdir nicely_evan.assignment-1.03
cmake CMakeLists.txt
cp -rfv * nicely_evan.assignment-1.03/
rm -rfv nicely_evan.assignment-1.03/cmake-build-debug/
rm -rfv nicely_evan.assignment-1.03/knightsTour/
rm -rfv nicely_evan.assignment-1.03/Testing/
rm -rfv nicely_evan.assignment-1.03/.*
rm -rfv nicely_evan.assignment-1.03/nicely_evan.assignment-1.03/
rm -rfv nicely_evan.assignment-1.03/*.tar.gz
cd nicely_evan.assignment-1.03
make
./main
make clean
cd ..
tar -czvf nicely_evan.assignment-1.03.tar.gz nicely_evan.assignment-1.03
