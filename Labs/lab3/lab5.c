////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

////////////////////////////////////////////////////////////////////


typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;

} BTNode;

////////////////////////////////////////////////////////////////////


void mirrorTree(BTNode *node);

void printSmallerValues(BTNode *node, int m);
int smallestValue(BTNode *node);
int hasGreatGrandchild(BTNode *node);

void printTree_InOrder(BTNode *node);

////////////////////////////////////////////////////////////////////

int main(int argc, const char * argv[]){

	int i;
	BTNode *root, *root2;
	BTNode btn[15];

	// Create the tree in Q1
	// Using manual dynamic allocation of memory for BTNodes

	root = malloc(sizeof(BTNode));
	root->item = 4;

	root->left = malloc(sizeof(BTNode));
	root->left->item = 5;

	root->right = malloc(sizeof(BTNode));
	root->right->item = 2;

	root->left->left = NULL;

	root->left->right = malloc(sizeof(BTNode));
	root->left->right->item = 6;

	root->left->right->left = NULL;
	root->left->right->right = NULL;

	root->right->left = malloc(sizeof(BTNode));
	root->right->left->item = 3;

	root->right->right = malloc(sizeof(BTNode));
	root->right->right->item = 1;

	root->right->left->left = NULL;

	root->right->left->right = NULL;

	root->right->right->left = NULL;

	root->right->right->right = NULL;

	printTree_InOrder(root);
	printf("\n");
	mirrorTree(root);
	printTree_InOrder(root);
	printf("\n\n");

	//question 2
	printf("\n input m for question 2:");
	scanf("%d", &i);
	printf("the values smaller than %d are:", i);
	printSmallerValues(root, i);
	printf("\n\n");

	//question 3
	printf("The smallest value in the tree is %d.\n", smallestValue(root));

	//question 4
	// Create a tree for Q4: Tall enough so some nodes have great-grandchildren
	// Use array of BTNodes, create tree by linking nodes together
	for (i = 0; i <= 6; i++){
		btn[i].item = i;
		btn[i].left = &(btn[i * 2 + 1]);
		btn[i].right = &(btn[i * 2 + 2]);
	}

	for (i = 7; i <= 14; i++){
		btn[i].item = i;
		btn[i].left = NULL;
		btn[i].right = NULL;
	}
	root2 = &btn[0];

	printf("The tree for question 4 visited by in-order is \n");
	printTree_InOrder(root2);
	printf("\nthe values stored in all nodes of the tree that have at least one great-grandchild are: ");

	hasGreatGrandchild(root2);

	return 0;
}

// Helper function for Q4 to determine depth from a node
int depth(BTNode *node) {
    if (node == NULL) {
        return 0;
    }
    int leftDepth = depth(node->left);
    int rightDepth = depth(node->right);

    if (leftDepth > rightDepth){
        return (1+leftDepth);
    }
    else {
        return (1+rightDepth);
    }
}

void mirrorTree(BTNode *node){

	// Q1. write your code here (Method: by recursion)
    // base case
    if (node == NULL) {
        return;
    }

    // general case: recursive steps
    mirrorTree(node->left);
    mirrorTree(node->right);

    // general case: actual steps
    BTNode *tmp = node->left;
    node->left = node->right;
    node->right = tmp;

}

int hasGreatGrandchild(BTNode *node){

	// Q2. write your code here
    //base case
    if (node == NULL){
        return 0;
    }

    //general case  ====> i dont understand this !!
    int count = 0;
    if (depth(node) >= 4){
        printf("%d", node->item);
        count = 1;
    }

    count += hasGreatGrandchild(node->left);
    count += hasGreatGrandchild(node->right);
    return count;
}

void printSmallerValues(BTNode *node, int m){

	// Q3. write your code here (Method: recursion in-order)
    //base case
    if (node ==  NULL){
        return;
    }

    //general case: recurse through left and right 
    printSmallerValues(node->left, m);
    printSmallerValues(node->right, m);

    //general case: process current node
    if (node->item < m) {
        printf("%d", node->item);
    }
}

int smallestValue(BTNode *node) {

	// Q4. write your code here
    //base case
    if (node == NULL){
        return 1000;
    }

    //general case: want to visit by in-order
    int leftMin = smallestValue(node->left);
    int rightMin = smallestValue(node->right);

    //general case:
    int minVal = node->item;
    if (leftMin < minVal){
        minVal = leftMin;
    }
    if (rightMin < minVal){
        minVal = rightMin;
    }
    
    return minVal;
}


//////////////////////////////////////////////////////////////////

void printTree_InOrder(BTNode *node){

	if (node == NULL) return;
	printTree_InOrder(node->left);
	printf("%d, ", node->item);
	printTree_InOrder(node->right);
	return;
}