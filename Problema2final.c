#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void Merge(int v[], int p, int q, int r){
    int i, j, k;
    int n1 = q - p + 1;
    int n2 = r - q;
    int* L = malloc((n1 + 1) * sizeof(int));
    int* R = malloc((n2 + 1) * sizeof(int));

    for(i = 0; i < n1; i++){
        L[i] = v[p + i];
    }
    for(j = 0; j < n2; j++){
        R[j] = v[q + 1 + j];
    }

    L[n1] = INT_MAX;
    R[n2] = INT_MAX;

    i = 0;
    j = 0;

    for(k = p; k <= r; k++){
        if(L[i] <= R[j]){
            v[k] = L[i];
            i++;
        }
        else{
            v[k] = R[j];
            j++;
        }
    }

    free(L);
    free(R);
}

void MergeSort(int v[], int p, int r){
    if(p < r){
        int q = (p + r)/2;
        MergeSort(v, p, q);
        MergeSort(v, q + 1, r);
        Merge(v, p, q, r);
    }
}

int BuscaBinaria(int v[], int n, int valor){
    int ini = 0;
    int end = n - 1;
    int mid;
    int resultado = -1;

    while(ini <= end){
        mid = (ini + end) / 2;
        if(v[mid] == valor){
            resultado = mid;
            end = mid - 1;
        }
        else if(v[mid] < valor){
            ini = mid + 1;
        }
        else{
            end = mid - 1;
        }
    }

    return resultado;
}

int PosicaoInsercao(int v[], int n, int valor){
    int ini = 0;
    int end = n - 1;
    int mid;
    int pos = n;

    while(ini <= end){
        mid = (ini + end) / 2;
        if(v[mid] >= valor){
            pos = mid;
            end = mid - 1;
        }
        else{
            ini = mid + 1;
        }
    }

    return pos;
}

int main(){
    int n, V;

    int i;
    int j = 1;

    int posicao;
    int primeiro_duplicado;
    int posicao_primeiro_duplicado = -1;
    int posicao_insercao;

    scanf("%d", &n);
    if(n == 0){
        printf("Nenhum 0");
        return 0;
    }

    int* artefatos = malloc(n * sizeof(int));
    int* artefatos_ordenados = malloc(n * sizeof(int));
    int* artefatos_ordenados_sem_repeticao = malloc(n * sizeof(int));

    for(i = 0; i < n; i++){
        scanf("%d", &artefatos[i]);
        artefatos_ordenados[i] = artefatos[i];
    }

    scanf("%d", &V);

    MergeSort(artefatos_ordenados, 0, n-1);

    for(i = 0; i < n; i++){
        posicao = BuscaBinaria(artefatos_ordenados, n, artefatos[i]);
        if(posicao != -1 && posicao + 1 < n && artefatos_ordenados[posicao] == artefatos_ordenados[posicao + 1]){
            primeiro_duplicado = artefatos[i];
            posicao_primeiro_duplicado = posicao;
            break;
        }
    }

    artefatos_ordenados_sem_repeticao[0] = artefatos_ordenados[0];
    for(i = 1; i < n; i++){
        if(artefatos_ordenados[i] != artefatos_ordenados_sem_repeticao[j - 1]){
            artefatos_ordenados_sem_repeticao[j] = artefatos_ordenados[i];
            j++;
        }
    }

    posicao_insercao = PosicaoInsercao(artefatos_ordenados_sem_repeticao, j, V);

    if(posicao_primeiro_duplicado == -1){
        printf("Nenhum %d", posicao_insercao);
    }
    else{
        printf("%d %d", primeiro_duplicado, posicao_insercao);
    }

    free(artefatos);
    free(artefatos_ordenados);
    free(artefatos_ordenados_sem_repeticao);

    return 0;
}