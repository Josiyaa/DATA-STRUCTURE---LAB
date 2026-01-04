#include <stdio.h>
#include <stdlib.h>

/* ================= DISJOINT SET ================= */

typedef struct {
    int parent;
    int rank;
} Subset;

/* Find with Path Compression */
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

/* Union by Rank */
void unionSet(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (xroot == yroot)
        return;

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

/* ================= GRAPH ================= */

typedef struct {
    int src, dest, weight;
} Edge;

typedef struct {
    int V, E;
    Edge* edges;
} Graph;

Graph* createGraph(int V, int E) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (Edge*)malloc(E * sizeof(Edge));
    return graph;
}

/* Compare function for qsort */
int compareEdges(const void* a, const void* b) {
    Edge* e1 = (Edge*)a;
    Edge* e2 = (Edge*)b;
    return e1->weight - e2->weight;
}

/* ================= KRUSKAL ================= */

void kruskalMST(Graph* graph) {
    int V = graph->V;
    Edge result[V - 1];  // Store MST edges
    int e = 0;           // Number of edges in MST
    int i = 0;           // Index for sorted edges

    /* Sort edges by weight */
    qsort(graph->edges, graph->E, sizeof(Edge), compareEdges);

    Subset* subsets = (Subset*)malloc(V * sizeof(Subset));

    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1 && i < graph->E) {
        Edge nextEdge = graph->edges[i++];

        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        if (x != y) {
            result[e++] = nextEdge;
            unionSet(subsets, x, y);
        }
    }

    printf("Edges in the Minimum Spanning Tree:\n");
    int minCost = 0;
    for (i = 0; i < e; i++) {
        printf("%d -- %d == %d\n",
               result[i].src, result[i].dest, result[i].weight);
        minCost += result[i].weight;
    }

    printf("Total cost of MST = %d\n", minCost);
}

/* ================= MAIN ================= */

int main() {
    int V = 4;  // Number of vertices
    int E = 5;  // Number of edges
    Graph* graph = createGraph(V, E);

    graph->edges[0] = (Edge){0, 1, 10};
    graph->edges[1] = (Edge){0, 2, 6};
    graph->edges[2] = (Edge){0, 3, 5};
    graph->edges[3] = (Edge){1, 3,
