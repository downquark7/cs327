#!/usr/bin/sh
rm -rf nicely_evan.assignment-1.03/
mkdir nicely_evan.assignment-1.03
cp -rfv * nicely_evan.assignment-1.03/
cd nicely_evan.assignment-1.03/
git --no-pager log >CHANGELOG
cmake CMakeLists.txt
rm -rfv cmake-build-debug/
rm -rfv knightsTour/
rm -rfv Testing/
rm -rfv .*
rm -rfv
rm -rfv *.tar.gz
make
./main
make clean
cd ..
tar -czvf nicely_evan.assignment-1.03.tar.gz nicely_evan.assignment-1.03
