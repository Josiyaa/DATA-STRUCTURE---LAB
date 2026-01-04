#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* ================= FIBONACCI HEAP ================= */

typedef struct FibNode {
    int vertex;
    int key;
    int degree;
    int mark;
    struct FibNode *parent;
    struct FibNode *child;
    struct FibNode *left;
    struct FibNode *right;
} FibNode;

typedef struct FibHeap {
    int n;
    FibNode *min;
} FibHeap;

FibNode* createNode(int vertex, int key) {
    FibNode* node = (FibNode*)malloc(sizeof(FibNode));
    node->vertex = vertex;
    node->key = key;
    node->degree = 0;
    node->mark = 0;
    node->parent = node->child = NULL;
    node->left = node->right = node;
    return node;
}

FibHeap* createHeap() {
    FibHeap* heap = (FibHeap*)malloc(sizeof(FibHeap));
    heap->n = 0;
    heap->min = NULL;
    return heap;
}

void insertNode(FibHeap* heap, FibNode* node) {
    if (heap->min == NULL) {
        heap->min = node;
    } else {
        node->left = heap->min;
        node->right = heap->min->right;
        heap->min->right->left = node;
        heap->min->right = node;

        if (node->key < heap->min->key)
            heap->min = node;
    }
    heap->n++;
}

void fibHeapLink(FibHeap* heap, FibNode* y, FibNode* x) {
    y->left->right = y->right;
    y->right->left = y->left;

    y->parent = x;
    if (x->child == NULL) {
        x->child = y;
        y->left = y->right = y;
    } else {
        y->left = x->child;
        y->right = x->child->right;
        x->child->right->left = y;
        x->child->right = y;
    }
    x->degree++;
    y->mark = 0;
}

void consolidate(FibHeap* heap) {
    int D = 45;
    FibNode* A[D];
    for (int i = 0; i < D; i++) A[i] = NULL;

    FibNode* w = heap->min;
    if (w == NULL) return;

    FibNode* start = w;
    do {
        FibNode* x = w;
        int d = x->degree;
        while (A[d] != NULL) {
            FibNode* y = A[d];
            if (x->key > y->key) {
                FibNode* temp = x;
                x = y;
                y = temp;
            }
            fibHeapLink(heap, y, x);
            A[d] = NULL;
            d++;
        }
        A[d] = x;
        w = w->right;
    } while (w != start);

    heap->min = NULL;
    for (int i = 0; i < D; i++) {
        if (A[i] != NULL) {
            if (heap->min == NULL) {
                heap->min = A[i];
                heap->min->left = heap->min->right = heap->min;
            } else {
                A[i]->left = heap->min;
                A[i]->right = heap->min->right;
                heap->min->right->left = A[i];
                heap->min->right = A[i];
                if (A[i]->key < heap->min->key)
                    heap->min = A[i];
            }
        }
    }
}

FibNode* extractMin(FibHeap* heap) {
    FibNode* z = heap->min;
    if (z != NULL) {
        FibNode* x = z->child;
        if (x != NULL) {
            FibNode* start = x;
            do {
                FibNode* next = x->right;
                x->parent = NULL;
                x->left = heap->min;
                x->right = heap->min->right;
                heap->min->right->left = x;
                heap->min->right = x;
                x = next;
            } while (x != start);
        }

        z->left->right = z->right;
        z->right->left = z->left;

        if (z == z->right) {
            heap->min = NULL;
        } else {
            heap->min = z->right;
            consolidate(heap);
        }
        heap->n--;
    }
    return z;
}

void cut(FibHeap* heap, FibNode* x, FibNode* y) {
    if (x->right == x)
        y->child = NULL;
    else {
        x->right->left = x->left;
        x->left->right = x->right;
        if (y->child == x)
            y->child = x->right;
    }
    y->degree--;

    x->left = heap->min;
    x->right = heap->min->right;
    heap->min->right->left = x;
    heap->min->right = x;
    x->parent = NULL;
    x->mark = 0;
}

void cascadingCut(FibHeap* heap, FibNode* y) {
    FibNode* z = y->parent;
    if (z != NULL) {
        if (y->mark == 0)
            y->mark = 1;
        else {
            cut(heap, y, z);
            cascadingCut(heap, z);
        }
    }
}

void decreaseKey(FibHeap* heap, FibNode* x, int k) {
    if (k > x->key) return;
    x->key = k;
    FibNode* y = x->parent;
    if (y != NULL && x->key < y->key) {
        cut(heap, x, y);
        cascadingCut(heap, y);
    }
    if (x->key < heap->min->key)
        heap->min = x;
}

/* ================= GRAPH ================= */

typedef struct AdjNode {
    int dest;
    int weight;
    struct AdjNode* next;
} AdjNode;

typedef struct Graph {
    int V;
    AdjNode** array;
} Graph;

Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjNode**)malloc(V * sizeof(AdjNode*));
    for (int i = 0; i < V; i++)
        graph->array[i] = NULL;
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    AdjNode* node = (AdjNode*)malloc(sizeof(AdjNode));
    node->dest = dest;
    node->weight = weight;
    node->next = graph->array[src];
    graph->array[src] = node;
}

/* ================= DIJKSTRA ================= */

void dijkstra(Graph* graph, int src) {
    int V = graph->V;
    int dist[V];
    FibNode* nodes[V];

    FibHeap* heap = createHeap();

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        nodes[i] = createNode(i, INT_MAX);
        insertNode(heap, nodes[i]);
    }

    dist[src] = 0;
    decreaseKey(heap, nodes[src], 0);

    while (heap->n != 0) {
        FibNode* minNode = extractMin(heap);
        int u = minNode->vertex;

        AdjNode* crawl = graph->array[u];
        while (crawl) {
            int v = crawl->dest;
            if (dist[u] != INT_MAX && dist[v] > dist[u] + crawl->weight) {
                dist[v] = dist[u] + crawl->weight;
                decreaseKey(heap, nodes[v], dist[v]);
            }
            crawl = crawl->next;
        }
    }

    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

/* ================= MAIN ================= */

int main() {
    int V = 5;
    Graph* graph = createGraph(V);

    addEdge(graph, 0, 1, 9);
    addEdge(graph, 0, 2, 6);
    addEdge(graph, 0, 3, 5);
    addEdge(graph, 0, 4, 3);
    addEdge(graph, 2, 1, 2);
    addEdge(graph, 2, 3, 4);

    dijkstra(graph, 0);
    return 0;
}
