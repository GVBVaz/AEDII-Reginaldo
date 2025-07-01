#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 251

typedef struct adj{
    int destino;
    int custo;
    struct adj* prox;
} adj;

adj* grafo[MAX];
int distancia[MAX];
int visitado[MAX];
int N, M, C, K;

void adicionaAresta(int u, int v, int custo){
    adj* novo = malloc(sizeof(adj));
    novo->destino = v;
    novo->custo = custo;
    novo->prox = grafo[u];
    grafo[u] = novo;
}

void dijkstra(int origem){
    int i;
    adj* p;

    for(i = 0; i < N; i++){
        distancia[i] = INT_MAX;
        visitado[i] = 0;
    }
    distancia[origem] = 0;

    while(1){
        int u = -1;
        int menor = INT_MAX;

        for(i = 0; i < N; i++){
            if(!visitado[i] && distancia[i] < menor){
                menor = distancia[i];
                u = i;
            }
        }

        if(u == -1){
            break;
        }
        visitado[u] = 1;

        for(p = grafo[u]; p != NULL; p = p->prox){
            int d = p->destino;
            int custo = p->custo;

            if(distancia[d] > distancia[u] + custo){
                distancia[d] = distancia[u] + custo;
            }
        }
    }
}

void limpaGrafo(){
    int i;

    for(i = 0; i < N; i++){
        adj* p = grafo[i];
        while(p){
            adj* temp = p;
            p = p->prox;
            free(temp);
        }
        grafo[i] = NULL;
    }
}

int main(){
    int U, V, P;
    int i;

    scanf("%d %d %d %d", &N, &M, &C, &K);

    limpaGrafo();

    for(i = 0; i < M; i++){
        scanf("%d %d %d", &U, &V, &P);

        if(U < C && V < C){
            if(V == U + 1){
                adicionaAresta(U, V, P);
            }
            else if(U == V + 1){
                adicionaAresta(V, U, P);
            }
        }
        else if(U < C && V >= C){
            adicionaAresta(V, U, P);
        }
        else if(V < C && U >= C){
            adicionaAresta(U, V, P);
        }
        else{
            adicionaAresta(U, V, P);
            adicionaAresta(V, U, P);
        }
    }

    dijkstra(K);

    printf("%d\n", distancia[C - 1]);
}