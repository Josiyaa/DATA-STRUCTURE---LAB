#include <stdio.h>
#include <limits.h>

#define MAX 10

int main() {
    int n;
    int cost[MAX][MAX];
    int selected[MAX] = {0};
    int edges = 0;
    int min, x = 0, y = 0;
    int totalCost = 0;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter the cost adjacency matrix (0 if no edge):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] == 0)
                cost[i][j] = INT_MAX;
        }
    }

    selected[0] = 1; // Start from first vertex

    printf("\nEdges in the Minimum Spanning Tree:\n");

    while (edges < n - 1) {
        min = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (selected[i]) {
                for (int j = 0; j < n; j++) {
                    if (!selected[j] && cost[i][j] < min) {
                        min = cost[i][j];
                        x = i;
                        y = j;
                    }
                }
            }
        }

        printf("%d - %d : %d\n", x, y, min);
        totalCost += min;
        selected[y] = 1;
        edges++;
    }

    printf("\nTotal cost of Minimum Spanning Tree: %d\n", totalCost);

    return 0;
}
