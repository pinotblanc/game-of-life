 #include <stdio.h>
 #include <stdlib.h>
 #include<unistd.h>

void initialize(int **board, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
           board[i][j] = rand() % 2;
        }
    }
}

void paint(int **board, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf((board[i][j]) ? "O " : "* ");
        }
        printf("\n");
    }
    printf("\n");
    printf("\n");
    printf("\n");
}

int getNeighbors(int **board, int i, int j, int n)
{
    int neighbors = 0;

    for (int x = -1; x < 2; x++)
    {
        for (int y = -1; y < 2; y++)
        {
            if (i + x >= 0 && i + x < n && j + y >= 0 && j + y < n)
                neighbors += board[i+x][j+y];
        }
    }
    neighbors -= board[i][j];
    return neighbors;
}

void nextGen(int **board, int n)
{
    int **next = (int **)malloc(n*sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        next[i] = (int *)malloc(n*sizeof(int));
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int neighbors = getNeighbors(board, i, j, n);

            if (board[i][j] == 1)
            {
                if (neighbors < 2 || neighbors > 3)
                    next[i][j] = 0;
                else
                    next[i][j] = 1;
            }
            else
            {
                if (neighbors == 3)
                    next[i][j] = 1;
                else
                    next[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            board[i][j] = next[i][j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        free(next[i]);
    }
    free(next);
}

int main(int argc, char const *argv[])
{
    // make board
    int n = 7;
    int gens = 10000;
    int **board = (int **)malloc(n*sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        board[i] = (int *)malloc(n*sizeof(int *));
    }
    
    initialize(board, n);
    paint(board, n);

    for (int i = 0; i < gens; i++)
    {
        nextGen(board, n);
        paint(board, n);
        sleep(1);
    }

    for (int i = 0; i < n; i++)
    {
        free(board[i]);
    }
    free(board);

    return 0;
}