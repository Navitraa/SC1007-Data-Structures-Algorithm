
void recursiveReverse(Stack *s) {
    // Base case: empty stack or only ONE element => there is nothing to reverse
    if (isEmptyStack(s) || s->size == 1) {
        return;
    }

    // Recursive case: 
    int temp = peek(s);
    pop(s);
    recursiveReverse(s);
    pushToBottom(s, temp);
}

pushToBottom(Stack *s, int value) {
    // Base case: empty stack
    if (isEmptyStack(s)) {
        push(s, value);
    }
    else {
        int temp = peek(s);
        pop(s);
        push(s, value);
        push(s, temp);
    }
}