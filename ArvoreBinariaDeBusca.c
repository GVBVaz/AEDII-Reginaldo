#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int chave;
    struct No* esquerda;
    struct No* direita;
    struct No* pai;
} No;

No* buscaRecursiva(No* raiz, int chave){
    if(raiz == NULL || chave == raiz->chave){
        return raiz;
    }

    if(chave < raiz->chave){
        return buscaRecursiva(raiz->esquerda, chave);
    }
    else{
        return buscaRecursiva(raiz->direita, chave);
    }
}

No* buscaIterativa(No* raiz, int chave){
    while(raiz != NULL && chave != raiz->chave){
        if(chave < raiz->chave){
            raiz = raiz->esquerda;
        }
        else{
            raiz = raiz->direita;
        }
    }

    return raiz;
}

No* minimo(No* raiz){
    while(raiz->esquerda != NULL){
        raiz = raiz->esquerda;
    }

    return raiz;
}

No* maximo(No* raiz){
    while(raiz->direita != NULL){
        raiz = raiz->direita;
    }

    return raiz;
}

No* criarNo(int chave){
    No* novo = malloc(sizeof(No));
    novo->chave = chave;
    novo->esquerda = NULL;
    novo->direita = NULL;
    novo->pai = NULL;
    return novo;
}

void inserirNaArvore(No** raiz, No* z){
    No* y = NULL; // y será pai de x
    No* x = *raiz;

    while(x != NULL){
        y = x;

        if(z->chave < x->chave){
            x = x->esquerda;
        }
        else{
            x = x->direita;
        }
    }

    z->pai = y;

    if(y == NULL){ // a árevore estava vazia
        *raiz = z;
    }
    else if(z->chave < y->chave){
        y->esquerda = z;
    }
    else{
        y->direita = z;
    }
}

void transplantar(No** raiz, No* u, No* v){
    if(u->pai == NULL){
        *raiz = v;
    }
    else if(u == u->pai->esquerda){
        u->pai->esquerda = v;
    }
    else{
        u->pai->direita = v;
    }

    if(v != NULL){
        v->pai = u->pai;
    }
}

void remover(No** raiz, No* z){
    if(z->esquerda == NULL){
        transplantar(raiz, z, z->direita);
    }
    else if(z->direita == NULL){
        transplantar(raiz, z, z->esquerda);
    }
    else{
        No* y = minimo(z->direita);

        if(y->pai != z){
            transplantar(raiz, y, y->direita);
            y->direita = z->direita;

            if(y->direita != NULL){
                y->direita->pai = y;
            }
        }

        transplantar(raiz, z, y);
        y->esquerda = z->esquerda;

        if(y->esquerda != NULL){
            y->esquerda->pai = y;
        }
    }

    free(z);
}

int altura(No* raiz){
    if(raiz == NULL){
        return -1;
    }

    int alt_esq = altura(raiz->esquerda);
    int alt_dir = altura(raiz->direita);
    int maior;

    if(alt_esq > alt_dir){
        maior = alt_esq;
    }
    else{
        maior = alt_dir;
    }

    return 1 + maior;
}

void imprimirEmOrdem(No* raiz){
    if(raiz != NULL){
        imprimirEmOrdem(raiz->esquerda);
        printf("%d ", raiz->chave);
        imprimirEmOrdem(raiz->direita);
    }
}