#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode{
    int key;
    struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} HashTableNode;

typedef struct _hashTable{
   int hSize; //size of hash table
   int nSize; //number of inserted keys
   HashTableNode *Table;
} HashTable;

int Hash(int,int);

ListNode* HashSearch(HashTable, int);
int HashInsert(HashTable *, int);

//In Practice, we will not do it
void HashPrint(HashTable);

int main()
{
    int opt;
    int size;

    int i;
    int key;

    //Create a HashTable
    HashTable Q3Hash;
    Q3Hash.hSize = 0; 
    Q3Hash.nSize = 0; 
    Q3Hash.Table = NULL;

    printf("============= Hash Table ============\n");
    printf("|1. Create a hash table             |\n");
    printf("|2. Insert a key to the hash table  |\n");
    printf("|3. Search a key in the hash table  |\n");
    printf("|4. Print the hash table            |\n");
    printf("|5. Quit                            |\n");
    printf("=====================================\n");

    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=4){
        switch(opt){
        case 1:
            printf("Enter the size of hash table:\n");
            scanf("%d",&Q3Hash.hSize);

            Q3Hash.nSize = 0;

            Q3Hash.Table = (HashTableNode *) malloc(sizeof(HashTableNode)*(Q3Hash.hSize));

            for(i=0;i<Q3Hash.hSize;i++){
               Q3Hash.Table[i].head = NULL;
               Q3Hash.Table[i].size = 0;
            }
            printf("HashTable is created.\n");
            break;
        case 2: //Insertion
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);

            if(HashInsert(&Q3Hash,key))
                printf("%d is inserted.\n",key);
            else
                printf("%d is a duplicate. No key is inserted.\n",key);
            break;
        case 3: //Search
            printf("Enter a key for searching in the HashTable:\n");
            scanf("%d",&key);
            ListNode* node = HashSearch(Q3Hash, key);

            if(node!=NULL)
                printf("%d is found.\n",key);
            else
                printf("%d is not found.\n",key);
            break;
        case 4:
            HashPrint(Q3Hash);
            break;
        }

    printf("Enter selection: ");
    scanf("%d",&opt);
    }

    for(i=0;i<Q3Hash.hSize;i++)
    {
        while(Q3Hash.Table[i].head)
        {
            ListNode *temp;
            temp = Q3Hash.Table[i].head;
            Q3Hash.Table[i].head = Q3Hash.Table[i].head->next;
            free(temp);
        }
    }
    free(Q3Hash.Table);

    return 0;

}

int Hash(int key,int hSize)
{
    return key%hSize;
}

//write your code here
ListNode* HashSearch(HashTable Q3Hash, int key)
{
    // Step 1: Initialise variables
    int index;
    ListNode *temp;

    // Step 2: Get hash value from non-empty hash table
    if (Q3Hash.hSize != 0) {
        index = Hash(key, Q3Hash.hSize);
    }
    else {
        return NULL;
    }

    // Step 3: Traverse through linked list to find the key value in the hash table
    temp = Q3Hash.Table[index].head;
    while (temp != NULL) {
        if (temp->key == key) {
            return temp;
        }
        temp = temp->next;
    }

    // Step 4: Return NULL if the while loop completes w/o finding the key
    return NULL;
}

//write your code here
int HashInsert(HashTable* Q3HashPtr, int key)
{
    // Step 1: Initialise variables
    int index;
    ListNode *newNode;

    // Step 2: Check for duplicate 
    if (HashSearch(*Q3HashPtr, key) != NULL) {
        return 0;
    }

    // Step 3: Obtain index value of key-to-be-added
    index = Hash(key, Q3HashPtr->hSize);

    // Step 4: Create new node containing the key
    newNode = (ListNode *) malloc (sizeof(ListNode));
    newNode->key = key;

    // Step 5: Insert the key (update links + update count)
    newNode->next = Q3Hash.Table[index].head;
    Q3Hash.Table[index].head = newNode;

    Q3HashPtr->nsize++;
    Q3HashPtr->Table[index].size++;

    // Step 6: Return 1 if node has been successfully inserted
    return 1;
}

void HashPrint(HashTable Q3Hash)
{
    int i;
    ListNode *temp;
    for(i=0;i<Q3Hash.hSize;i++)
    {
        temp =Q3Hash.Table[i].head;
        printf("%d:  ",i);
        while(temp !=NULL)
        {
            printf("%d -> ", temp->key);
            temp = temp->next;
        }
        printf("\n");
    }
}