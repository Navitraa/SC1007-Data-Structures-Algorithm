//////////////////////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include <stdlib.h>

//////////////////////////////////   linked list //////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
	int size;
	ListNode *head;
	ListNode *tail;
} LinkedList;

////////////////////////////////// stack    //////////////////////////////////////////////
typedef struct stack{
	LinkedList ll;
} Stack;

//////////////////////////////////// queue ////////////////////////////////////////////

typedef struct _queue{
	LinkedList ll;
} Queue;

////////////////////////////////////////////////////////////////////////////////
void printList(ListNode *head);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int item);
int removeNode(LinkedList *ll, int index);

///////////////////////////// declare functions ///////////////////////////////////////
void removeUntil(Stack *s, int value);

////////////////////////// main function ///////////////////////////
int main() 
{
    int input, value;
    printf("Enter a stack of numbers (with the topmost number displayed on the right): ");
    scanf("%d", &input);
    printf("Enter your chosen value (among integers): ");
    scanf("%d", &value);

    int n = 0;
    int input_copy = input;
    Stack *s = malloc(sizeof(Stack)); // allocate memory for the stack
    s->ll.size = 0;
    s->ll.head = NULL;

    while (input_copy > 0)
    {
        int digit = input_copy % 10;
        insertNode(&(s->ll), n, digit);
        input_copy /= 10;
        n++;
    }

    removeUntil(s, value);
}


///////////////////////// function definitions ///////////////////////////
int insertNode(LinkedList *ll, int index, int item){
    ListNode  *pre, *newNode;
    // If empty list or inserting first node, update head pointer
    if (index == 0){
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = ll->head;

        ll->head = newNode;
        ll->size++;
        return 1;
    }
    // Find the nodes before and at the target position; Create a new node and reconnect the links
    else if ((pre = findNode(ll, index-1)) != NULL){
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = pre->next;
        pre->next = newNode;
        ll->size++;
        return 1;
    }
    return 0;
}


void removeUntil(Stack *s, int value)
{
    // Traverse the stack from top to bottom
    while (s->ll.head != NULL)
    {
        int topValue = ((s->ll).head)->item; // peek() function

        if (topValue == value) return;
        else
        {
            ListNode *tmp = (s->ll).head;
            s->ll.head = s->ll.head->next;
            free(tmp);
            s->ll.size--;
        }
    }
}
