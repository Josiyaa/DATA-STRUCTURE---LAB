#include <stdio.h>

#define MAX 10

int graph[MAX][MAX];
int n = 0;  // number of vertices

void createGraph() {
    int i, j;

    printf("Enter number of vertices (max %d): ", MAX);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX) {
        printf("Invalid number of vertices.\n");
        return;
    }

    // initialize matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            graph[i][j] = 0;

    int edges, src, dest;
    printf("Enter number of edges: ");
    if (scanf("%d", &edges) != 1 || edges < 0) {
        printf("Invalid number of edges.\n");
        return;
    }

    printf("Enter edges (u v):\n");
    for (i = 0; i < edges; i++) {
        scanf("%d %d", &src, &dest);

        if (src < 0 || src >= n || dest < 0 || dest >= n) {
            printf("Invalid vertex index. Try again.\n");
            i--;
            continue;
        }

        graph[src][dest] = 1;
        graph[dest][src] = 1;  // undirected
    }
}

void addEdge() {
    if (n == 0) {
        printf("Graph not created yet.\n");
        return;
    }

    int u, v;
    printf("Enter edge (u v): ");
    scanf("%d %d", &u, &v);

    if (u < 0 || u >= n || v < 0 || v >= n) {
        printf("Invalid vertices.\n");
        return;
    }

    graph[u][v] = 1;
    graph[v][u] = 1;
    printf("Edge added.\n");
}

void displayGraph() {
    if (n == 0) {
        printf("Graph not created yet.\n");
        return;
    }

    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n--- GRAPH MENU ---\n");
        printf("1. Create Graph\n");
        printf("2. Add Edge\n");
        printf("3. Display Graph\n");
        printf("4. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            return 0;
        }

        switch (choice) {
            case 1: createGraph(); break;
            case 2: addEdge(); break;
            case 3: displayGraph(); break;
            case 4: return 0;
            default: printf("Invalid choice.\n");
        }
    }
}
