#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge in the graph
struct Edge
{
    int src, dest, weight;
};

// Structure to represent a subset for union-find
struct Subset
{
    int parent;
    int rank;
};

// Function to find the set of an element i (uses path compression)
int find(struct Subset subsets[], int i)
{
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Function to perform union of two sets of x and y (uses union by rank)
void Union(struct Subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Function to compare two edges based on their weights for sorting
int compareEdges(const void *a, const void *b)
{
    return ((struct Edge *)a)->weight - ((struct Edge *)b)->weight;
}

// Function to apply Kruskal's algorithm and print the minimum spanning tree
void kruskalMST(struct Edge *edges, int numVertices, int numEdges)
{
    struct Edge result[numVertices]; // to store the result
    int e = 0;                       // index for the result array
    int i = 0;                       // index for the sorted edges array

    // Sort all the edges in non-decreasing order of their weights
    qsort(edges, numEdges, sizeof(edges[0]), compareEdges);

    // Allocate memory for creating subsets
    struct Subset *subsets = (struct Subset *)malloc(numVertices * sizeof(struct Subset));

    // Create subsets with single elements
    for (int v = 0; v < numVertices; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Number of edges to be taken is equal to numVertices-1
    while (e < numVertices - 1 && i < numEdges)
    {
        // Pick the smallest edge
        struct Edge nextEdge = edges[i++];

        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        // If including this edge does not cause a cycle, include it in the result
        if (x != y)
        {
            result[e++] = nextEdge;
            Union(subsets, x, y);
        }
    }

    // Display the selected edges and their costs
    printf("Edge Cost\n");
    for (int j = 0; j < e; ++j)
    {
        printf("%d--%d %d\n", result[j].src + 1, result[j].dest + 1, result[j].weight);
    }

    // Calculate and display the total cost of the minimum spanning tree
    int totalWeight = 0;
    for (int j = 0; j < e; ++j)
    {
        totalWeight += result[j].weight;
    }
    printf("Total Weight of the Minimum Spanning Tree: %d\n", totalWeight);

    // Free allocated memory
    free(subsets);
}

int main()
{
    int numVertices, numEdges;

    // Get the number of vertices and edges
    printf("Enter the Number of Vertices and Edges: ");
    scanf("%d %d", &numVertices, &numEdges);

    struct Edge *edges = (struct Edge *)malloc(numEdges * sizeof(struct Edge));

    // Get the edges from the user
    printf("Enter the Edges (src dest weight):\n");
    for (int i = 0; i < numEdges; ++i)
    {
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
        edges[i].src--;
        edges[i].dest--;
    }

    // Apply Kruskal's algorithm and display the result
    kruskalMST(edges, numVertices, numEdges);

    // Free allocated memory
    free(edges);

    return 0;
}
