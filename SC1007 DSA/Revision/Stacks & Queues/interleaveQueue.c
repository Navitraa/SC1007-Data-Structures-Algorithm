//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//////////////////////////////////   linked list /////////////////////////////////

typedef struct _listnode{
   int item;
   struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
   ListNode *tail;
} LinkedList;

////////////////////////////////// stack    ///////////////////////////////////////////////////////

typedef struct stack{
	LinkedList ll;
} Stack;

//////////////////////////////////// queue ////////////////////////////////////////////////////////

typedef struct _queue{
	LinkedList ll;
} Queue;

///////////////////////// function prototypes ////////////////////////////////////


void interleaveQueue(Queue *q) {
    Queue temp;
    temp.ll.head = NULL;
    temp.ll.tail = NULL;
    temp.ll.size = 0;
    int size = q->ll.size;

    // create new temporary queue which stores first half of all elements
    for (int i = 0; i < size/2; i++) {
        enqueue(&temp, dequeue(q));
    }

    // now interleave
    while (!isEmptyQueue(&temp)) {
        enqueue(q, dequeue(&temp));
        enqueue(q, dequeue(q));
    }
}