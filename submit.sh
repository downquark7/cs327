#!/usr/bin/sh
git --no-pager log > changelog
make clean
tar -czvf nicely-evan-cs327-01.tar.gz makefile changelog main.c map/*
