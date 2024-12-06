#include <stdio.h>
#include <stdlib.h>

typedef struct _graph {
    int V;
    int E;
    int *visited;
    int **matrix;
} Graph;

void printGraphMatrix(Graph g);
void RecursiveBFS(Graph *g, int *queue, int front, int rear);

// Utility functions from Code Reference 2
void enqueue(int *queue, int *rear, int item);
int dequeue(int *queue, int *front);
int isQueueEmpty(int front, int rear);

int main() {
    Graph g;
    int i, j;

    printf("Enter the number of vertices:\n");
    scanf("%d", &g.V);

    g.E = 0;
    g.matrix = (int **)malloc(g.V * sizeof(int *));
    for (i = 0; i < g.V; i++)
        g.matrix[i] = (int *)malloc(g.V * sizeof(int));

    for (i = 0; i < g.V; i++)
        for (j = 0; j < g.V; j++)
            g.matrix[i][j] = 0;

    g.visited = (int *)malloc(sizeof(int) * g.V);
    for (i = 0; i < g.V; i++) g.visited[i] = 0;

    int V1, V2;
    printf("Enter two vertices which are adjacent to each other:\n");
    while (scanf("%d %d", &V1, &V2) == 2) {
        if (V1 > 0 && V1 <= g.V && V2 > 0 && V2 <= g.V) {
            g.matrix[V1 - 1][V2 - 1] = 1;
            g.matrix[V2 - 1][V1 - 1] = 1;
            g.E++;
        } else
            break;
        printf("Enter two vertices which are adjacent to each other:\n");
    }
    scanf("%*c");
    printf("Enter a start vertex for BFS:\n");
    scanf("%d", &i);
    printGraphMatrix(g);

    // Initialize a queue for BFS and start !! note that queue must be initialised 
    int queue[g.V];
    int front = 0, rear = -1;

    enqueue(queue, &rear, i - 1); // Start BFS from vertex i, adjusted for 0-based indexing
    g.visited[i - 1] = 1;

    RecursiveBFS(&g, queue, front, rear);

    return 0;
}

// Write your code here
void RecursiveBFS(Graph *g, int *queue, int front, int rear) {
    // Base case: Empty queue
    if (isQueueEmpty(front, rear)) {
        return;
    }

    // Recursive case: Dequeue the front element and process it
    int v = dequeue(queue, &front);
    printf("%d ", current + 1); // Print the current vertex (1-based indexing)

    // Recursive case: Enqueue all unvisited neighbors
    for (int u = 0; u < g->V; u++) {
        if (g->matrix[v][u] == 1 && g->visited[u] == 0) {
            enqueue(queue, &rear, u);
            g->visited[u] = 1; // Mark as visited
        }
    }

    // Recursive call for the next level
    RecursiveBFS(g, queue, front, rear);
}

// Utility function to enqueue an item
void enqueue(int *queue, int *rear, int item) {
    (*rear)++;
    queue[*rear] = item;
}

// Utility function to dequeue an item
int dequeue(int *queue, int *front) {
    return queue[(*front)++];
}

// Utility function to check if the queue is empty
int isQueueEmpty(int front, int rear) {
    return front > rear;
}

void printGraphMatrix(Graph g) {
    int i, j;

    for (i = 0; i < g.V; i++) {
        for (j = 0; j < g.V; j++)
            printf("%d\t", g.matrix[i][j]);
        printf("\n");
    }
}
