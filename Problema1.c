#include <stdio.h>
 
int main(){
    int V, C, voto1, voto2, voto3;
    int i, j;
    int mais_votado1 = 0;
    int mais_votado2 = 0;
    int votos_mais_votado1 = 0;
    int votos_mais_votado2 = 0;
    float soma = 0;
    float porcentagem;
 
    scanf("%d %d", &V, &C);
    int votos_por_candidato[C+1];
    int matriz_votos[V][4];
    
    for(i = 1; i <= C; i++){
        votos_por_candidato[i] = 0;
    }
 
    for(i = 0; i < V; i++){
        scanf("%d %d %d", &voto1, &voto2, &voto3);
        matriz_votos[i][1] = voto1;
        matriz_votos[i][2] = voto2;
        matriz_votos[i][3] = voto3;
        for(j = 1; j <= C; j++){
            if(voto1 == j){
                votos_por_candidato[j]++;
            }
        }
    }
 
    for(i = 1; i <= C; i++){
        if(votos_por_candidato[i] > votos_mais_votado1){
            mais_votado1 = i;
            votos_mais_votado1 = votos_por_candidato[i];
        }
        soma += votos_por_candidato[i];
    }
 
    for(i = 1; i <= C; i++){
        if(votos_por_candidato[i] > votos_mais_votado2 && i != mais_votado1){
            mais_votado2 = i;
            votos_mais_votado2 = votos_por_candidato[i];
        }
    }
 
    porcentagem = (100 * votos_mais_votado1) / soma;
 
    if(mais_votado1 == 0){
        printf("0\n");
    }
 
    else if(porcentagem >= 50){
        if(votos_mais_votado1 == votos_mais_votado2){
            if(mais_votado1 < mais_votado2){
                printf("%d %.2f\n", mais_votado1, porcentagem);
            }
            else{
                printf("%d %.2f\n", mais_votado2, porcentagem);
            }
        }
        else{
            printf("%d %.2f\n", mais_votado1, porcentagem);
        }
    }
 
    else{
        if(votos_mais_votado1 == votos_mais_votado2){
            if(mais_votado1 < mais_votado2){
                printf("%d %.2f\n", mais_votado1, porcentagem);
            }
            else{
                printf("%d %.2f\n", mais_votado2, porcentagem);
            }
        }
        else{
            printf("%d %.2f\n", mais_votado1, porcentagem);
        }
 
        votos_mais_votado1 = 0;
        votos_mais_votado2 = 0;
 
        for(i = 0; i < V; i++){
            for(j = 1; j <= 3; j++){
                if(matriz_votos[i][j] == mais_votado1){
                    votos_mais_votado1++;
                    break;
                }
                else if(matriz_votos[i][j] == mais_votado2){
                    votos_mais_votado2++;
                    break;
                }
            }
        }
        soma = votos_mais_votado1 + votos_mais_votado2;
 
        if(votos_mais_votado1 > votos_mais_votado2){
            porcentagem = (100 * votos_mais_votado1) / soma;
            printf("%d %.2f\n", mais_votado1, porcentagem);
        }
        else if(votos_mais_votado2 > votos_mais_votado1){
            porcentagem = (100 * votos_mais_votado2) / soma;
            printf("%d %.2f\n", mais_votado2, porcentagem);
        }
        else{
            if(mais_votado1 < mais_votado2){
                porcentagem = (100 * votos_mais_votado1) / soma;
                printf("%d %.2f\n", mais_votado1, porcentagem);
            }
            else{
                porcentagem = (100 * votos_mais_votado2) / soma;
                printf("%d %.2f\n", mais_votado2, porcentagem);
            }
        }
    }
}