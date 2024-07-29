//leftist heap code for insertion and delete min element one by one  
//The null path length (npl) attribute associated with each node 
//represents the shortest distance to a null leaf node in its subtree. 

#include <stdio.h>
#include <stdlib.h>

// Define LeftistNode structure
typedef struct LeftistNode {
    int key;
    int npl; // Null Path Length
    struct LeftistNode *left;
    struct LeftistNode *right;
} LeftistNode;

// Function to create a new node
LeftistNode* createNode(int key) {
    LeftistNode* newNode = (LeftistNode*)malloc(sizeof(LeftistNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->key = key;
    newNode->npl = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to merge two Leftist Heaps
LeftistNode* merge(LeftistNode* x, LeftistNode* y) {
    if (x == NULL) return y;
    if (y == NULL) return x;

    if (x->key > y->key) {
        LeftistNode* temp = x;
        x = y;
        y = temp;
    }

    x->right = merge(x->right, y);

    if (x->left == NULL || (x->right != NULL && x->left->npl < x->right->npl)) {
        LeftistNode* temp = x->left;
        x->left = x->right;
        x->right = temp;
    }

    if (x->right == NULL) {
        x->npl = 0;
    } else {
        x->npl = x->right->npl + 1;
    }

    return x;
}

// Function to insert a new element into the Leftist Heap
LeftistNode* insert(LeftistNode* root, int key) {
    LeftistNode* newNode = createNode(key);
    return merge(root, newNode);
}

// Function to delete the minimum element from the Leftist Heap
LeftistNode* deleteMin(LeftistNode* root) {
    if (root == NULL) return NULL;
    LeftistNode* left = root->left;
    LeftistNode* right = root->right;
    free(root);
    return merge(left, right);
}

// Function to display the elements of the Leftist Heap
void display(LeftistNode* root) {
    if (root == NULL) return;
    printf("%d ", root->key);
    display(root->left);
    display(root->right);
}

int main() {
    LeftistNode* root = NULL;

    // Inserting elements in the given order
    int elements[] = {77, 22, 9, 68, 16, 34, 13, 8};
    int numElements = sizeof(elements) / sizeof(elements[0]);
    
    for (int i = 0; i < numElements; i++) {
        root = insert(root, elements[i]);
    }

    // Displaying the Leftist Heap after each deleteMin operation
    printf("Leftist Heap after insertions: ");
    display(root);
    printf("\n");

    printf("Deleting min element one by one:\n");
    for (int i = 0; i < numElements; i++) {
        root = deleteMin(root);
        printf("Leftist Heap after deleting min element: ");
        display(root);
        printf("\n");
    }

    return 0;
}
