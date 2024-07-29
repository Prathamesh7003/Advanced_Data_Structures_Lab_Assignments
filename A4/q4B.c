//trie
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie node structure
typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
} TrieNode;

// Function to create a new Trie node
TrieNode* createNode() {
    TrieNode* newNode = (TrieNode*)malloc(sizeof(TrieNode));
    newNode->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// Function to insert a word into the Trie
void insert(TrieNode* root, const char* word) {
    TrieNode* cur = root;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (cur->children[index] == NULL) {
            cur->children[index] = createNode();
        }
        cur = cur->children[index];
    }
    cur->isEndOfWord = true;
}

// Function to perform inorder traversal of the Trie
void inorderTraversal(TrieNode* root, char* buffer, int depth) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i] != NULL) {
            buffer[depth] = 'a' + i;
            if (root->children[i]->isEndOfWord) {
                buffer[depth + 1] = '\0';
                printf("%s\n", buffer);
            }
            inorderTraversal(root->children[i], buffer, depth + 1);
        }
    }
}

int main() {
    // Initialize the Trie
    TrieNode* root = createNode();

    // Ask the user to enter words
    printf("Enter words (type 'done' when finished):\n");
    char word[100];
    while (1) {
        scanf("%s", word);
        if (strcmp(word, "done") == 0) {
            break;
        }
        insert(root, word);
    }

    // Perform inorder traversal of the Trie to print the lexicographically sorted words
    printf("\nLexicographically sorted words:\n");
    char buffer[100];
    inorderTraversal(root, buffer, 0);

    return 0;
}
