#include <stdio.h>

#define width 5
#define height 5

/***
 * @param bit (0-(length-1))th bit of number
 * @param num number representing a board state or list of positions to get bit from
 * @return 1 or 0
 */
long long int getBit(int bit, long long int num)
{
    return (num >> bit) & 1;
}

long long int flipBit(int bit, long long int num)
{
    return num ^ (1 << bit);
}

const long long int fullBoard = ( 1LL << (width * height + 1)) - 2;

int isBoardFull(long long int board)
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

int recursive(long long int board, int last);

int recursive(long long int board, int last)
{
    board = flipBit(last, board);
    if (isBoardFull(board))
        return 1;
    int sum = 0, i;
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
                    sum += recursive(board, next);
    }
    return sum;
}

int main()
{
    int i, sum = 0;

    for (i = 1; i <= width * height; i++)
        sum += recursive(0, i);

    printf("%d\n", sum);
    return 0;
}
