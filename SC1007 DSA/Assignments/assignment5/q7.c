#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;
typedef ListNode StackNode;

typedef struct _graph{
    int V;
    int E;
    int *visited; //store the visited vertices
    int **matrix;
}Graph;

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} Stack;

// You should not change the prototypes of these functions
//////STACK///////////////////////////////////////////
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
////GRAPH////////////////////////////////////////////
void printGraphMatrix(Graph );
////////////////////////////////////////////

int Connected (Graph);

int main()
{
    Graph g;
    int i,j;
    

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.E = 0;
    g.matrix = (int **)malloc(g.V*sizeof(int *));
    for(i=0;i<g.V;i++)
        g.matrix[i] = (int *)malloc(g.V*sizeof(int));

    for(i=0;i<g.V;i++)
       for(j=0;j<g.V;j++)
           g.matrix[i][j] = 0;
	
	g.visited = (int *) malloc(sizeof(int)*g.V);
    for(i=0;i<g.V;i++) g.visited[i] = 0;
    
    
    int V1, V2;
    printf("Enter a directed edge: (press a to stop)\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.matrix[V1-1][V2-1] = 1;
            g.E++;
        }
        else
            break;
        printf("Enter a directed edge: (press a to stop)\n");
    }
    scanf("%*c");
    
    
    int res = Connected(g);
    if(res == 1)
        printf("The graph is strongly connected.\n");
    else
        printf("The graph is not strongly connected.\n");

    return 0;
}

// Each DFS algo should return number of neighbour_vertices visited
void DFS_I (Graph *g, int v)
{
    // create a stack
    Stack s;
    s.head = NULL;
    s.size = 0;

    // push starting vertex v into the stack, mark it as visited and print it
    push(&s, v);
    g->visited[v] = 1;

    // while the stack is not empty
    while (!isEmptyStack(s)) {
        // peak stack to get top vertex
        int w = peek(s);

        // find an unvisited vertex u adjacent to w
        int foundUnvisited = 0; // initialise
        for (int u = 0; u < g->V; u++) {
            if ((g->matrix[w][u] == 1) && (g->visited[u] == 0)) {
                // push unvisted vertex u onto the stack and mark it as visited
                push(&s, u);
                g->visited[u] = 1;

                // indicate if visited vertex is found; break accordingly
                foundUnvisited = 1;
                break;
            }
        }
        // if no unvisited adjacent vertex was found, pop from the stack (to backtrack)
        if (!foundUnvisited) {
            pop(&s);
        }
    } 
}

// Function to reverse the directed graph
Graph reverseGraph(Graph g) {
    // initialise a new graph called 'reversed'
    Graph reversed;
    reversed.V = g.V;
    reversed.E = g.E;
    reversed.matrix = (int **) malloc(g.V * sizeof(int *));
    reversed.visited = (int *) malloc(sizeof(int) * g.V);

    // reverse matrix
    for (int i = 0; i < g.V; i++) {
        reversed.matrix[i] = (int *) malloc(g.V * sizeof(int));
        for (int j = 0; j < g.V; j++) {
            reversed.matrix[i][j] = g.matrix[j][i];  // Reverse the direction of edges
        }
    }
    return reversed;
}

// Reset the visited array for fresh DFS
void resetVisited(Graph *g) {
    for (int i = 0; i < g->V; i++) {
        g->visited[i] = 0;
    }
}

// Check if the graph is strongly connected
int Connected(Graph g) {
    // Step 1: Perform DFS on the original graph from vertex 0
    DFS_I(&g, 0);

    // Step 2: Check if all vertices are visited
    for (int i = 0; i < g.V; i++) {
        if (g.visited[i] == 0) {
            return 0;  // If any vertex is not visited, graph is not strongly connected
        }
    }

    // Step 3: Reverse the graph
    Graph reversed = reverseGraph(g);

    // Step 4: Reset the visited array for the reversed graph
    resetVisited(&reversed);

    // Step 5: Perform DFS on the reversed graph from vertex 0
    DFS_I(&reversed, 0);

    // Step 6: Check if all vertices are visited in the reversed graph
    for (int i = 0; i < reversed.V; i++) {
        if (reversed.visited[i] == 0) {
            return 0;  // If any vertex is not visited in the reversed graph, it's not strongly connected
        }
    }

    // If both DFS traversals visited all vertices, the graph is strongly connected
    return 1;
}


void printGraphMatrix(Graph g)
{
    int i,j;

    for(i=0;i<g.V;i++){
        for(j=0;j<g.V;j++)
            printf("%d\t",g.matrix[i][j]);
        printf("\n");
    }

}

void push(Stack *sPtr, int vertex)
{
	StackNode *newNode;
    newNode= malloc(sizeof(StackNode));
    newNode->vertex = vertex;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if(sPtr==NULL || sPtr->head==NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

int isEmptyStack(Stack s)
{
     if(s.size==0) return 1;
     else return 0;
}

int peek(Stack s){
    return s.head->vertex;
}

void removeAllItemsFromStack(Stack *sPtr)
{
	while(pop(sPtr));
}
