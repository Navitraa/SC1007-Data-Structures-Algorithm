//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////

typedef struct _btnode{
int item;
struct _btnode *left;
struct _btnode *right;
} BTNode;

///////////////////////////////////////////////////////////////////////

void insertBSTNode(BTNode **node, int value);
void printBSTInOrder(BTNode *node);
int isBST(BTNode *node, int min, int max);
BTNode *removeBSTNode(BTNode *node, int value);
BTNode *findMin(BTNode *p);

///////////////////////////////////////////////////////////////////////

int main(){
	int i=0;

	BTNode *root=NULL;

	//question 1
	do{
		printf("input a value you want to insert(-1 to quit):");

		scanf("%d",&i);
		if (i!=-1)
			insertBSTNode(&root,i);
	}while(i!=-1);

	//question 2
	printf("\n");
	printBSTInOrder(root);

	//question 3
	if ( isBST(root,-1000000, 1000000)==1)
		printf("It is a BST!\n");
	else
		printf("It is not a BST!\n");

	//question 4
	do{
		printf("\ninput a value you want to remove(-1 to quit):");
		scanf("%d",&i);
		if (i!=-1)
		{
			root=removeBSTNode(root,i);
			printBSTInOrder(root);
		}
	}while(i!=-1);


	return 0;
}

//////////////////////////////////////////////////////////////////////

void insertBSTNode(BTNode **node, int value)
{
	// Base case: if node->NULL
    if (*node == NULL) {
        *node = malloc(sizeof(BTNode));
        (*node)->item = value;
        (*node)->left = NULL;
        (*node)->right = NULL;
        return; //note !! 
    }
    // Recursive case: compare values at node
    if (value > (*node)->item) {
        insertBSTNode(&(*node)->right, value);
    }
    else if (value < (*node)->item) {
        insertBSTNode(&(*node)->left, value);
    }
    else {
        printf("Value already exists in the BST \n");
        return;
    }
}

//////////////////////////////////////////////////////////////////////

void printBSTInOrder(BTNode *node)
{
	// Base case: null node
    if (node == NULL) {
        return;
    }

    // Recursive case: LCR
    printBSTInOrder(node->left); //left
    printf("%d", node->item); //current
    printBSTInOrder(node->right); //right

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int isBST(BTNode *node, int min, int max) // the item stored in node has to be smaller than max and larger than min
{
	// Base case: null root
    if (node == NULL) {
        return 1;
    }

    // Recusive case
    if (node->item >= max || node->item <= min) {
        return 0;
    }
    return isBST(node->left, min, node->item) && isBST(node->right, node->item, max);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BTNode *removeBSTNode(BTNode *node, int value)
{
	// Base case: null node
    if (node == NULL) {
        printf("Invalid node \n");
        return NULL;
    }

    // Look for the right node
    if (value > node->item) {
        node->right = removeBSTNode(node->right, value);
    }
    else if (value < node->item) {
        node->left = removeBSTNode(node->left, value);
    }
    else if (value == node->item) {
        //Case1: node has 2 child nodes
        if (node->left != NULL && node->right != NULL) {
            BTNode *smallest_value = findMin(node->right);
            node->item = smallest_value->item; 
            node->right = removeBSTNode(node->right, smallest_value->item);
        }
        //Case2: node has 0-1 child nodes
        else {
            BTNode *p = node;
            if (node->left != NULL) { //only 1 child node
                node = node->left;
            }
            else { // only 1 node OR no child node
                node = node->right;
            }
            free(p);
        }
    }
    return node;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BTNode *findMin(BTNode *p)
{
	if (p->left != NULL) {
        return findMin(p->left);
    }
    else {
        return p;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////