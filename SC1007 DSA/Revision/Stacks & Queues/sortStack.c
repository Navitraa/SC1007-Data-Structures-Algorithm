void sortStack(Stack *sPtr);

int main() {
    Stack s;
    s.size = 0;
    s.head = NULL;

    // Example usage
    push(&s, 6);
    push(&s, 2);
    push(&s, 5);
    push(&s, 1);
    push(&s, 3);
    push(&s, 4);

    sortStack(&s);

    while (!isEmptyStack(s)) {
        printf("%d ", peek(s));
        pop(&s);
    }

    return 0;
}

void sortStack(Stack *sPtr) {
    // initialise stack
    int temp;
    Stack sortingStack;
    sortingStack.size = 0;
    sortingStack.head = 0;

    // push onto stack 
    while (!isEmptyStack(sPtr)) {
        push(&sortingStack, pop(sPtr));
    }

    while (!isEmptyStack(sortingStack)) {
        temp = pop(&sortingStack);
        while (!isEmptyStack(sPtr) && temp > peek(sPtr)) {
            push(&sortingStack, pop(sPtr));
        }
        push(sPtr, temp);
    }
}