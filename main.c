#include <stdio.h>

#define width 5
#define height 5

/***
 * @param bit 0-(length-1) bit of number
 * @param num number representing a board state or list of positions to get bit from
 * @return 1 or 0
 */
int getBit(int bit, int num) {
    return (num >> bit) & 1;
}

int flipBit(int bit, int num) {
    return num ^ (1 << bit);
}

int fullBoard = (1 << (width * height)) - 1;

int isBoardFull(int board) {
    return board == fullBoard;
}

int main() {
    printf("%d", 2147483647);
    return 0;
}
