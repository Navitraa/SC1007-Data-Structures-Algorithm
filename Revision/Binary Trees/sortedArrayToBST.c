
BTNode* sortedArrayToBST(int arr[], int start, int end) {
    // Base case: if start is greater than end, return NULL
    if (start > end) {
        return NULL;
    }

    // Recursive case: get middle element
    int mid = start + (end - start) / 2;

    // Recursive case: create new node with the middle element
    BTNode *node = (BTNode*) malloc(sizeof(BTNode));
    node->item = arr[mid];

    // Recursive case: build the left and right subtrees
    node->left = sortedArrayToBST(arr, start, mid-1);
    node->right = sortedArrayToBST(arr, mid+1, end);

    return node;
}