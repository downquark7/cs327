//
// Created by downq on 1/30/2023.
//

#ifndef CS327_MAP_H
#define CS327_MAP_H

#define MAP_WIDTH 80
#define MAP_HEIGHT 24
#define ROCK '%'
#define TREE '^'
#define ROAD '#'
#define TALL_GRASS ':'
#define SHORT_GRASS '.'
#define WATER '~'
#define PC '@'

struct p {
    int x;
    int y;
};

struct cell {
    char c;
    struct p p;
//    void (*update)(struct cell *);
//    int (*can_player_cross)(struct cell *);
};

struct map {
    struct cell cells[MAP_HEIGHT][MAP_WIDTH];
    struct cell exits[4];
    void (*generate)(struct map *);
    void (*display)(struct map *);
};

void setMapFunctions(struct map *m);
void displayToPrintf(struct map *m);
void generateV0(struct map *m);
#endif //CS327_MAP_H
