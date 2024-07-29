#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure for a skip list node
typedef struct ListNode {
    int val;
    struct ListNode* next;
    struct ListNode* jump; // Jump pointer for skip list
    struct ListNode* down; // Pointer to the node in the next level down
} ListNode;

// Function to create a new node
ListNode* createNode(int val) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->val = val;
    newNode->next = NULL;
    newNode->jump = NULL;
    newNode->down = NULL;
    return newNode;
}

// Function to insert a new node into the skip list
void insert(ListNode** head, int val) {
    // Check whether the value is already in the list; abort if found
    ListNode* cur = *head;
    while (cur != NULL) {
        if (cur->val == val) {
            printf("Error: Value already exists in the list.\n");
            return;
        }
        cur = cur->down; // Move to the next level down
    }

    // Flip coins to determine the insertion height
    int height = 0;
    while (rand() % 2 == 0) {
        height++;
    }

    // If necessary, increase sentinel height until it is one greater than the insertion height
    while (height > 0 && (*head)->down == NULL) {
        ListNode* newHead = createNode(-1); // Create a new sentinel node
        newHead->down = *head; // Link it to the current head
        *head = newHead; // Update the head
        height--;
    }

    // Initialize cur to be the head of the list
    cur = *head;

    // Create an array to keep track of nodes at each level where insertion happens
    ListNode* update[height + 1];
    for (int i = 0; i <= height; i++) {
        update[i] = NULL;
    }

    // Traverse through the levels of the skip list
    while (cur != NULL) {
        // Find the possible insertion point at this level
        while (cur->next != NULL && cur->next->val < val) {
            cur = cur->next;
        }
        // Store the node where insertion will happen at this level
        update[height] = cur;

        // Move to the next lower level
        cur = cur->down;
        height--;
    }

    // Insert nodes at each level
    for (int i = 0; i <= height; i++) {
        ListNode* newNode = createNode(val);
        newNode->next = update[i]->next;
        update[i]->next = newNode;

        // Link the node to the level below
        if (i > 0) {
            newNode->down = update[i - 1]->next;
        }
    }
}

// Function to print the skip list
void printSkipList(ListNode* head) {
    ListNode* cur = head;
    while (cur->down != NULL) {
        cur = cur->down;
    }

    // Traverse from the bottom level to the top
    while (cur != NULL) {
        ListNode* levelCur = cur;
        while (levelCur != NULL) {
            printf("%d -> ", levelCur->val);
            levelCur = levelCur->next;
        }
        printf("NULL\n");
        cur = cur->next;
    }
}

// Function to free memory allocated for the skip list
void freeSkipList(ListNode* head) {
    ListNode* cur = head;
    while (cur != NULL) {
        ListNode* temp = cur;
        cur = cur->down;
        ListNode* del = temp;
        while (del != NULL) {
            ListNode* tempDel = del;
            del = del->next;
            free(tempDel);
        }
    }
}

int main() {
    srand(time(0)); // Seed for random number generation

    // Create the linked list representation provided
    ListNode* head = createNode(-1); // Sentinel node
    head->next = createNode(2);
    head->next->next = createNode(5);
    head->next->next->next = createNode(8);
    head->next->next->next->next = createNode(12);
    head->next->next->next->next->next = createNode(15);

    // Print the original linked list representation for verification
    printf("Original Linked List Representation:\n");
    ListNode* cur = head->next; // Skip the sentinel node
    while (cur != NULL) {
        printf("%d -> ", cur->val);
        cur = cur->next;
    }
    printf("NULL\n");

    // Insert nodes into the skip list
    insert(&head, 2);
    insert(&head, 5);
    insert(&head, 8);
    insert(&head, 12);
    insert(&head, 15);

    // Print the skip list
    printf("Skip List Representation:\n");
    printSkipList(head);

    // Free memory allocated for the skip list
    freeSkipList(head);

    return 0;
}
