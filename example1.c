#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct Graph {
    int v;
    int *vis;
    struct Node **alst;
} GPH;

NODE *create_node(int v) {
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge(GPH *g, int src, int dest) {
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;
}

GPH *create_g(int v) {
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(sizeof(NODE *) * v);
    g->vis = malloc(sizeof(int) * v);

    for (int i = 0; i < v; i++) {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }

    return g;
}

void DFS(GPH *g, int v_nr, int dest, int *path_exists) {
    NODE *adj_list = g->alst[v_nr];
    NODE *aux = adj_list;
    g->vis[v_nr] = 1;
    if (v_nr == dest) {
        *path_exists = 1;
        return;
    }
    while (aux != NULL) {
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0) {
            DFS(g, con_ver, dest, path_exists);
        }
        aux = aux->next;
    }
}

int main() {
    int nrv, edg_nr, src, dest;
    printf("Cate noduri are reteaua? ");
    scanf("%d", &nrv);
    printf("Cate muchii are reteaua? ");
    scanf("%d", &edg_nr);
    GPH *g = create_g(nrv);
    printf("Adauga %d muchii (de la 1 la %d):\n", edg_nr, nrv);
    for (int i = 0; i < edg_nr; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        add_edge(g, src - 1, dest - 1); // decrementăm pentru a indexa de la 0
    }
    printf("Introduceti sursa si destinatia pentru a verifica existenta unui drum direct:\n");
    scanf("%d %d", &src, &dest);
    int path_exists = 0;
    DFS(g, src - 1, dest - 1, &path_exists); // decrementăm pentru a indexa de la 0
    if (path_exists) {
        printf("Exista un drum direct intre nodurile %d si %d.\n", src, dest);
    } else {
        printf("Nu exista un drum direct intre nodurile %d si %d.\n", src, dest);
    }
    return 0;
}
