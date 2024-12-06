#include <stdio.h>
#include <stdlib.h>

enum GraphType {ADJ_MATRIX, ADJ_LIST}; // Types of Graph Representation

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;

struct GraphForm{
    int **matrix;
    ListNode **list;
};

typedef struct _graph{
    int V;
    int E;
    enum GraphType type;
    struct GraphForm adj;
}Graph;

void printGraphMatrix(Graph );
void adjM2adjL(Graph *);
void printGraphList(Graph );
void calDegreeV(Graph,int *);
void printDegreeV(int *,int );

int main()
{
    Graph g;
    int i,j;

    int* degreeV;

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.E = 0;
    g.adj.matrix = (int **)malloc(g.V*sizeof(int *));
    for(i=0;i<g.V;i++)
        g.adj.matrix[i] = (int *)malloc(g.V*sizeof(int));

    for(i=0;i<g.V;i++)
        for(j=0;j<g.V;j++)
            g.adj.matrix[i][j] = 0;
    g.type = ADJ_MATRIX;

    degreeV = (int *) malloc(g.V*sizeof(int));
    for(i=0;i<g.V;i++)
        degreeV[i]=0;

    int V1, V2;
    printf("Enter two vertices which are adjacent to each other: (enter a to stop)\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.adj.matrix[V1-1][V2-1] = 1;
            g.adj.matrix[V2-1][V1-1] = 1;
            g.E++;
        }
        else
            break;
        printf("Enter two vertices which are adjacent to each other: (enter a to stop)\n");
    }

    printGraphMatrix(g);
    
    adjM2adjL(&g);
    
    printGraphList(g);

    calDegreeV(g,degreeV);
    
    printDegreeV(degreeV,g.V);

    return 0;
}

void printGraphMatrix(Graph g)
{
    int i,j;
    printf("Print graph matrix \n");
    if(g.type == ADJ_LIST) {printf("Error"); return;}
    
    for(i=0;i<g.V;i++){ // since its symmetrical about y=-x anyways
        for(j=0;j<g.V;j++)
            printf("%d\t",g.adj.matrix[i][j]);
        printf("\n"); //new line after each row has been printed
    }
    printf("\n"); //new line after the entire matrix has been printed

}

void adjM2adjL(Graph *g) {
    // initialise variables
    int i, j;
    ListNode **list;
    ListNode *temp;

    // error handling: return input if graph is already in adjacency list form
    if (g->type == ADJ_LIST) {
        printf("Error: Graph is already in adjacency list form \n");
        return;
    }

    // error handling: graph has no vertices, then empty graph need not be converted
    if (g->V <= 0) {
        printf("Empty graph\n");
        return;
    }

    // initalise array of linked list heads for the adjacency list (malloc, initialise NULL)
    list = (ListNode **) malloc (g->V * sizeof(ListNode *)); // NOTE syntax: it's (ListNode *) not ListNode!
    for (i = 0; i < g->V; i++) {
        list[i] = NULL;
    }

    // iterate over adjacency matrix to fill the adjacency list (traverse thru matrix, if == 1 then insert node, case 1, case 2)
    for (i = 0; i < g->V; i++) {
        for (j = 0; j < g->V; j++) {
            // if there is an edge between i and j
            if (g->adj.matrix[i][j] == 1) {
                // case 1: insert node at head of the adjlist
                if (list[i] == NULL) {
                    list[i] = (ListNode *) malloc(sizeof(ListNode));
                    list[i]->vertex = j+1; // TO CLARIFY: idg the i, j concept !! adjust for 1-based indexing
                    list[i]->next = NULL;
                    temp = list[i];
                }

                // case 2: append to existing non-NULL adjlist
                else {
                    temp->next = (ListNode *) malloc(sizeof(ListNode));
                    temp->next->vertex = j+1;
                    temp->next->next = NULL;
                    temp = temp->next;
                }
            }
        }
    }

    // update graph type to ADJ_LIST after conversion
    g->type = ADJ_LIST;

    // free memory for ADJ_MATRIX since it is no longer needed   ---- TO CLARIFY LOGIC ALSO !!!!!!!!!!!!!!!!
    for (i = 0; i<g->V; i++) {
        free(g->adj.matrix[i]);
    free(g->adj.matrix);   
    }

    // update graph structure to point to the newly-created ADJ_LIST
    g->adj.list = list; // NOTE syntax
}

// Write your code here
void calDegreeV(Graph g, int *degreeV)
{
    // initialise variables
    int i;
    ListNode *temp = NULL;

    // set degree for each vertex
    // iterate thru each row of linkedlist i.e. each vertex
    for (i = 0; i < g.V; i++) {
        // initialise
        degreeV[i] = 0;
        temp = g.adj.list[i];
        // count degree and update degreeV[i]
        while (temp != NULL) {
            degreeV[i]++;
            temp = temp->next;
        }
    }
}

void printDegreeV(int *degreeV,int V)
{
    int i;
    for(i=0;i<V;i++)
        printf("%d: %d degree\n",i+1,degreeV[i]);
}



