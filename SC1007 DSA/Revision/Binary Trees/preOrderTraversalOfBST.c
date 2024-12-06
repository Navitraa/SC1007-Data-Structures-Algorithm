
void iterativePreOrderTraversal(TreeNode *root) {
    // Base case
    if (root == NULL) {
        return;
    }

    // Recursive case: initialise stack
    Stack *stack = (Stack*) malloc(sizeof(Stack));
    stack->top = NULL;

    // Recursive case: using the stack for iterative process
    push(stack, root);

    while (!isEmptyStack(stack)) {
        TreeNode *current = pop(stack);
        printf("%d", current->data);
        if (current->right) {
            push(stack, current->right);
        }
        if (current->left) {
            push(stack, current->left);
        }
    }
    free(stack);
}