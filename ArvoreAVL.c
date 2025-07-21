#include <stdio.h>
#include <stdlib.h>

typedef struct NoAVL{
    int valor;
    int altura;
    struct NoAVL* esquerda;
    struct NoAVL* direita;
} NoAVL;

int altura(NoAVL* no){
    if(no != NULL){
        return no->altura;
    }
    else{
        return -1;
    }
}

void corrigir_altura(NoAVL* no){
    int altura_esq = altura(no->esquerda);
    int altura_dir = altura(no->direita);

    if(altura_esq > altura_dir){
        no->altura = altura_esq + 1;
    }
    else{
        no->altura = altura_dir + 1;
    }
}

NoAVL* rotacao_esquerda(NoAVL* x){
    NoAVL* y = x->direita;
    x->direita = y->esquerda;
    y->esquerda = x;

    corrigir_altura(x);
    corrigir_altura(y);

    return y;
}

NoAVL* rotacao_direita(NoAVL* x){
    NoAVL* y = x->esquerda;
    x->esquerda = y->direita;
    y->direita = x;

    corrigir_altura(x);
    corrigir_altura(y);

    return y;
}

int fator_balanceamento(NoAVL* no){
    if(no == NULL){
        return 0;
    }

    return altura(no->esquerda) - altura(no->direita);
}

NoAVL* novo_no(int valor){
    NoAVL* no = malloc(sizeof(NoAVL));
    no->valor = valor;
    no->altura = 0;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

NoAVL* inserirAVL(NoAVL* raiz, int valor){
    if(raiz == NULL){
        return novo_no(valor);
    }

    if(valor < raiz->valor){
        raiz->esquerda = inserirAVL(raiz->esquerda, valor);
    }
    else if(valor > raiz->valor){
        raiz->direita = inserirAVL(raiz->direita, valor);
    }
    else{
        return raiz;
    }

    corrigir_altura(raiz);

    int fb = fator_balanceamento(raiz);

    // Caso 3
    if(fb > 1 && valor < raiz->esquerda->valor){
        return rotacao_direita(raiz);
    }

    // Caso 1
    if(fb < -1 && valor > raiz->direita->valor){
        return rotacao_esquerda(raiz);
    }

    // Caso 4
    if(fb > 1 && valor > raiz->esquerda->valor){
        raiz->esquerda = rotacao_esquerda(raiz->esquerda);
        return rotacao_direita(raiz);
    }

    // Caso 2
    if(fb < -1 && valor < raiz->direita->valor){
        raiz->direita = rotacao_direita(raiz->direita);
        return rotacao_esquerda(raiz);
    }

    return raiz;
}