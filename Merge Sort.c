#include <stdio.h>
#include <limits.h>

void Merge(int v[], int p, int q, int r){
    int i, j, k;
    int n1 = q - p + 1;
    int n2 = r - q;
    int L[n1 + 1], R[n2 + 1];

    for(i = 0; i < n1; i++){
        L[i] = v[p + i];
    }
    for(j = 0; j < n2; j++){
        R[j] = v[q + 1 + j];
    }

    L[n1] = INT_MAX;
    R[n2] = INT_MAX;

    i = 0, j = 0;

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
}

void MergeSort(int v[], int p, int r){
    if(p < r){
        int q = (p + r)/2;
        MergeSort(v, p, q);
        MergeSort(v, q + 1, r);
        Merge(v, p, q, r);
    }
}

int main(){
    int vetor[10];
    int i;

    for(i = 0; i < 10; i++){
        scanf("%d", &vetor[i]);
    }
    for(i = 0; i < 10; i++){
        if(i != 9){
            printf("%d ", vetor[i]);
        }
        else{
            printf("%d\n", vetor[i]);
        }
    }

    MergeSort(vetor, 0, 9);

    for(i = 0; i < 10; i++){
        if(i != 9){
            printf("%d ", vetor[i]);
        }
        else{
            printf("%d\n", vetor[i]);
        }
    }
}