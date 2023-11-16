#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent an edge in the graph
struct Edge
{
    int src, dest;
};

// Structure to represent a node in the adjacency list
struct Node
{
    int vertex;
    struct Node *next;
};

// Structure to represent the adjacency list for each vertex
struct Graph
{
    int numVertices;
    struct Node **adjLists;
};

// Function to create a new graph with a given number of vertices
struct Graph *createGraph(int vertices)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjLists = (struct Node **)malloc(vertices * sizeof(struct Node *));

    for (int i = 0; i < vertices; ++i)
    {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(struct Graph *graph, int src, int dest)
{
    // Add edge from src to dest
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->vertex = dest;
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add edge from dest to src (since it's an undirected graph)
    newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->vertex = src;
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Function to perform breadth-first search and calculate distances
int *BFS(struct Graph *graph, int startVertex)
{
    int *distances = (int *)malloc(graph->numVertices * sizeof(int));

    // Mark all vertices as not visited
    bool *visited = (bool *)malloc(graph->numVertices * sizeof(bool));
    for (int i = 0; i < graph->numVertices; ++i)
    {
        visited[i] = false;
        distances[i] = -1; // Initialize distances to -1
    }

    // Create a queue for BFS
    int *queue = (int *)malloc(graph->numVertices * sizeof(int));
    int front = -1, rear = -1;

    // Mark the current node as visited and enqueue it
    visited[startVertex] = true;
    queue[++rear] = startVertex;
    distances[startVertex] = 0;

    while (front != rear)
    {
        // Dequeue a vertex from the queue
        int currentVertex = queue[++front];

        // Traverse the adjacency list of the dequeued vertex
        struct Node *temp = graph->adjLists[currentVertex];
        while (temp)
        {
            int adjVertex = temp->vertex;

            // If the adjacent vertex is not visited, mark it visited and enqueue it
            if (!visited[adjVertex])
            {
                visited[adjVertex] = true;
                queue[++rear] = adjVertex;
                distances[adjVertex] = distances[currentVertex] + 2; // Assuming edge weight is 2
            }

            temp = temp->next;
        }
    }

    free(visited);
    free(queue);

    return distances;
}

// Function to display BFS traversal
void displayBFS(struct Graph *graph, int startVertex)
{
    printf("Breadth-First Search Traversal from Node %d:\n", startVertex);

    // Perform BFS and get distances
    int *distances = BFS(graph, startVertex);

    // Display the traversal
    for (int i = 0; i < graph->numVertices; ++i)
    {
        printf("%d ", i + 1);
    }

    printf("\n");

    // Display the distances
    printf("Shortest Distances from Node %d:\n", startVertex);
    for (int i = 0; i < graph->numVertices; ++i)
    {
        printf("Node %d: %d\n", i + 1, distances[i]);
    }

    free(distances);
}

int main()
{
    int numVertices, numEdges;

    // Get the number of vertices and edges
    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    // Create the graph
    struct Graph *graph = createGraph(numVertices);

    // Get the edges from the user
    printf("Enter the edges (as pairs of vertices):\n");
    for (int i = 0; i < numEdges; ++i)
    {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src - 1, dest - 1);
    }

    // Get the starting node for BFS
    int startVertex;
    printf("Enter the starting node for BFS: ");
    scanf("%d", &startVertex);

    // Display BFS traversal and shortest distances
    displayBFS(graph, startVertex - 1);

    // Free allocated memory
    for (int i = 0; i < numVertices; ++i)
    {
        struct Node *temp = graph->adjLists[i];
        while (temp)
        {
            struct Node *prev = temp;
            temp = temp->next;
            free(prev);
        }
    }

    free(graph->adjLists);
    free(graph);

    return 0;
}
