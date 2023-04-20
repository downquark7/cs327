#!/usr/bin/sh
SUBMIT_FILENAME="nicely_evan.assignment-1.09"
rm -rf $SUBMIT_FILENAME
rm -rf $SUBMIT_FILENAME.tar.gz
rm -rf /tmp/$SUBMIT_FILENAME/
mkdir $SUBMIT_FILENAME
cp -rfv ./* $SUBMIT_FILENAME/
cd $SUBMIT_FILENAME/ || exit
git --no-pager log > CHANGELOG
rm -rfv cmake-build-debug/
rm -rfv $SUBMIT_FILENAME
rm -rfv Testing/
rm -rfv .*
rm -rfv *.csv
rm -rfv *.txt
rm -rfv ./*.tar.gz
make clean
cd ..
tar -czvf $SUBMIT_FILENAME.tar.gz $SUBMIT_FILENAME
tar -xzf $SUBMIT_FILENAME.tar.gz -C /tmp
cd /tmp/$SUBMIT_FILENAME || exit
make run
