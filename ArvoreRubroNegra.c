#include <stdio.h>
#include <stdlib.h>

typedef enum {VERMELHO, PRETO} Cor;

typedef struct No{
    int chave;
    Cor cor;
    struct No* esquerda;
    struct No* direita;
    struct No* pai;
} No;

typedef struct{
    No* raiz;
    No* nulo;
} ArvoreRN;

No* criar_no(ArvoreRN* arvore, int chave){
    No* no = malloc(sizeof(No));
    no->chave = chave;
    no->cor = VERMELHO;
    no->esquerda = no->direita = no->pai = arvore->nulo;
    return no;
}

ArvoreRN* criar_arvore(){
    ArvoreRN* arvore = malloc(sizeof(ArvoreRN));
    arvore->nulo = malloc(sizeof(No));
    arvore->nulo->cor = PRETO;
    arvore->nulo->esquerda = arvore->nulo->direita = arvore->nulo->pai = NULL;
    arvore->raiz = arvore->nulo;
    return arvore;
}

void rotacao_esquerda(ArvoreRN* arvore, No* x){
    No* y = x->direita;
    x->direita = y->esquerda; // subárvore esquerda de y passa a ser subárvore direita de x

    if(y->esquerda != arvore->nulo){
        y->esquerda->pai = x;
    }

    y->pai = x->pai; // liga o pai de x a y

    if(x->pai == arvore->nulo){
        arvore->raiz = y;
    }
    else if(x == x->pai->esquerda){
        x->pai->esquerda = y;
    }
    else{
        x->pai->direita = y;
    }

    y->esquerda = x; // coloca x à esquerda de y
    x->pai = y;
}

void rotacao_direita(ArvoreRN* arvore, No* x){
    No* y = x->esquerda;
    x->esquerda = y->direita;

    if(y->direita != arvore->nulo){
        y->direita->pai = x;
    }

    y->pai = x->pai;

    if(x->pai == arvore->nulo){
        arvore->raiz = y;
    }
    else if(x == x->pai->esquerda){
        x->pai->esquerda = y;
    }
    else{
        x->pai->direita = y;
    }

    y->direita = x;
    x->pai = y;
}

void corrigir_insercao(ArvoreRN* arvore, No* z){
    while(z->pai->cor == VERMELHO){
        if(z->pai == z->pai->pai->esquerda){
            No* tio = z->pai->pai->direita;

            if(tio->cor == VERMELHO){
                // Caso 1
                z->pai->cor = PRETO;
                tio->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            }
            else{
                if(z == z->pai->direita){
                    // Caso 2
                    z = z->pai;
                    rotacao_esquerda(arvore, z);
                }

                // Caso 3
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacao_direita(arvore, z->pai->pai);
            }
        }
        else{
            // Espelho dos casos acima
            No* tio = z->pai->pai->esquerda;

            if(tio->cor == VERMELHO){
                // Caso 4
                z->pai->cor = PRETO;
                tio->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            }
            else{
                if(z == z->pai->esquerda){
                    // Caso 5
                    z = z->pai;
                    rotacao_direita(arvore, z);
                }

                // Caso 6
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacao_esquerda(arvore, z->pai->pai);
            }
        }
    }

    arvore->raiz->cor = PRETO;
}

void inserir(ArvoreRN* arvore, int chave){
    No* novo = criar_no(arvore, chave);
    No* y = arvore->nulo;
    No* x = arvore->raiz;

    while(x != arvore->nulo){
        y = x;

        if(novo->chave < x->chave){
            x = x->esquerda;
        }
        else{
            x = x->direita;
        }
    }

    novo->pai = y;

    if(y == arvore->nulo){
        arvore->raiz = novo;
    }
    else if(novo->chave < y->chave){
        y->esquerda = novo;
    }
    else{
        y->direita = novo;
    }

    novo->esquerda = novo->direita = arvore->nulo;
    novo->cor = VERMELHO;

    corrigir_insercao(arvore, novo);
}

void transplante(ArvoreRN* arvore, No* u, No* v){
    if(u->pai == arvore->nulo){
        arvore->raiz = v;
    }
    else if(u == u->pai->esquerda){
        u->pai->esquerda = v;
    }
    else{
        u->pai->direita = v;
    }

    v->pai = u->pai;
}

No* minimo(ArvoreRN* arvore, No* no){
    while(no->esquerda != arvore->nulo){
        no = no->esquerda;
    }
    return no;
}

void corrigir_remocao(ArvoreRN* arvore, No* x){
    while(x != arvore->raiz && x->cor == PRETO){
        if(x == x->pai->esquerda){
            No* w = x->pai->direita;

            if(w->cor == VERMELHO){ // Caso 1
                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                rotacao_esquerda(arvore, x->pai);
                w = x->pai->direita;
            }

            if(w->esquerda->cor == PRETO && w->direita->cor == PRETO){ // Caso 2
                w->cor = VERMELHO;
                x = x->pai;
            }
            else{
                if(w->direita->cor == PRETO){ // Caso 3
                    w->esquerda->cor = PRETO;
                    w->cor = VERMELHO;
                    rotacao_direita(arvore, w);
                    w = x->pai->direita;
                }

                // Caso 4
                w->cor = x->pai->cor;
                x->pai->cor = PRETO;
                w->direita->cor = PRETO;
                rotacao_esquerda(arvore, x->pai);
                x = arvore->raiz;
            }
        }
        else{
            // Espelho dos casos acima
            No* w = x->pai->esquerda;

            if(w->cor == VERMELHO){ // Caso 1
                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                rotacao_direita(arvore, x->pai);
                w = x->pai->esquerda;
            }

            if(w->direita->cor == PRETO && w->esquerda->cor == PRETO){ // Caso 2
                w->cor = VERMELHO;
                x = x->pai;
            }
            else{
                if(w->esquerda->cor == PRETO){ // Caso 3
                    w->direita->cor = PRETO;
                    w->cor = VERMELHO;
                    rotacao_esquerda(arvore, w);
                    w = x->pai->esquerda;
                }

                // Caso 4
                w->cor = x->pai->cor;
                x->pai->cor = PRETO;
                w->esquerda->cor = PRETO;
                rotacao_direita(arvore, x->pai);
                x = arvore->raiz;
            }
        }
    }

    x->cor = PRETO;
}

void remover(ArvoreRN* arvore, No* z){
    No* y = z;
    No* x;
    Cor cor_original = y->cor;

    if(z->esquerda == arvore->nulo){
        x = z->direita;
        transplante(arvore, z, z->direita);
    }
    else if(z->direita == arvore->nulo){
        x = z->esquerda;
        transplante(arvore, z, z->esquerda);
    }
    else{
        y = minimo(arvore, z->direita);
        cor_original = y->cor;
        x = y->direita;

        if(y->pai == z){
            x->pai = y;
        }
        else{
            transplante(arvore, y, y->direita);
            y->direita = z->direita;
            y->direita->pai = y;
        }

        transplante(arvore, z, y);
        y->esquerda = z->esquerda;
        y->esquerda->pai = y;
        y->cor = z->cor;
    }

    if(cor_original == PRETO){
        corrigir_remocao(arvore, x);
    }

    free(z);
}