#include <stdio.h>
#include <stdlib.h>

struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};

struct Stack {
    int top;
    unsigned capacity;
    int* array;
};

struct Queue* createQueue(unsigned capacity) {
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*) malloc(queue->capacity * sizeof(int));
    return queue;
}

struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*) malloc(stack->capacity * sizeof(int));
    return stack;
}

void enqueue(struct Queue* queue, int item) {
    if (queue->size == queue->capacity)
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

int dequeue(struct Queue* queue) {
    if (queue->size == 0)
        return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

void push(struct Stack* stack, int item) {
    if (stack->top == stack->capacity - 1)
        return;
    stack->array[++stack->top] = item;
}

int pop(struct Stack* stack) {
    if (stack->top == -1)
        return -1;
    return stack->array[stack->top--];
}

int top(struct Stack* stack) {
    if (stack->top == -1)
        return -1;
    return stack->array[stack->top];
}

int isEmpty(struct Queue* queue) {
    return queue->size == 0;
}

int checkSortedOrder(struct Queue* q) {
    int expected = 1;       //comparison
    struct Stack* s = createStack(q->capacity);
    struct Queue* sortedQueue = createQueue(q->capacity);

    while (q->size != 0) {
        int temp = dequeue(q);

        if (temp == expected) {
            enqueue(sortedQueue, temp);
            expected++;
        } else {
            if (s->top != -1 && top(s) < temp)
                return 0;

            push(s, temp);               //if not match then pushed into the stack
        }

        while (s->top != -1 && top(s) == expected) {
            enqueue(sortedQueue, temp = pop(s));
            expected++;
        }
    }

    if (expected - 1 == q->capacity && s->top == -1) {
        printf("Yes\n");
        printf("The rearranged order is: ");
        while (!isEmpty(sortedQueue)) {
            printf("%d ", dequeue(sortedQueue));
        }
        printf("\n");
        return 1;
    }

    return 0;
}

int main() {
    struct Queue* q = createQueue(5);
    enqueue(q, 5);
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);

    checkSortedOrder(q);
    return 0;
}
