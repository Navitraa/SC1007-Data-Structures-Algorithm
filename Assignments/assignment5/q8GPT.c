#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode {
    int vertex;
    struct _listnode *next;
} ListNode;

typedef ListNode StackNode;

typedef struct _graph {
    int V;
    int E;
    int *visited; // Store the visited vertices
    int **matrix;
} Graph;

typedef struct _linkedlist {
    int size;
    ListNode *head;
} Stack;

// Stack-related functions
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);

// Graph-related functions
void printGraphMatrix(Graph g);
int Connected(Graph g);

// DFS Function
void DFS_I(Graph *g, int v);  // Now void as we only need to mark visited vertices

int main() {
    Graph g;
    int i, j;

    printf("Enter the number of vertices:\n");
    scanf("%d", &g.V);

    g.E = 0;
    g.matrix = (int **) malloc(g.V * sizeof(int *));
    for (i = 0; i < g.V; i++)
        g.matrix[i] = (int *) malloc(g.V * sizeof(int));

    for (i = 0; i < g.V; i++)
        for (j = 0; j < g.V; j++)
            g.matrix[i][j] = 0;

    g.visited = (int *) malloc(sizeof(int) * g.V);
    for (i = 0; i < g.V; i++)
        g.visited[i] = 0;

    int V1, V2;
    printf("Enter two vertices which are adjacent to each other: (press a to stop)\n");
    while (scanf("%d %d", &V1, &V2) == 2) {
        if (V1 > 0 && V1 <= g.V && V2 > 0 && V2 <= g.V) {
            g.matrix[V1 - 1][V2 - 1] = 1;
            g.matrix[V2 - 1][V1 - 1] = 1;
            g.E++;
        } else
            break;
        printf("Enter two vertices which are adjacent to each other: (press a to stop)\n");
    }
    scanf("%*c");

    int res = Connected(g);
    if (res == 1)
        printf("The graph is connected.\n");
    else
        printf("The graph is not connected.\n");

    return 0;
}

// DFS function using stack to visit all connected vertices from vertex `v`
void DFS_I(Graph *g, int v) {
    // Create a stack
    Stack s;
    s.head = NULL;
    s.size = 0;

    // Push the starting vertex onto the stack
    push(&s, v);
    g->visited[v] = 1;  // Mark it as visited

    // While the stack is not empty
    while (!isEmptyStack(s)) {
        int w = peek(s);  // Get the top of the stack

        // Look for unvisited adjacent vertices
        int foundUnvisited = 0;
        for (int u = 0; u < g->V; u++) {
            if (g->matrix[w][u] == 1 && g->visited[u] == 0) {
                // Push the unvisited vertex onto the stack and mark as visited
                push(&s, u);
                g->visited[u] = 1;
                foundUnvisited = 1;
                break;  // Explore this vertex next
            }
        }

        // If no unvisited adjacent vertex was found, pop from the stack
        if (!foundUnvisited) {
            pop(&s);
        }
    }
}

// Check if the graph is connected
int Connected(Graph g) {
    // Start DFS from vertex 0 (any vertex would work)
    DFS_I(&g, 0);

    // Check if all vertices are visited
    for (int i = 0; i < g.V; i++) {
        if (g.visited[i] == 0) {
            return 0;  // If any vertex is unvisited, the graph is not connected
        }
    }
    return 1;  // If all vertices are visited, the graph is connected
}

// Stack functions
void push(Stack *sPtr, int vertex) {
    StackNode *newNode = malloc(sizeof(StackNode));
    newNode->vertex = vertex;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr) {
    if (sPtr == NULL || sPtr->head == NULL) {
        return 0;
    } else {
        StackNode *temp = sPtr->head;
        sPtr->head = sPtr->head->next;
        free(temp);
        sPtr->size--;
        return 1;
    }
}

int isEmptyStack(Stack s) {
    return (s.size == 0);
}

int peek(Stack s) {
    return s.head->vertex;
}

void removeAllItemsFromStack(Stack *sPtr) {
    while (pop(sPtr));
}

void printGraphMatrix(Graph g) {
    int i, j;
    for (i = 0; i < g.V; i++) {
        for (j = 0; j < g.V; j++)
            printf("%d\t", g.matrix[i][j]);
        printf("\n");
    }
}
