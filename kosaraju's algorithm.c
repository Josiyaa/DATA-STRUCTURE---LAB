#include <stdio.h>
#include <stdlib.h>

/* ================= GRAPH ================= */

typedef struct Node {
    int dest;
    struct Node* next;
} Node;

typedef struct Graph {
    int V;
    Node** adj;
} Graph;

Node* createNode(int dest) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->dest = dest;
    node->next = NULL;
    return node;
}

Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->adj = (Node**)malloc(V * sizeof(Node*));

    for (int i = 0; i < V; i++)
        graph->adj[i] = NULL;

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* node = createNode(dest);
    node->next = graph->adj[src];
    graph->adj[src] = node;
}

/* ================= STACK ================= */

typedef struct Stack {
    int* data;
    int top;
} Stack;

Stack* createStack(int V) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (int*)malloc(V * sizeof(int));
    stack->top = -1;
    return stack;
}

void push(Stack* stack, int v) {
    stack->data[++stack->top] = v;
}

int pop(Stack* stack) {
    return stack->data[stack->top--];
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

/* ================= DFS ================= */

void DFS1(Graph* graph, int v, int visited[], Stack* stack) {
    visited[v] = 1;
    Node* temp = graph->adj[v];
    while (temp) {
        if (!visited[temp->dest])
            DFS1(graph, temp->dest, visited, stack);
        temp = temp->next;
    }
    push(stack, v);
}

void DFS2(Graph* graph, int v, int visited[]) {
    visited[v] = 1;
    printf("%d ", v);

    Node* temp = graph->adj[v];
    while (temp) {
        if (!visited[temp->dest])
            DFS2(graph, temp->dest, visited);
        temp = temp->next;
    }
}

/* ================= TRANSPOSE ================= */

Graph* transposeGraph(Graph* graph) {
    Graph* transpose = createGraph(graph->V);

    for (int v = 0; v < graph->V; v++) {
        Node* temp = graph->adj[v];
        while (temp) {
            addEdge(transpose, temp->dest, v);
            temp = temp->next;
        }
    }
    return transpose;
}

/* ================= SCC ================= */

void findSCCs(Graph* graph) {
    int V = graph->V;
    int visited[V];

    for (int i = 0; i < V; i++)
        visited[i] = 0;

    Stack* stack = createStack(V);

    /* Step 1: Order vertices by finish time */
    for (int i = 0; i < V; i++)
        if (!visited[i])
            DFS1(graph, i, visited, stack);

    /* Step 2: Transpose graph */
    Graph* transpose = transposeGraph(graph);

    /* Step 3: DFS in stack order */
    for (int i = 0; i < V; i++)
        visited[i] = 0;

    printf("Strongly Connected Components:\n");

    while (!isEmpty(stack)) {
        int v = pop(stack);
        if (!visited[v]) {
            DFS2(transpose, v, visited);
            printf("\n");
        }
    }
}

/* ================= MAIN ================= */

int main() {
    int V = 5;
    Graph* graph = createGraph(V);

    addEdge(graph, 1, 0);
    addEdge(graph, 0, 2);
    addEdge(graph, 2, 1);
    addEdge(graph, 0, 3);
    addEdge(graph, 3, 4);

    findSCCs(graph);
    return 0;
}
