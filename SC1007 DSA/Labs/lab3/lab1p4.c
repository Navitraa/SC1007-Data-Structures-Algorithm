#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode{
    int item;
    struct _listnode *next;
} ListNode;


void printList(ListNode *cur);
ListNode * findNode(ListNode *cur, int index);
int insertNode(ListNode **ptrHead, int index, int item);
void deleteList(ListNode **ptrHead);
int duplicateReverse(ListNode *cur,ListNode **ptrNewHead);

int main()
{
    ListNode *head=NULL;
    ListNode *dupRevHead=NULL; // initialise an empty linked list for reverse_list
    int size =0;
    int item;

    printf("Enter a list of numbers, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
        if(insertNode(&head,size, item)) size++;
    scanf("%*s");

    printf("\nBefore duplicateReverse() is called:\n");
    printList(head);

    duplicateReverse(head,&dupRevHead);

    printf("\nAfter duplicateReverse() was called:\n");
    printf("The original list:\n");
    printList(head);
    printf("The duplicated reverse list:\n");
    printList(dupRevHead);

    if(head!=NULL)
       deleteList(&head);
    if(dupRevHead)
       deleteList(&dupRevHead);

    return 0;
}

void printList(ListNode *cur){
    printf("Current List: ");
    while (cur != NULL){
        printf("%d ", cur->item);
        cur = cur->next;
    }
    printf("\n");
}

ListNode *findNode(ListNode* cur, int index)
{
   if (cur==NULL || index<0)
      return NULL;
   while(index>0){
      cur=cur->next;
      if (cur==NULL)
         return NULL;
      index--;
   }
   return cur;
}

int insertNode(ListNode **ptrHead, int index, int item){
    ListNode  *pre, *newNode;
    // If empty list or inserting first node, update head pointer
    if (index == 0){
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = *ptrHead;
        *ptrHead = newNode;
        return 1;
    }
    // Find the nodes before and at the target position
    // Create a new node and reconnect the links
    else if ((pre = findNode(*ptrHead, index-1)) != NULL){
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = pre->next;
        pre->next = newNode;
        return 1;
    }
    return 0;
}

void deleteList(ListNode **ptrHead){
    ListNode *cur = *ptrHead;
    ListNode *temp;
    while (cur!= NULL) {
        temp=cur->next;
        free(cur);
        cur=temp;
    }
    *ptrHead=NULL;
}

int duplicateReverse(ListNode *cur,ListNode **ptrNewHead)
{
    while (cur != NULL) {
        // create copy of the current node
        ListNode *newNode = malloc(sizeof(ListNode));
        if (newNode == NULL) { // in case of memory leak 
            printf("Memory allocation failed\n");
            return -1;
        }

        // get headptr to point to the current node
        newNode->item = cur->item;
        newNode->next = *ptrNewHead;
        *ptrNewHead = newNode;

        // move to the next node in the original list
        cur = cur->next;
    }     
}

/* 
int duplicateReverse(ListNode *cur,ListNode **ptrNewHead)
{
    // Method: using recursion
    if (cur == NULL) return 0; // Base case: reached the end of the original list

    // Reach the end of the list
    int result = duplicateReverse(cur->next, ptrNewHead);
    if (result != 0) return -1; // Error encountered during recursion

    // Create new node and insert at index 0 of the new list
    ListNode *newNode = malloc(sizeof(ListNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return -1; // Memory allocation failed
    }
    newNode->item = cur->item;
    newNode->next = *ptrNewHead;
    *ptrNewHead = newNode;

    return 0; // success
}
*/