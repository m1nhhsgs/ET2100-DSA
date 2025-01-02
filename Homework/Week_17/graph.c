#include <stdio.h>
#include <stdbool.h>

enum Node {
    A = 0,
    B,
    C,
    D,
    E,
    G,
    H
};

static const char* nodeNames[7] = { "A", "B", "C", "D", "E", "G", "H" };

typedef struct {
    bool matrix[7][7];
} Graph;

void initGraph(Graph* g) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            g->matrix[i][j] = false;
        }
    }
}

void addEdge(Graph* g, enum Node from, enum Node to) {
    g->matrix[from][to] = true;
}

bool isEdge(const Graph* g, enum Node from, enum Node to) {
    return g->matrix[from][to];
}

void printGraph(const Graph* g) {
    printf("Adjacency Matrix:\n");
    printf("    A B C D E G H\n");
    for (int i = 0; i < 7; i++) {
        printf("%s : ", nodeNames[i]);
        for (int j = 0; j < 7; j++) {
            printf("%d ", g->matrix[i][j] ? 1 : 0);
        }
        printf("\n");
    }
    printf("\n");
}

void bfs(const Graph* g, enum Node start) {
    bool visited[7];
    for (int i = 0; i < 7; i++) {
        visited[i] = false;
    }

    enum Node queue[7];
    int front = 0, rear = 0;
    visited[start] = true;
    queue[rear++] = start;

    printf("BFS order from %s: ", nodeNames[start]);
    while (front < rear) {
        enum Node current = queue[front++];
        printf("%s ", nodeNames[current]);

        for (int j = 0; j < 7; j++) {
            if (g->matrix[current][j] && !visited[j]) {
                visited[j] = true;
                queue[rear++] = (enum Node)j;
            }
        }
    }
    printf("\n");
}

static void dfsUtil(const Graph* g, enum Node current, bool visited[]) {
    visited[current] = true;
    printf("%s ", nodeNames[current]);

    for (int j = 0; j < 7; j++) {
        if (g->matrix[current][j] && !visited[j]) {
            dfsUtil(g, (enum Node)j, visited);
        }
    }
}

void dfs(const Graph* g, enum Node start) {
    bool visited[7];
    for (int i = 0; i < 7; i++) {
        visited[i] = false;
    }
    printf("DFS order from %s: ", nodeNames[start]);
    dfsUtil(g, start, visited);
    printf("\n");
}

int main() {
    Graph g;
    initGraph(&g);

    addEdge(&g, A, B);
    addEdge(&g, A, D);
    addEdge(&g, A, E);
    addEdge(&g, A, H);
    addEdge(&g, B, C);
    addEdge(&g, B, D);
    addEdge(&g, B, G);
    addEdge(&g, C, B);
    addEdge(&g, C, D);
    addEdge(&g, C, H);
    addEdge(&g, D, A);
    addEdge(&g, D, C);
    addEdge(&g, D, G);
    addEdge(&g, D, H);
    addEdge(&g, E, B);
    addEdge(&g, E, D);
    addEdge(&g, E, G);
    addEdge(&g, G, A);
    addEdge(&g, G, B);
    addEdge(&g, G, E);
    addEdge(&g, G, H);

    printGraph(&g);
    printf("\nEdge from A to B? %s\n", isEdge(&g, A, B) ? "Yes" : "No");
    printf("Edge from B to A? %s\n", isEdge(&g, B, A) ? "Yes" : "No");

    bfs(&g, A);
    dfs(&g, A);

    return 0;
}