#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int *F;

//write your code here
int top_down_dp(int n)
{
    // Base cases
    if (n == 0) {
        F[0] = 0;
        return 0;
    }
    if (n == 1) {
        F[1] = 1;
        return 1;
    }
    if (n == 2) {
        F[2] = 2;
        return 2;
    }

    // Check if the value is already present in the memory, else calculate
    // NOTE: look thru test cases and set initialised value accordingly
    if (F[n-1] == -1) {
        F[n-1] = top_down_dp(n-1);
    }
    if (F[n-2] == -1) {
        F[n-2] = top_down_dp(n-2);
    }
    if (F[n-3] == -1) {
        F[n-3] = top_down_dp(n-3);
    }

    // Calculate F[n] 
    F[n] = F[n-1] + 2*F[n-2] - 3*F[n-3];
    return F[n];
}


int main ()
{
    int n;
    int function;
    int i;
    printf("Enter the value of n:\n");
    scanf("%d",&n);

    // create and initialise memory DYNAMICALLY for the array
    F = malloc(sizeof(int) * (n+1)); // ignore the red squiggly line
    for (int i=0; i<=n; i++) {
        F[i] = -1;
    }
    
    printf("The value of F(%d) is: %d \n", n, top_down_dp(n));
        
}