#include <stdio.h>

#define width 5
#define height 5

/***
 * @param bit (0-(length-1))th bit of number
 * @param num number representing a board state or list of positions to get bit from
 * @return 1 or 0
 */
int getBit(int bit, int num)
{
    return (num >> bit) & 1;
}

int flipBit(int bit, int num)
{
    return num ^ (1 << bit);
}

const int fullBoard = (1 << (width * height)) - 1;

int isBoardFull(int board)
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

//need to save pathways later but not now cuz they take up so much time and space
int recursive(int board, int last)
{
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
                if (!getBit(board, next))
                {
                    int newBoard = flipBit(board, next);
                    sum += recursive(newBoard, next);
                }
    }
    return sum;
}

int main()
{
    int i = 1, sum = 0;

    for (i = 0; i < width * height; i++)
        sum += recursive(0, i);

    printf("%d\n", sum);
    return 0;
}
