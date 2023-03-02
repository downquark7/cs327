#!/usr/bin/sh
rm -rf nicely_evan.assignment-1.04/
rm -rf nicely_evan.assignment-1.04.tar.gz
rm -rf /tmp/nicely_evan.assignment-1.04/
mkdir nicely_evan.assignment-1.04
cp -rfv * nicely_evan.assignment-1.04/
cd nicely_evan.assignment-1.04/
git --no-pager log > CHANGELOG
rm -rfv cmake-build-debug/
rm -rfv knightsTour/
rm -rfv Testing/
rm -rfv .*
rm -rfv *.tar.gz
make clean
cd ..
tar -czvf nicely_evan.assignment-1.04.tar.gz nicely_evan.assignment-1.04
tar -xzf nicely_evan.assignment-1.04.tar.gz -C /tmp
cd /tmp/nicely_evan.assignment-1.04
make
./main