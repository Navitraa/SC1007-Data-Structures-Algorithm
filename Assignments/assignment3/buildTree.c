#include <stdio.h>
#include <stdlib.h>

#define MAX_N 120

typedef struct _btnode{
    char id;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

void buildTree(BTNode** node, char* preO, char* postO);
void inOrder(BTNode *cur);
void preOrder(BTNode *cur);
void postOrder(BTNode *cur);

int main()
{
    char preO[MAX_N];
    char postO[MAX_N];
    scanf("%s",preO);
    scanf("%s",postO);

    BTNode* root=NULL;
    buildTree(&root,preO,postO);
    if(root==NULL) printf("error\n");
    preOrder(root);
    printf("\n");
    postOrder(root);
    printf("\n");

    inOrder(root);
    printf("\n");

    return 0;
}
void inOrder(BTNode *cur){
    if (cur == NULL)
        return;

    inOrder(cur->left);
    printf("%c",cur->id);
    inOrder(cur->right);
}
void preOrder(BTNode *cur){
    if (cur == NULL)
        return;

    printf("%c",cur->id);
    preOrder(cur->left);
    preOrder(cur->right);
}
void postOrder(BTNode *cur){
    if (cur == NULL)
        return;

    postOrder(cur->left);
    postOrder(cur->right);
    printf("%c",cur->id);
}

#include <string.h>

char *sliceString(char *str, int start, int end)
{
    int size = (end - start + 1);
    char *output = (char *)malloc((size + 1) * sizeof(char));

    for (int i = 0; i < size; i++) {
        output[i] = str[start + i];
    }

    output[size] = '\0';

    return output;
}

void buildTree(BTNode** node, char* preO, char* postO)
{
    // Base case: if preO is empty, return
    if (preO[0] == '\0') {
        return;
    }

    // Initialize the root node if it doesn't exist
    if (*node == NULL) {
        *node = (BTNode*)malloc(sizeof(BTNode));
        (*node)->id = preO[0];
        (*node)->left = NULL;
        (*node)->right = NULL;
    }

    // Base case: If there is only one node, we're done
    if (strlen(preO) == 1) {
        return;
    }

    // The root of the left subtree is the second element in preorder
    char left_node = preO[1];

    // Find the position of left_node in the postorder array
    char *leftRootPos = strchr(postO, left_node);
    int position = (int)(leftRootPos - postO);

    // Calculate the size of the left subtree
    int leftSubtreeSize = position + 1;

    // Initialize Left and Right preorder/postorder strings
    char *left_preO = sliceString(preO, 1, 1 + leftSubtreeSize - 1);
    char *right_preO = sliceString(preO, 1 + leftSubtreeSize, strlen(preO) - 1);
    char *left_postO = sliceString(postO, 0, leftSubtreeSize - 1);
    char *right_postO = sliceString(postO, leftSubtreeSize, strlen(postO) - 2);

    // Build the left subtree
    buildTree(&(*node)->left, left_preO, left_postO);
    // Build the right subtree
    buildTree(&(*node)->right, right_preO, right_postO);

    // Free the dynamically allocated memory
    free(left_preO);
    free(right_preO);
    free(left_postO);
    free(right_postO);
}






// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
/*/ Write your code here

    // Base case
    if (*node == NULL) { //since node is a double pointer, shld check *node == NULL 
        return;
    }

    // Recursive case: evaluate current node
    char root = preO[0];
    node->item = root;
    char left_node = preO[1];
    node->left->item = left_node;

    // split into 4 new strings
    char *leftRootPos = strchr(postO, left_node);

    

} 

int length_postOrder = sizeof(postO) / sizeof(postO[0]);
    int length_preOrder = sizeof(preO) / sizeof(preO[0]);
    char left_postorder[100] = {};
    char right_postorder[100] = {};
    char left_preorder[100] = {};
    char right_preorder[100] = {}; 
    
    //traverse through original postorder string
    for (int i = 0; i < length_postOrder; i++) {
        left_postorder[i] = postO[i+1]; //until left_node->item
        right_postorder[j] = postO[i+1]; //after left_node->item
    }

    //traverse through original preorder string
    strchr(str, ch)
    for (int i = 0; i < length_postOrder; i++) {
        left_preorder.append(preO[i+1]); //until left_node->item
        right_preorder.append(preO[i+1]); //after left_node->item
    }

    buildTree(&node->left, left_preorder, left_postorder);
    buildTree(&node->right, right_preorder, right_postorder);
    
    */