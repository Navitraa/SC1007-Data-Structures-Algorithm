
int *F;

int main ()
{
    int n;
    int function;
    int i;
    printf("Enter the value of n:\n");
    scanf("%d",&n);

    // create and initialise memory DYNAMICALLY for the array
    F = malloc(sizeof(int) * (n+1)); // ?????
    for (int i=0; i<=n; i++) {
        F[i] = -1;
    }
    
    printf("The value of F(%d) is: %d \n", n, top_down_dp(n));
        
}