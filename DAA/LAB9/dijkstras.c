#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Structure to represent a graph
struct Graph
{
    int numVertices;
    int **adjacencyMatrix;
};

// Function to create a new graph with a given number of vertices
struct Graph *createGraph(int vertices)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjacencyMatrix = (int **)malloc(vertices * sizeof(int *));
    for (int i = 0; i < vertices; ++i)
    {
        graph->adjacencyMatrix[i] = (int *)malloc(vertices * sizeof(int));
    }

    return graph;
}

// Function to free the memory allocated for the graph
void freeGraph(struct Graph *graph)
{
    for (int i = 0; i < graph->numVertices; ++i)
    {
        free(graph->adjacencyMatrix[i]);
    }
    free(graph->adjacencyMatrix);
    free(graph);
}

// Function to find the vertex with the minimum distance value, from the set of vertices
// not yet included in the shortest path tree
int minDistance(int distance[], bool sptSet[], int numVertices)
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < numVertices; ++v)
    {
        if (!sptSet[v] && distance[v] <= min)
        {
            min = distance[v];
            min_index = v;
        }
    }

    return min_index;
}

// Function to display the shortest paths from the source vertex
void displayShortestPaths(int source, int distance[], int parent[], int numVertices)
{
    printf("Source Destination Cost Path\n");

    for (int i = 0; i < numVertices; ++i)
    {
        if (i != source)
        {
            printf("%d\t%d\t%d\t%d", source + 1, i + 1, distance[i], source + 1);

            int j = i;
            while (parent[j] != -1)
            {
                printf("->%d", parent[j] + 1);
                j = parent[j];
            }

            printf("\n");
        }
    }
}

// Function to implement Dijkstra's algorithm to find the shortest paths
void dijkstra(struct Graph *graph, int source)
{
    int numVertices = graph->numVertices;
    int distance[numVertices]; // To store the shortest distance from source to i
    bool sptSet[numVertices];  // To keep track of vertices included in the shortest path tree
    int parent[numVertices];   // To store the parent nodes for constructing the path

    // Initialize all distances as INFINITE and sptSet[] as false
    for (int i = 0; i < numVertices; ++i)
    {
        distance[i] = INT_MAX;
        sptSet[i] = false;
        parent[i] = -1;
    }

    // Distance from the source vertex to itself is always 0
    distance[source] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < numVertices - 1; ++count)
    {
        int u = minDistance(distance, sptSet, numVertices);

        sptSet[u] = true;

        // Update distance value of the adjacent vertices of the picked vertex
        for (int v = 0; v < numVertices; ++v)
        {
            if (!sptSet[v] && graph->adjacencyMatrix[u][v] && distance[u] != INT_MAX &&
                distance[u] + graph->adjacencyMatrix[u][v] < distance[v])
            {
                distance[v] = distance[u] + graph->adjacencyMatrix[u][v];
                parent[v] = u;
            }
        }
    }

    // Display the shortest paths
    displayShortestPaths(source, distance, parent, numVertices);
}

int main()
{
    int numVertices;

    // Read the graph from the input file
    FILE *file = fopen("inDiAdjMat1.dat", "r");
    if (!file)
    {
        printf("Error opening file inDiAdjMat1.dat\n");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", &numVertices);

    // Create the graph
    struct Graph *graph = createGraph(numVertices);

    // Read the adjacency matrix from the file
    for (int i = 0; i < numVertices; ++i)
    {
        for (int j = 0; j < numVertices; ++j)
        {
            fscanf(file, "%d", &graph->adjacencyMatrix[i][j]);
        }
    }

    fclose(file);

    // Get the source vertex from the user
    int source;
    printf("Enter the Source Vertex: ");
    scanf("%d", &source);
    source--;

    // Apply Dijkstra's algorithm and display the result
    dijkstra(graph, source);

    // Free allocated memory
    freeGraph(graph);

    return 0;
}
