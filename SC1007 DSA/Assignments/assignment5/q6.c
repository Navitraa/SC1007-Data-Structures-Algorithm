#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;

typedef struct _graph{
    int V;
    int E;
    int *visited;
    int **matrix;
}Graph;

typedef ListNode QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

int SD (Graph G, int v, int w);

void printGraphMatrix(Graph );

// You should not change the prototypes of these functions
void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);

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
    printf("Enter two vertices which are adjacent to each other:\n");
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
    // printGraphMatrix(g);
    
    printf("Enter two vertices for finding their shortest distance: (press a to stop)\n");
    scanf("%d %d", &i, &j);

    int d = SD(g,i,j);
    if(d==-1)
        printf("%d and %d are unconnected.\n",i,j);
    else
        printf("The shortest distance is %d\n",d);
    return 0;
}

// Write your code here
int SD(Graph g, int v, int z){
    // create queue & initialise distance
    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    // create distance array to track shortest distance to each vertex
    int *distance = (int*)malloc(g.V * sizeof(int));
    for (int i = 0; i < g.V; i++) {
        distance[i] = -1; // initialise all distances as unreachable
        g.visited[i] = 0; // reset visited array  
    }

    // adjust starting input vertexes for 0-based indexing
    v = v - 1; 
    z = z - 1;
    
    // enqueue starting vertex & mark as visited
    enqueue(&q, v);
    g.visited[v] = 1; // vertex v is marked as visited in the visited[] array
    distance[v] = 0;

    // while the queue is not empty
    while (!isEmptyQueue(q)) {
        // dequeue vertex denoted as w
        int w = dequeue(&q);

        // for each unvisited vertex u adjacent to w 
        for (int u = 0; u < g.V; u++) {
            if ((g.matrix[w][u] == 1) && (g.visited[u] == 0)) {
                // enqueue u and mark as visited
                enqueue(&q, u);
                g.visited[u] = 1;
                distance[u] = distance[w] + 1; // increment distance

                // if we reach target vertex z, return the distance
                if (u == z) {
                    free(distance);
                    return distance[u];
                }
            }
        }
    }
    // if no path to z is found, return -1
    free(distance);
    return -1;
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


void enqueue(Queue *qPtr, int item) {
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    if(newNode==NULL) exit(0);

    newNode->vertex = item;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr) {
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       int headValue = qPtr->head->vertex;
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return headValue;
    }
}

int getFront(Queue q){
    return q.head->vertex;
}

int isEmptyQueue(Queue q) {
    if(q.size==0) return 1;
    else return 0;
}

void removeAllItemsFromQueue(Queue *qPtr)
{
	while(dequeue(qPtr));
}