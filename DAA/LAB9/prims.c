#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

// Structure to represent a node in the Min-Heap
struct MinHeapNode
{
    int vertex;
    int key;
};

// Structure to represent the Min-Heap
struct MinHeap
{
    int size;
    int capacity;
    int *pos;
    struct MinHeapNode **array;
};

// Structure to represent an edge in the graph
struct Edge
{
    int src, dest, weight;
};

// Structure to represent a graph
struct Graph
{
    int numVertices;
    int **adjacencyMatrix;
};

// Function to create a new Min-Heap node
struct MinHeapNode *createMinHeapNode(int vertex, int key)
{
    struct MinHeapNode *minHeapNode = (struct MinHeapNode *)malloc(sizeof(struct MinHeapNode));
    minHeapNode->vertex = vertex;
    minHeapNode->key = key;
    return minHeapNode;
}

// Function to create a Min-Heap
struct MinHeap *createMinHeap(int capacity)
{
    struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode **)malloc(capacity * sizeof(struct MinHeapNode *));
    return minHeap;
}

// Function to swap two Min-Heap nodes
void swapMinHeapNode(struct MinHeapNode **a, struct MinHeapNode **b)
{
    struct MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}

// Function to heapify at a given index
void minHeapify(struct MinHeap *minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->key < minHeap->array[smallest]->key)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->key < minHeap->array[smallest]->key)
        smallest = right;

    if (smallest != idx)
    {
        struct MinHeapNode *smallestNode = minHeap->array[smallest];
        struct MinHeapNode *idxNode = minHeap->array[idx];

        minHeap->pos[smallestNode->vertex] = idx;
        minHeap->pos[idxNode->vertex] = smallest;

        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

// Function to check if the Min-Heap is empty
int isEmpty(struct MinHeap *minHeap)
{
    return minHeap->size == 0;
}

// Function to extract the minimum node from the Min-Heap
struct MinHeapNode *extractMin(struct MinHeap *minHeap)
{
    if (isEmpty(minHeap))
        return NULL;

    struct MinHeapNode *root = minHeap->array[0];
    struct MinHeapNode *lastNode = minHeap->array[minHeap->size - 1];

    minHeap->array[0] = lastNode;

    minHeap->pos[root->vertex] = minHeap->size - 1;
    minHeap->pos[lastNode->vertex] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

// Function to decrease the key value of a given vertex
void decreaseKey(struct MinHeap *minHeap, int vertex, int key)
{
    int i = minHeap->pos[vertex];

    minHeap->array[i]->key = key;

    while (i > 0 && minHeap->array[i]->key < minHeap->array[(i - 1) / 2]->key)
    {
        minHeap->pos[minHeap->array[i]->vertex] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->vertex] = i;

        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }
}

// Function to check if a given vertex is in the Min-Heap
int isInMinHeap(struct MinHeap *minHeap, int vertex)
{
    return minHeap->pos[vertex] < minHeap->size;
}

// Function to print the cost adjacency matrix of the minimum spanning tree
void printMSTCostMatrix(int **costMatrix, int numVertices)
{
    printf("Cost Adjacency Matrix of Minimum Spanning Tree:\n");
    for (int i = 0; i < numVertices; ++i)
    {
        for (int j = 0; j < numVertices; ++j)
            printf("%d ", costMatrix[i][j]);
        printf("\n");
    }
}

// Function to find the minimum spanning tree using Prim's algorithm
void primMST(struct Graph *graph, int startVertex)
{
    int numVertices = graph->numVertices;
    int **costMatrix = (int **)malloc(numVertices * sizeof(int *));
    for (int i = 0; i < numVertices; ++i)
        costMatrix[i] = (int *)malloc(numVertices * sizeof(int));

    struct MinHeap *minHeap = createMinHeap(numVertices);
    struct MinHeapNode *heapNodes[numVertices];

    for (int v = 0; v < numVertices; ++v)
    {
        heapNodes[v] = createMinHeapNode(v, INT_MAX);
        minHeap->array[v] = heapNodes[v];
        minHeap->pos[v] = v;
    }

    minHeap->array[startVertex]->key = 0;
    decreaseKey(minHeap, startVertex, 0);

    while (!isEmpty(minHeap))
    {
        struct MinHeapNode *minHeapNode = extractMin(minHeap);
        int u = minHeapNode->vertex;

        for (int v = 0; v < numVertices; ++v)
        {
            if (graph->adjacencyMatrix[u][v] && isInMinHeap(minHeap, v) && graph->adjacencyMatrix[u][v] < heapNodes[v]->key)
            {
                heapNodes[v]->key = graph->adjacencyMatrix[u][v];
                decreaseKey(minHeap, v, graph->adjacencyMatrix[u][v]);
                costMatrix[u][v] = graph->adjacencyMatrix[u][v];
                costMatrix[v][u] = graph->adjacencyMatrix[u][v];
            }
        }
    }

    // Display the cost adjacency matrix of the minimum spanning tree
    printMSTCostMatrix(costMatrix, numVertices);

    // Calculate and display the total cost of the minimum spanning tree
    int totalCost = 0;
    for (int i = 0; i < numVertices; ++i)
    {
        for (int j = i + 1; j < numVertices; ++j)
        {
            if (costMatrix[i][j] != 0)
                totalCost += costMatrix[i][j];
        }
    }
    printf("Total Weight of the Minimum Spanning Tree: %d\n", totalCost);

    // Free allocated memory
    for (int i = 0; i < numVertices; ++i)
        free(costMatrix[i]);
    free(costMatrix);
    free(minHeap->pos);
    free(minHeap->array);
    free(minHeap);
}

// Function to read the graph from an input file
struct Graph *readGraphFromFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    int numVertices;
    fscanf(file, "%d", &numVertices);

    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;

    graph->adjacencyMatrix = (int **)malloc(numVertices * sizeof(int *));
    for (int i = 0; i < numVertices; ++i)
    {
        graph->adjacencyMatrix[i] = (int *)malloc(numVertices * sizeof(int));
        for (int j = 0; j < numVertices; ++j)
            fscanf(file, "%d", &graph->adjacencyMatrix[i][j]);
    }

    fclose(file);

    return graph;
}

int main()
{
    // Read the graph from the input file
    const char *filename = "inUnAdjMat.dat";
    struct Graph *graph = readGraphFromFile(filename);

    int startVertex;
    printf("Enter the Starting Vertex: ");
    scanf("%d", &startVertex);
    startVertex--;

    // Apply Prim's algorithm and display the result
    primMST(graph, startVertex);

    // Free allocated memory
    for (int i = 0; i < graph->numVertices; ++i)
        free(graph->adjacencyMatrix[i]);
    free(graph->adjacencyMatrix);
    free(graph);

    return 0;
}
