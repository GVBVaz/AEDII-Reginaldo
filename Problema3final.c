#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dict{
    char termo[100];
    char traducao[100];
} dicionario;

void RemoverBarraN(char *str){
    str[strcspn(str, "\n")] = '\0';
}

void Merge(dicionario v[], int left, int mid, int right){
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    dicionario *L = malloc(n1 * sizeof(dicionario));
    dicionario *R = malloc(n2 * sizeof(dicionario));

    for(i = 0; i < n1; i++){
        L[i] = v[left + i];
    }
    for(j = 0; j < n2; j++){
        R[j] = v[mid + 1 + j];
    }

    i = 0, j = 0, k = left;

    while(i < n1 && j < n2){
        if(strcmp(L[i].termo, R[j].termo) <= 0){
            v[k++] = L[i++];
        }
        else{
            v[k++] = R[j++];
        }
    }

    while(i < n1){
        v[k++] = L[i++];
    }
    while(j < n2){
        v[k++] = R[j++];
    }

    free(L);
    free(R);
}

void MergeSort(dicionario v[], int left, int right){
    if(left < right){
        int mid = (left + right) / 2;
        MergeSort(v, left, mid);
        MergeSort(v, mid + 1, right);
        Merge(v, left, mid, right);
    }
}

int BuscaBinaria(dicionario v[], int n, const char* palavra){
    int ini = 0;
    int end = n - 1;
    int mid;

    while(ini <= end){
        mid = (ini + end) / 2;
        int cmp = strcmp(v[mid].termo, palavra);
        if(cmp == 0){
            return mid;
        }
        else if(cmp < 0){
            ini = mid + 1;
        }
        else{
            end = mid - 1;
        }
    }

    return -1;
}

int main(){
    int M, N;
    int i;

    scanf("%d %d", &M, &N);
    getchar();

    dicionario palavras_conhecidas[M];
    char frase[100];
    char frase_traduzida[1000] = "";

    for(i = 0; i < M; i++){
        fgets(palavras_conhecidas[i].termo, 100, stdin);
        RemoverBarraN(palavras_conhecidas[i].termo);
        fgets(palavras_conhecidas[i].traducao, 100, stdin);
        RemoverBarraN(palavras_conhecidas[i].traducao);
    }

    MergeSort(palavras_conhecidas, 0, M - 1);

    for(i = 0; i < N; i++){
        fgets(frase, 100, stdin);
        RemoverBarraN(frase);

        frase_traduzida[0] = '\0';

        char *palavra = strtok(frase, " ");
        while(palavra != NULL){
            int posicao = BuscaBinaria(palavras_conhecidas, M, palavra);

            if(posicao != -1){
                strcat(frase_traduzida, palavras_conhecidas[posicao].traducao);
            }
            else{
                strcat(frase_traduzida, palavra);
            }
            strcat(frase_traduzida, " ");

            palavra = strtok(NULL, " ");
        }

        printf("%s\n", frase_traduzida);
    }
}