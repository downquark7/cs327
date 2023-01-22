#include <stdio.h>
#include <stdlib.h>

#define customint int

int width = 5;
int height = 5;

/***
 * @param bit (0-(length-1))th bit of number
 * @param num number representing a board state or list of positions to get bit from
 * @return 1 or 0
 */
customint getBit(int bit, customint num)
{
    return (num >> bit) & 1;
}

customint flipBit(int bit, customint num)
{
    return num ^ (1 << bit);
}

customint fullBoard;

int isBoardFull(customint board)
{
    return board == fullBoard;
}

int xyToBoard(int x, int y)
{
    return 1 + x + width * y;
}

int getX(int num)
{
    return (num - 1) % width;
}

int getY(int num)
{
    return (num - 1) / width;
}

int recursive(customint board, int last, int *prevhist, int length)
{
    int i;
    int *hist;
    hist = malloc(4 * length + 4);
    for (i = 0; i < length; i++)
        hist[i] = prevhist[i];
    hist[length] = last;
    board = flipBit(last, board);
    if (isBoardFull(board))
    {
        for (i = 0; i < length; i++)
            printf("%d, ", hist[i]);
        i++;
        printf("%d\n", hist[i]);
        return 1;
    }
    length++;
    int sum = 0;
    int xOffsets[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int yOffsets[] = {-1, 1, 2, -2, 2, -2, 1, -1};
    for (i = 0; i < 8; i++)
    {
        int nextX = getX(last) + xOffsets[i];
        int nextY = getY(last) + yOffsets[i];
        int next = xyToBoard(nextX, nextY);
        if (nextX >= 0 && nextX < width)
            if (nextY >= 0 && nextY < height)
                if (!getBit(next, board))
                    sum += recursive(board, next, hist, length);
    }
    free(hist);
    return sum;
}

int main(int argc, char *argv[])
{
    fullBoard = ((customint) 1 << (width * height + 1)) - 2;
    int i, sum = 0;

    for (i = 1; i <= width * height; i++)
        sum += recursive(0, i, 0, 0);

    printf("%d\n", sum);
    return 0;
}
