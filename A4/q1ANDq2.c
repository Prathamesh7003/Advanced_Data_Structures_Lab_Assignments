//splay tree insertion and deletion

#include <stdio.h>
#include <stdlib.h>

// Define structure for a splay tree node
typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

// Create a new splay tree node
Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

// Perform a right rotation
Node* rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// Perform a left rotation
Node* leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Perform splay operation
Node* splay(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    // Key lies in left subtree
    if (key < root->key) {
        if (root->left == NULL)
            return root;

        // Zig-zig (left left)
        if (key < root->left->key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        // Zig-zag (left right)
        else if (key > root->left->key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }

        // Perform second rotation
        return (root->left == NULL) ? root : rightRotate(root);
    }
    // Key lies in right subtree
    else {
        if (root->right == NULL)
            return root;

        // Zag-zig (right left)
        if (key < root->right->key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        // Zag-zag (right right)
        else if (key > root->right->key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }

        // Perform second rotation
        return (root->right == NULL) ? root : leftRotate(root);
    }
}

// Insert a new node with the given key
Node* insert(Node* root, int key) {
    // If the tree is empty, return a new node
    if (root == NULL)
        return newNode(key);

    // Perform splay on the root
    root = splay(root, key);

    // If key is already present, return root
    if (root->key == key)
        return root;

    // Otherwise, allocate memory for the new node
    Node* newnode = newNode(key);

    // If key is greater than root's key, set right child of root
    if (root->key < key) {
        newnode->left = root;
        newnode->right = root->right;
        root->right = NULL;
    }
    // If key is smaller than root's key, set left child of root
    else {
        newnode->right = root;
        newnode->left = root->left;
        root->left = NULL;
    }

    return newnode;
}

// Function to find the node with the maximum key in the given tree
Node* findMax(Node* root) {
    if (root == NULL)
        return NULL;
    while (root->right != NULL)
        root = root->right;
    return root;
}

// Delete a node with the given key from the tree
Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return NULL;

    // Perform splay on the root
    root = splay(root, key);

    // If key is not present in the tree, return root
    if (root->key != key)
        return root;

    // If key is present, then remove it
    Node* temp;
    if (root->left == NULL) {
        temp = root;
        root = root->right;
    } else {
        temp = root;
        root = splay(root->left, key);
        root->right = temp->right;
    }
    free(temp);
    return root;
}

// Inorder traversal of the tree
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Main function
int main() {
    Node* root = NULL;

    // Inserting elements into an empty splay tree
    int keys[] = {20, 10, 30, 40, 45, 56, 70};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        printf("Inserting key %d\n", keys[i]);
        root = insert(root, keys[i]);
        printf("Splay tree after inserting %d: ", keys[i]);
        inorder(root);
        printf("\n\n");
    }

    // Deleting elements from the splay tree
    int del_keys[] = {10, 30, 45};
    int del_n = sizeof(del_keys) / sizeof(del_keys[0]);

    for (int i = 0; i < del_n; i++) {
        printf("Deleting key %d\n", del_keys[i]);
        root = deleteNode(root, del_keys[i]);
        printf("Splay tree after deleting %d: ", del_keys[i]);
        inorder(root);
        printf("\n\n");
    }

    return 0;
}
