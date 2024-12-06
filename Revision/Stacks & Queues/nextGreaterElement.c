
int *nextGreaterElement(int *arr, int n) {

    int* result = (int*) malloc(n * sizeof(int));
    Stack s;
    s.size = 0;
    s.head = NULL;

    // Special case: 0 elements in array
    if (n == 0) {
        return -1;
    }

    // Special case: 1 element in array
    if (n == 1) {
        result[0] = 0;
        return result;
    }

    int greaterElement = arr[0];
    // the ones with nextGreaterElement
    for (int i = 0; i < n; i++) {
        while (!isEmptyStack(s) && arr[i] > arr[peak(s)]) {
            int index = peak(s);
            result[index] = arr[i];
            pop(&s);
        }
        push(&s, i);
    }
    // the ones which get replaced with -1
    while (!isEmptyStack(s)) {
        int index = peak(s);
        result[index] = -1;
        pop(&s);
    }

    deleteStack(&s);
    return result;
}


/* if (arr[i] < greaterElement) {
            result[i] = arr[i];
        }
        else if (arr[i] > greaterElement) {
            greaterElement = arr[i];
        }