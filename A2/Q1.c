#include <stdio.h>
#include <stdlib.h>

struct Stack {
    int top;
    unsigned capacity;
    int* array;
};

struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*) malloc(stack->capacity * sizeof(int));
    return stack;
}

int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, int item) {
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

int pop(struct Stack* stack) {
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->top--];
}

int top(struct Stack* stack) {
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->top];
}

struct QNode {
    int key;
    struct QNode* next;
};

struct Queue {
    struct QNode *front, *rear;
    int size;  // Add size field to the Queue structure
};

struct QNode* newNode(int k)
{
    struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
    temp->key = k;
    temp->next = NULL;
    return temp;
}

struct Queue* createQueue()
{
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    q->size = 0;  // Initialize size to 0
    return q;
}

void enQueue(struct Queue* q, int k)
{
    struct QNode* temp = newNode(k);
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        q->size = 1;  // Update size
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
    q->size++;  // Update size
}

void deQueue(struct Queue* q)
{
    if (q->front == NULL)
        return;
    struct QNode* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    q->size--;  // Update size
}

int front(struct Queue* q)
{
    if (q->front == NULL)
        return -1;
    return q->front->key;
}

int size(struct Queue* q)
{
    return q->size;
}

void reverseQueueFirstKElements(int k, struct Queue* q)
{
    if (q->front == NULL || k > q->size)        //k=no_of_elements
        return;
    if (k <= 0) 
        return;
    struct Stack* stack = createStack(k);
    for (int i = 0; i < k; i++) {
        push(stack, front(q));
        deQueue(q);
    }
    while (!isEmpty(stack)) {
        enQueue(q, top(stack));
        pop(stack);
    }
    // Remaining elements of original queue are then moved to the end of the queue
    for (int i = 0; i < size(q) - k; i++) {
        enQueue(q, front(q));
        deQueue(q);
    }
}
void printQueue(struct Queue* q) {
    struct QNode* temp = q->front;
    while (temp != NULL) {
        printf("%d ", temp->key);
        temp = temp->next;
    }
}

int main() {
    struct Queue* q = createQueue();
    enQueue(q, 1);
    enQueue(q, 2);
    enQueue(q, 3);
    enQueue(q, 4);
    enQueue(q, 5);
    enQueue(q, 6);
    enQueue(q, 7);
    enQueue(q, 8);
    enQueue(q, 9);
    enQueue(q, 10);

    printf("Original queue: ");
    printQueue(q);

    int k = 5;
    reverseQueueFirstKElements(k, q);

    printf("\nQueue after reversing first %d elements: ", k);
    printQueue(q);
    printf("\n");

    return 0;
}
