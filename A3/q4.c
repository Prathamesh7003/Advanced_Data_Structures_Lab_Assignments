//dijiksra using binomial heap
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 1000

// Structure to represent a node in the graph
typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

// Structure to represent the graph
typedef struct Graph {
    int num_vertices;
    Node* adj_list[MAX_VERTICES];
} Graph;

// Structure to represent a node in the binomial heap
typedef struct BinomialNode {
    int vertex;
    int distance;
} BinomialNode;

// Structure to represent the binomial heap
typedef struct BinomialHeap {
    int size;
    BinomialNode* nodes[MAX_VERTICES];
} BinomialHeap;

// Function to create a new node
Node* createNode(int vertex, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with given number of vertices
Graph* createGraph(int num_vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->num_vertices = num_vertices;
    for (int i = 0; i < num_vertices; i++) {
        graph->adj_list[i] = NULL;
    }
    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest, int weight) {
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->adj_list[src];
    graph->adj_list[src] = newNode;
}

// Function to create a new binomial node
BinomialNode* createBinomialNode(int vertex, int distance) {
    BinomialNode* newNode = (BinomialNode*)malloc(sizeof(BinomialNode));
    newNode->vertex = vertex;
    newNode->distance = distance;
    return newNode;
}

// Function to create a new binomial heap
BinomialHeap* createBinomialHeap() {
    BinomialHeap* heap = (BinomialHeap*)malloc(sizeof(BinomialHeap));
    heap->size = 0;
    return heap;
}

// Function to swap two binomial nodes
void swap(BinomialNode** a, BinomialNode** b) {
    BinomialNode* temp = *a;
    *a = *b;
    *b = temp;
}

// Function to maintain the heap property of the binomial heap
void heapify(BinomialHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->nodes[left]->distance < heap->nodes[smallest]->distance)
        smallest = left;

    if (right < heap->size && heap->nodes[right]->distance < heap->nodes[smallest]->distance)
        smallest = right;

    if (smallest != idx) {
        swap(&heap->nodes[smallest], &heap->nodes[idx]);
        heapify(heap, smallest);
    }
}

// Function to extract the minimum node from the binomial heap
BinomialNode* extractMin(BinomialHeap* heap) {
    if (heap->size == 0)
        return NULL;

    BinomialNode* minNode = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size--;
    heapify(heap, 0);

    return minNode;
}

// Function to decrease the distance of a vertex in the binomial heap
void decreaseKey(BinomialHeap* heap, int vertex, int new_distance) {
    int i;
    for (i = 0; i < heap->size; i++) {
        if (heap->nodes[i]->vertex == vertex) {
            heap->nodes[i]->distance = new_distance;
            break;
        }
    }

    while (i != 0 && heap->nodes[(i - 1) / 2]->distance > heap->nodes[i]->distance) {
        swap(&heap->nodes[i], &heap->nodes[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Function to check if the binomial heap is empty
bool isEmpty(BinomialHeap* heap) {
    return heap->size == 0;
}

// Dijkstra's algorithm using binomial heap
void dijkstra(Graph* graph, int start) {
    int distances[MAX_VERTICES];
    BinomialHeap* heap = createBinomialHeap();

    for (int i = 0; i < graph->num_vertices; i++) {
        distances[i] = INT_MAX;
        heap->nodes[i] = createBinomialNode(i, INT_MAX);
    }

    heap->nodes[start]->distance = 0;
    distances[start] = 0;
    heap->size = graph->num_vertices;

    while (!isEmpty(heap)) {
        BinomialNode* minNode = extractMin(heap);
        int u = minNode->vertex;

        Node* temp = graph->adj_list[u];
        while (temp != NULL) {
            int v = temp->vertex;
            int weight = temp->weight;

            if (distances[u] != INT_MAX && distances[v] > distances[u] + weight) {
                distances[v] = distances[u] + weight;
                decreaseKey(heap, v, distances[v]);
            }
            temp = temp->next;
        }
    }

    printf("Shortest distances from vertex %d: \n", start);
    for (int i = 0; i < graph->num_vertices; i++) {
        printf("Vertex %d: Distance %d\n", i, distances[i]);
    }
}

int main() {
    int num_vertices = 4;
    Graph* graph = createGraph(num_vertices);
    addEdge(graph, 0, 1, 1);
    addEdge(graph, 0, 2, 4);
    addEdge(graph, 1, 2, 2);
    addEdge(graph, 1, 3, 5);
    addEdge(graph, 2, 3, 1);

    int start_vertex = 0;
    dijkstra(graph, start_vertex);

    return 0;
}
