#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_L 30
#define MAX_C 80

typedef struct{
    int x;
    int y;
} ponto;

char mapa[MAX_L][MAX_C + 1];
int dist_joao[MAX_L][MAX_C];
int dist_pedrinho[MAX_L][MAX_C];
int L;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int valido(int x, int y){
    if(x < 0 || x >= L){
        return 0;
    }
    if(y < 0 || y >= (int)strlen(mapa[x])){
        return 0;
    }

    char c = mapa[x][y];
    if(c == ' ' || c == '*' || c == '+' || c == '$'){
        return 1;
    }

    return 0;
}

int bfs(ponto origem, int dist[MAX_L][MAX_C]){
    int i, j, d;

    for(i = 0; i < L; i++){
        for(j = 0; j < (int)strlen(mapa[i]); j++){
            dist[i][j] = -1;
        }
    }

    ponto fila[MAX_L * MAX_C];
    int inicio = 0;
    int fim = 0;

    dist[origem.x][origem.y] = 0;
    fila[fim++] = origem;

    while(inicio < fim){
        ponto p = fila[inicio++];

        if(mapa[p.x][p.y] == '$'){
            return dist[p.x][p.y];
        }

        for(d = 0; d < 4; d++){
            int nx = p.x + dx[d];
            int ny = p.y + dy[d];

            if(valido(nx, ny) && dist[nx][ny] == -1){
                dist[nx][ny] = dist[p.x][p.y] + 1;
                ponto np = {nx, ny};
                fila[fim++] = np;
            }
        }
    }

    return -1;
}

int main(){
    int i, j;

    ponto joao = {-1, -1};
    ponto pedrinho = {-1, -1};

    scanf("%d", &L);
    getchar();

    for(i = 0; i < L; i++){
        fgets(mapa[i], MAX_C + 1, stdin);

        int len = strlen(mapa[i]);
        if(mapa[i][len - 1] == '\n'){
            mapa[i][len - 1] = '\0';
        }

        for(j = 0; mapa[i][j] != '\0'; j++){
            if(mapa[i][j] == '*'){
                joao.x = i;
                joao.y = j;
            }
            else if(mapa[i][j] == '+'){
                pedrinho.x = i;
                pedrinho.y = j;
            }
        }
    }

    int d_joao = bfs(joao, dist_joao);
    int d_pedrinho = bfs(pedrinho, dist_pedrinho);

    if(d_joao == -1 && d_pedrinho == -1){
        printf("-1\n");
    }
    else if(d_joao != -1 && (d_pedrinho == -1 || d_joao < d_pedrinho)){
        printf("1\n");
    }
    else if(d_pedrinho != -1 && (d_joao == -1 || d_pedrinho < d_joao)){
        printf("2\n");
    }
    else if(d_joao == d_pedrinho){
        printf("0\n");
    }

    return 0;
}