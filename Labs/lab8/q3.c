#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//memory
int *r;

// NEW: Added a helper function to print integer-array in ascending order - IDG the concept of first_cut[] array at all !!!!
void print_pos(int rlength, int first_cut[]) { // rlength = length n of rod given
    // Base case
    if (rlength == 0) {
        return;
    }

    // Recursive case => CANNOT UNDERSTAND !!!! must revisit
    int pos = first_cut[rlength];
    printf("%d ", pos);
    print_pos(rlength-pos,first_cut);
}

//write your code here
// TO ADD: print the list of lengths of cutting pieces (in ascending order) achieved in the optimal solution
int cr_bottom_up_dp_print(int *p, int n) // n = length of rod; p = price list
{
    // NEW: initialise array to track the position of the first cut for each rod length (i.e. length of cut-piece of rod)
    int first_cut[n+1];
    for (int i=0; i <= n; i++) { // initialise all values in the array to 0 (can initialise first_cut[n]=0 too, since NULL=0 for an integer array)
        first_cut[i] = 0;
    }

    // Base case
    r[0] = 0;

    // Recursive case
    for (int j = 1; j <= n; j++) { // j = rod length (building it bottom up)
        int pos_temp = 0; // NEW: initialise as pos=0 to assume no cutting/ length of rod = 0 ?
        for (int i = 1; i <= j; i++) { // i = length of first rod
            int temp = p[i] + r[j-i]; // p[i] = price of a rod of length i
            if (temp > r[j]) { // r[j] = maximum revenue obtained by cutting a rod of length j into pieces
                pos_temp = i; // NEW! 
                r[j] = temp; // update maximum revenue
            }
        }
        first_cut[j] = pos_temp;
    }

    // Print lengths of cut-rod pieces in ascending order || and returns max-revenue value
    printf("Length of each piece is:\n");
    print_pos(n,first_cut);
    printf("\n");
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
    r = malloc(sizeof(int) * (n+1));
    
    
    //set all memory elements to -1
    for (i=0; i<=n; i++)
        r[i] = -1;
                
    printf("The maximun value is: %d \n", cr_bottom_up_dp_print(p,n));
}