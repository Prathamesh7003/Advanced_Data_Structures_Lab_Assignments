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

// Function to count the number of children of a Trie node
int countChildren(TrieNode* node) {
    int count = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            count++;
        }
    }
    return count;
}

// Function to find the longest common prefix
char* longestCommonPrefix(TrieNode* root) {
    TrieNode* cur = root;
    char* prefix = (char*)malloc(sizeof(char) * 100);
    int index = 0;

    // Traverse the Trie until we encounter a node with more than one child
    while (cur != NULL && countChildren(cur) == 1 && !cur->isEndOfWord) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (cur->children[i] != NULL) {
                prefix[index++] = 'a' + i;
                cur = cur->children[i];
                break;
            }
        }
    }

    prefix[index] = '\0';
    return prefix;
}

// Function to perform preorder traversal of the Trie
void preorderTraversal(TrieNode* root, char* buffer, int depth) {
    if (root == NULL) {
        return;
    }
    if (root->isEndOfWord) {
        buffer[depth] = '\0';
        printf("%s\n", buffer);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i] != NULL) {
            buffer[depth] = 'a' + i;
            preorderTraversal(root->children[i], buffer, depth + 1);
        }
    }
}

int main() {
    // Initialize the Trie
    TrieNode* root = createNode();

    // Insert words into the Trie
    const char* words[] = {"Cancellation", "cancel", "Canada", "canabary", "can", "cando"};
    int numWords = sizeof(words) / sizeof(words[0]);
    for (int i = 0; i < numWords; i++) {
        insert(root, words[i]);
    }

    // Find the longest common prefix
    char* commonPrefix = longestCommonPrefix(root);
    printf("Longest Common Prefix: %s\n", commonPrefix);

    // Perform preorder traversal of the Trie
    printf("\nWords in lexicographically increasing order:\n");
    char buffer[100];
    preorderTraversal(root, buffer, 0);

    return 0;
}
