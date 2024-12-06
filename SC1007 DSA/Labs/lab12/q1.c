#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *M; // this is an array

//write your code here
int fib_recursive(int n)
{
    // Base case
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    // Recursive case
    return fib_recursive(n-1) + fib_recursive(n-2);
}

//write your code here
int top_down_dp(int n)
{
    // Base cases: Basic cases must be hard coded i.e. when n=0 and n=1
    if (n == 0) {
        M[0] = 0;
        return 0;
    }
    if (n == 1) {
        M[1] = 1;
        return 1;
    }

    // Only if M[n-1] and M[n-2] have NOT been calculated yet, THEN calculate it
    if (M[n-1] == -1) {
        M[n-1] = top_down_dp(n-1);
    }
    if (M[n-2] == -1) {
        M[n-2] = top_down_dp(n-2);
    }

    // Calculate M[n]
    M[n] = M[n-1] + M[n-2];
    return M[n];
}

//write your code here
int bottom_up_dp(int n)
{
    M[0] = 0;
    M[1] = 1;

    for (int i = 2; i <= n; i++) { // NOTE: start from i=2 NOT i=0
        M[i] = M[i-1] + M[i-2]; // DEBUG: typo of 1 instead of i
    }
    return M[n];
}
 
void main ()
{
    int n;
    int function;
    int i;
    printf("Enter the value of n:\n");
    scanf("%d",&n);
    
    //allocate the memory array
    M = malloc(sizeof(int) * (n+1)); // ohh u only need to malloc once for the entire array
    
    printf("Choose a function (1 for recursive, 2 for top-down DP, 3 for bottom-up DP, 0 to stop): \n");
    scanf("%d",&function);
    while (function != 0)
    {
        if (function == 1)
        {
            clock_t begin = clock();
            printf("The result of Fib(%d) is: %d \n", n, fib_recursive(n));
            clock_t end = clock();
            double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            printf("Running time is: %f seconds \n", time_spent);
        }
        else if (function == 2)
        {
            //set all memory elements to -1
            for (i=0; i<=n; i++)
                M[i] = -1; 
                
            clock_t begin = clock();
            printf("The result of Fib(%d) is: %d \n", n, top_down_dp(n));
            clock_t end = clock();
            double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            printf("Running time is: %f seconds \n", time_spent);
        }
        else if (function == 3)
        {
            //set all memory elements to -1
            for (i=0; i<=n; i++)
                M[i] = -1;
                
            clock_t begin = clock();
            printf("The result of Fib(%d) is: %d \n", n, bottom_up_dp(n));
            clock_t end = clock();
            double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            printf("Running time is: %f seconds \n", time_spent);
        }
        printf("Choose a function (1 for recursive, 2 for top-down DP, 3 for bottom-up DP, 0 to stop): \n");
        scanf("%d",&function);
    }
}