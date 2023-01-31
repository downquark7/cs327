//
// Created by downq on 1/30/2023.
//

#ifndef MAPDATA_H
#define MAPDATA_H

#define mapwidth 80
#define mapheight 24

struct cell {
    char c;
//    void (*update)(struct cell *);
//    int (*can_player_cross)(struct cell *);
};

struct map {
    struct cell cells[mapheight][mapwidth];
    void (*generate)(struct map *);
    void (*display)(struct map *);
};

void setMapFunctions(struct map *m);
void displayToPrintf(struct map *m);
void generateV0(struct map *m);
#endif //MAPDATA_H
