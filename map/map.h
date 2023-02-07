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
#define PC '@'

struct p {
    int y;
    int x;
};

struct cell {
    char c;
    struct p p;
};

struct map {
    struct cell cells[MAP_HEIGHT][MAP_WIDTH];
    struct cell exits[4];
    int seed;
    struct grid *g;
    struct p p;
};

void displayToPrintf(struct map *m);
void generate(struct map *m);
void display(struct map *m);

#endif //CS327_MAP_H
