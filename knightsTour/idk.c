//
// kinda stolen code don't give me credit https://github.com/nadeemhussain/UVA/blob/master/knight%27s%20tour%20problem.cpp
//
#include <stdio.h>

const int N = 8;

int xMove[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int yMove[8] = {1, 2, 2, 1, -1, -2, -2, -1};

int isSafe(int x, int y)
{
    return (x >= 0 && x < N && y >= 0 && y < N);
}

int countReachable(int x, int y, int sol[N][N])
{
    int count = 0;
    for (int i = 0; i < 8; i++)
    {
        int next_x = x + xMove[i];
        int next_y = y + yMove[i];
        if (isSafe(next_x, next_y) && sol[next_x][next_y] == -1)
            count++;
    }
    return count;
}

void printSolution(int sol[N][N])
{
    for (int x = 0; x < N; x++)
    {
        for (int y = 0; y < N; y++)
            printf("%2d ", sol[x][y]);
        printf("\n");
    }
}

int solveKTUtil(int x, int y, int movei, int sol[N][N], int xMove[N], int yMove[N])
{
    int k, next_x, next_y;
    if (movei == N * N)
        return 1;

    int min_reachable = 8;
    int min_x, min_y;
    for (k = 0; k < 8; k++)
    {
        next_x = x + xMove[k];
        next_y = y + yMove[k];
        if (isSafe(next_x, next_y) && sol[next_x][next_y] == -1)
        {
            int reachable = countReachable(next_x, next_y, sol);
            if (reachable < min_reachable)
            {
                min_reachable = reachable;
                min_x = next_x;
                min_y = next_y;
            }
        }
    }

    if (min_reachable == 8)
        return 0;

    sol[min_x][min_y] = movei;
    if (solveKTUtil(min_x, min_y, movei + 1, sol, xMove, yMove))
        return 1;
}

int solveKT()
{
    int sol[N][N];

    /* Initialization of solution matrix */
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++)
            sol[x][y] = -1;

    // Since the Knight is initially at the first block
    sol[0][0]  = 0;

    /* Start from 0,0 and explore all tours using solveKTUtil() */
    if(solveKTUtil(0, 0, 1, sol, xMove, yMove) == 0)
    {
        printf("Solution does not exist");
        return 0;
    }
    else
        printSolution(sol);

    return 1;
}

int main()
{
    solveKT();
}
