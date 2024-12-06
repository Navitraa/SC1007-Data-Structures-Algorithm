#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


//write your code here
/* Symbols used are: 
1. n = number of items
2. C = capacity of knapsack
3. s = size of item
4. v = value of item
5. i = ith item
6. j = jth capacity
*/

int bottom_up_dp(int n, int *s, int *v, int C)
{
    // Step 1: Allocate memory for the DP table 
    int **M = (int**) malloc(sizeof(int*) * (n+1));
    for (int i = 0; i <= n; i++) { // iterates thru each row 
        M[i] = (int*) malloc(sizeof(int) * (C+1));
    }

    // Step 2: Initialise DP table values
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= C; j++) {
            // Base case: if no items or capacity, then 0 value
            if (i == 0 || j == 0) {
                M[i][j] = 0;
            }
            // Consider whether to include the item
            else if (s[i] <= j) { // IMPT LOGIC PORTION
                if (M[i-1][j] > M[i-1][j-s[i]] + v[i]) {
                    M[i][j] = M[i-1][j];
                }
                else {
                    M[i][j] = M[i-1][j-s[i]] + v[i];
                }
            }
            // Cannot include the item
            else {
                M[i][j] = M[i-1][j];
            }
        }
    }

    // Step 3: Return maximum value, present at M[n][C]
    return M[n][C];

    // Step 4: Free memory
    for (int i = 0; i <= n; i++) {
        free(M[i]);
    }
    free(M);
}

 
int main ()
{
    int n,C;
    int function;
    int *s;
    int *v;
    int i,j;
    printf("Enter the number of items n:\n");
    scanf("%d",&n);
    printf("Enter the capacity C:\n");
    scanf("%d",&C);
    s = (int *) malloc(sizeof(int) * (n+1));
    v = (int *) malloc(sizeof(int) * (n+1));
    
    printf("Enter the sizes of items (as a list, separate by spacing:\n");
    for (i=1;i<=n;i++)
        scanf("%d",&s[i]);
        
    printf("Enter the values of items (as a list, separate by spacing:\n");
    for (i=1;i<=n;i++)
        scanf("%d",&v[i]);
    
    printf("The maximum value is: %d \n", bottom_up_dp(n,s,v,C));
        
}