#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//memory
int *r; // Use r !!! 

//write your code here; q = max revenue for rod of length n
int cr_recursive(int *p, int n)
{
    // Base case: n=0
    if (n == 0) {
        return 0;
    }

    // Recursive part
    int q = -1; // DONT UNDERSTAND WHY HERE: q is initialised to -1 to store maximum revenue for rod of length n
    // recurse through different lengths of the first piece of rod (after cutting)
    for (int i = 1; i <= n; i++) {
        int temp = p[i] + cr_recursive(p, n-i); // store value using recursive function
        // update maximum value
        if (temp > q) {
            q = temp;
        }
    }
    return q;
}

//write your code here
int cr_top_down_dp(int *p, int n)
{
    // Base cases
    if (n == 0) {
        return 0;
    }

    // Check memory -> retrieve r[n] if it has already been calculated
    if (r[n] > 0) { // default r[n] = -1 (initialised in the main function)
        return r[n];
    }
    
    // Recursive part
    int q = -1; // JUST NOTE ig (there seems to be a pattern)
    for (int i = 1; i <= n; i++) {
        int temp = p[i] + cr_top_down_dp(p, n-i); // store value using recursive function
        // update maximum value
        if (temp > q) {
            q = temp;
        }
    }
    r[n] = q; // update the memory wif the max value
    return q;
    

}

//write your code here
int cr_bottom_up_dp(int *p, int n) // n = length of rod; p = price list
{
    r[0] = 0;
    for (int j = 1; j <= n; j++) { // j = rod length (building it bottom up)
        // This chunk is pretty standard.
        for (int i = 1; i <= j; i++) { // i = length of first rod
            int temp = p[i] + r[j-i]; // p[i] = price of a rod of length i
            if (temp > r[j]) { // r[j] = maximum revenue obtained by cutting a rod of length j into pieces
                r[j] = temp; // update maximum revenue
            }
        }
    }
    return r[n];
}
 
void main ()
{
    int n;      //length of  rod
    int function;
    int i;
    int *p;     //price list
    
    int price_list[10] = {0,1,4,8,9,10,17,17,20,24}; //declare one more value to cover the index 0;
    
    n = sizeof(price_list) / sizeof(int) - 1;
    p = price_list;
    
    
    //allocate the memory array
    r = malloc(sizeof(int) * (n+1)); // +1 for to add the NULL at the end of the array
    
    printf("Choose a function (1 for recursive, 2 for top-down DP, 3 for bottom-up DP, 0 to stop): \n");
    scanf("%d",&function);
    while (function != 0)
    {
        if (function == 1)
        {
            printf("The maximun value is: %d \n", cr_recursive(p,n));
        }
        else if (function == 2)
        {
            //set all memory elements to -1
            for (i=0; i<=n; i++)
                r[i] = -1;
                
            printf("The maximun value is: %d \n", cr_top_down_dp(p,n));
        }
        else if (function == 3)
        {
            //set all memory elements to -1
            for (i=0; i<=n; i++)
                r[i] = -1;
                
            printf("The maximun value is: %d \n", cr_bottom_up_dp(p,n));
        }
        printf("Choose a function (1 for recursive, 2 for top-down DP, 3 for bottom-up DP, 0 to stop): \n");
        scanf("%d",&function);
    }
}