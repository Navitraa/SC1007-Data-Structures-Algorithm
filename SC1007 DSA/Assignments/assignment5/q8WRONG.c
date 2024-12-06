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
    for(i=0;i<g.V;i++) 
        g.visited[i] = 0;
    
    
    int V1, V2;
    printf("Enter two vertices which are adjacent to each other: (press a to stop)\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.matrix[V1-1][V2-1] = 1;
            g.matrix[V2-1][V1-1] = 1;
            g.E++;
        }
        else
            break;
        printf("Enter two vertices which are adjacent to each other: (press a to stop)\n");
    }
    scanf("%*c");
    
    
    int res = Connected(g);
    if(res ==1)
        printf("The graph is connected.\n");
    else
        printf("The graph is not connected.\n");

    return 0;
}

// Each DFS algo should return number of neighbour_vertices visited
int DFS_I (Graph *g, int v)
{
    // create a stack + initialise vertices_visitied index
    Stack s;
    s.head = NULL;
    s.size = 0;
    int visited_index = 0;

    // adjust starting vertex v for 0-based indexing
    // v = v - 1;

    // push starting vertex v into the stack, mark it as visited and print it
    push(&s, v);
    g->visited[v] = 1;
    visited_index++;
    printf("%d ", v + 1);

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
                visited_index++;

                // print the current vertex u (adjust for 1-based indexing)
                printf("%d ", u + 1); 

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
    return visited_index;
}

// Write your code here
int Connected (Graph g)
{
    // put each target_vertex through DFS algorithm: initialise target array
    for (int i = 0; i < g.V; i++) {
        g.visited[i] = 0; // initialise all target_vertexes as unvisited
    }
    
    // choose starting target_vertex: put it through DFS algorithm
    for (int v = 0; v < g.V; v++) {
        if (g.visited[v] == 0) {
            int neighbour_vertices_visited = DFS_I(&g, v);
            if (neighbour_vertices_visited < g.V) { 
                return 0; // not connected
            }
        }
    }
    // if all goes smoothly, return 1 (is connected)
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
