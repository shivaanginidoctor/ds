#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
#define FALSE 0
#define TRUE 1

typedef struct node {
    int vertex;
    struct node* next;
} Node;

Node* graph[MAX_VERTICES];

short int visited[MAX_VERTICES];

int n;
Node* createNode(int vertex);
void addEdge(int src, int dest);
void dfs(int v);
void initializeVisited();

Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

void addEdge(int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph[src];
    graph[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph[dest];
    graph[dest] = newNode;
}

void dfs(int v) {
    Node* w;
    visited[v] = TRUE;
    printf("%5d", v);

    for (w = graph[v]; w != NULL; w = w->next) {
        if (!visited[w->vertex])
            dfs(w->vertex);
    }
}

void initializeVisited() {
    for (int i = 0; i < n; i++)
        visited[i] = FALSE;
}

int main() {
    int edges, src, dest, startVertex;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        graph[i] = NULL;
        visited[i] = FALSE;
    }

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter each edge (source destination):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &src, &dest);
        addEdge(src, dest);
    }

    printf("Enter starting vertex for DFS: ");
    scanf("%d", &startVertex);

    printf("\nDepth First Search Traversal:\n");
    dfs(startVertex);

    printf("\n");
    return 0;
}