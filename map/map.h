//
// Created by downq on 1/30/2023.
//

#ifndef CS327_MAP_H
#define CS327_MAP_H

#define MAP_WIDTH 80
#define MAP_HEIGHT 21
#define ROCK '%'
#define TREE '^'
#define ROAD '#'
#define TALL_GRASS ':'
#define SHORT_GRASS '.'
#define WATER '~'

struct p {
    int y;
    int x;
};

struct cell {
    char c;
    struct p p;
};

struct map {
    char cells[MAP_HEIGHT][MAP_WIDTH + 1];
    char swimmerCells[MAP_HEIGHT][MAP_WIDTH + 1];
    struct cell exits[4];
    struct p p;
    int seed;
    struct grid *g;
    struct entity *e;
    int eCount;
};

void generate(struct map *m);

void display(struct map *m);


#endif //CS327_MAP_H
