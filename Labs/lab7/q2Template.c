#include <stdio.h>
#include <stdlib.h>

int nQueens(int** board, int N, int col);
int isSafe(int** board,int N, int row, int col);
void printSolution(int** board, int N);

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

    if (!nQueens(board, BSize, 0))
    	printf("Solution does not exist");

    return 0;
}

// write your code here; DEBUGGED: forgot to include printSolution but that's about it.
// such that int** board = the dynamically-allocated 2D array, int n = board size, int col = column index i.e. current column being solved for in the recursive function
int nQueens(int** board, int BSize, int col)
{
     // Base case: if all queens have been placed, return 1
    if (col == BSize) { 
        printSolution(board, BSize);
        return 1;
    }

     // Recursive case: consider the column col and try placing the queen at different rows on that column
    for (int r = 0; r < BSize; r++) {
        printf("We are now evaluating row %d column %d \n", r, col);
        // check if that board[col][row] position is safe
        if (isSafe(board, BSize, r, col)) {
            // assign queen, then move on to the next column
            printf("This square is safe. \n");
            board[r][col] = 1;
            if (nQueens(board, BSize, col + 1) == 1) {
                return 1; // if recursion returns true, the solution is found
            }
            // BACKTRACK: if solution is not found
            board[r][col] = 0;
        }
    }

    // Invalid case: NQueens cannot be assigned to a board of size BSize
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
