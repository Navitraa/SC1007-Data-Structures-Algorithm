#include <stdio.h>
#include <stdlib.h>

int nQueensAll(int** board, int N, int col);
int isSafe(int** board,int N, int row, int col);
void printSolution(int** board, int N);
int count = 0;

int main()
{
    int **board;
    int BSize;

    int i,j;

    printf("Enter the size of chessBoard:\n");
    scanf("%d",&BSize);

    board = (int **)malloc(BSize*sizeof(int *));
    for(i=0;i<BSize;i++)
        board[i] = (int *)malloc(BSize*sizeof(int));

    for(i=0;i<BSize;i++)
       for(j=0;j<BSize;j++)
           board[i][j] = 0;

    nQueensAll(board, BSize, 0);
    if (count == 0)
    	printf("Solution does not exist");
    else
    	printf("There are total %d solutions",count);

    return 0;
}

// write your code here; DEBUGGED: use the global variable 'count' instead of initialisating a local variable 'solutions' within the nQeensAll function bc it will reset every time the function is called recursively
int nQueensAll(int** board, int BSize, int col)
{
    // Base Case
    if (col == BSize) {
        count++;
        printSolution(board, BSize);
        return 1;
    }

    // Recursive Case
    for (int row = 0; row < BSize; row++) {
        if (isSafe(board, BSize, row, col)) {
            board[row][col] = 1;
            nQueensAll(board, BSize, col+1);
            board[row][col] = 0; // backtrack
        }
    }

    // Invalid Case
    return 0;

}

//Safe checking
int isSafe(int** board,int BSize, int row, int col)
{
    int i, j;

    // Horicatal check
    for (i = 0; i < col; i++)
        if (board[row][i])
            return 0;

    // Upper left diagonal check
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return 0;

    // Lower left diagonal check
    for (i = row, j = col; j >= 0 && i < BSize; i++, j--)
        if (board[i][j])
            return 0;

    return 1;
}

void printSolution(int** board, int BSize)
{
    int i,j;
    for (i = 0; i < BSize; i++) {
        for (j = 0; j < BSize; j++){
            if(board[i][j]==1)
                printf(" Q ");
            else
                printf(" + ");
        }
        printf("\n");
    }
    printf("\n");
}
