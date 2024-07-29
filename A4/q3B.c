//skip list search
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
    newNode->val = val;
    newNode->next = NULL;
    newNode->jump = NULL;
    newNode->down = NULL;
    return newNode;
}

// Function to insert a new node into the skip list
void insert(ListNode** head, int val) {
    ListNode* cur = *head;

    // Traverse the levels of the skip list
    while (cur != NULL) {
        // Find the insertion point in the current level
        while (cur->next != NULL && cur->next->val < val) {
            cur = cur->next;
        }

        // Insert the new node at the current level
        ListNode* newNode = createNode(val);
        newNode->next = cur->next;
        cur->next = newNode;

        // Move to the next level down with probability 0.5
        if (rand() % 2 == 0) {
            // If there is no level below, create one
            if (cur->down == NULL) {
                cur->down = createNode(val);
                cur->down->next = newNode;
            }
            cur = cur->down;
        } else {
            break; // Stop traversing levels
        }
    }
}

// Function to search for an element in the skip list
ListNode* search(ListNode* head, int val) {
    ListNode* cur = head;
    while (cur != NULL) {
        while (cur->next != NULL && cur->next->val <= val) {
            cur = cur->next;
        }
        if (cur->val == val) {
            return cur;
        }
        cur = cur->down;
    }
    return NULL;
}

int main() {
    srand(time(0)); // Seed for random number generation

    // Create a skip list representation of the linked list
    ListNode* head = createNode(-1); // Sentinel node
    head->next = createNode(2);
    head->next->next = createNode(5);
    head->next->next->next = createNode(8);
    head->next->next->next->next = createNode(12);
    head->next->next->next->next->next = createNode(15);

    // Insert nodes into the skip list
    insert(&head, 2);
    insert(&head, 5);
    insert(&head, 8);
    insert(&head, 12);
    insert(&head, 15);

    // Search for values in the skip list
    int search_values[] = {14, 12};
    int num_search_values = sizeof(search_values) / sizeof(search_values[0]);

    printf("Searching for values in the skip list:\n");
    for (int i = 0; i < num_search_values; i++) {
        ListNode* result = search(head, search_values[i]);
        if (result != NULL) {
            printf("%d is found in the skip list.\n", search_values[i]);
        } else {
            printf("%d is not found in the skip list.\n", search_values[i]);
        }
    }

    return 0;
}
