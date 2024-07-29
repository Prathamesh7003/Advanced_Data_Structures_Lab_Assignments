//merge skew heap
#include<stdio.h>
#include<stdlib.h>

// Structure to represent a node in the skew heap
struct Node {
    int value;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* newNode(int value) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to merge two skew heaps
struct Node* merge(struct Node* heap1, struct Node* heap2) {
    // If one of the heaps is empty, return the other heap
    if (!heap1)
        return heap2;
    if (!heap2)
        return heap1;

    // Swap the children of heap1
    struct Node* temp = heap1->left;
    heap1->left = heap1->right;
    heap1->right = temp;

    // Recursively merge the right child of heap1 with heap2
    heap1->right = merge(heap1->right, heap2);

    // Return heap1
    return heap1;
}

// Function to print the skew heap
void printHeap(struct Node* root) {
    if (root) {
        printf("%d ", root->value);
        printHeap(root->left);
        printHeap(root->right);
    }
}

int main() {
    // Constructing the first skew heap
    struct Node* heap1 = newNode(2);
    heap1->left = newNode(4);
    heap1->right = newNode(22);

    // Constructing the second skew heap
    struct Node* heap2 = newNode(12);
    heap2->left = newNode(18);
    heap2->right = newNode(90);

    // Merging the two skew heaps
    struct Node* mergedHeap = merge(heap1, heap2);

    // Printing the merged skew heap
    printf("Merged Skew Heap: ");
    printHeap(mergedHeap);
    printf("\n");

    return 0;
}
