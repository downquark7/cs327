//
// Created by downq on 1/30/2023.
//

#ifndef CS327_MAP_H
#define CS327_MAP_H

#define MAP_WIDTH 80
#define MAP_HEIGHT 24

struct cell {
    char c;
//    void (*update)(struct cell *);
//    int (*can_player_cross)(struct cell *);
};

struct map {
    struct cell cells[MAP_HEIGHT][MAP_WIDTH];
    void (*generate)(struct map *);
    void (*display)(struct map *);
};

void setMapFunctions(struct map *m);
void displayToPrintf(struct map *m);
void generateV0(struct map *m);
#endif //CS327_MAP_H
