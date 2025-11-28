#include "arvore.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct node{
    void *dado;
    struct node *esq;
    struct node *dir;
}node;

typedef struct arvore{
    node *raiz;
    Comparador comp;
}stArvore;

/// --- Funções auxiliares privadas: --- ///

static node *NewNode(void *dado){
    node *novo = malloc(sizeof(node));
    if(novo ==  NULL){
        return NULL;
    }
    novo->dado = dado;
    novo->dir = NULL;
    novo->esq = NULL;
    return novo;
}

static node *InserirRecursivo(node *no, void *dado, Comparador comp, bool *inseriu){
    if(no == NULL){
        *inseriu = true;
        return NewNode(dado);
    }

    int cmp = comp(dado, no->dado);

    if(cmp < 0){
        no->esq = InserirRecursivo(no->esq, dado, cmp, inseriu);
    }else if(cmp > 0){
        no->dir = InserirRecursivo(no->dir, dado, cmp, inseriu);
    }else{
        *inseriu = false;
    }

    return no;
}

static void *BuscarRecursivo(node *no, void *chave, Comparador comp){
    if(no == NULL){
        return NULL;
    }

    int cmp = comp(chave, no->dado);

    if(cmp < 0){
        return BuscarRecursivo(no->esq, chave, cmp);
    }else if(cmp > 0){
        return BuscarRecursivo(no->dir, chave, cmp);
    }else{
        return no->dado;
    }
}

static node *encontrarMinimo(node *no){
    while(no->esq != NULL){
        no = no->esq;
    }

    return no;
}


static node *removerRecursivo(node *no, void *chave, Comparador comp, Visita destruir, bool *removeu){
    if(no == NULL){
        *removeu = false;
        return NULL;
    }

    int cmp = comp(chave, no->dado);

    if(cmp < 0){
        no->esq = removerRecursivo(no->esq, chave, cmp, destruir, removeu);
    }else if(cmp > 0){
        no->dir = removerRecursivo(no->dir, chave, cmp, destruir, removeu);
    }else{
        *removeu = true;

        if(no->esq == NULL){
            node *temp = no->dir;
            if(destruir != NULL) destruir(no->dado, NULL);
            free(no);
            return temp;
        }else if(no->dir ==  NULL){
            node *temp = no->esq;
            if(destruir != NULL) destruir(no->dado, NULL);
            free(no);
            return temp;
        }

        node *temp = encontrarMinimo(no->dir);
        if(destruir != NULL) destruir(no->dado, NULL);
        no->dado = temp->dado;
        no->dir = removerRecursivo(no->dir, no->dado, cmp, NULL, removeu);
    }

    return no;
}

static void traverseRecursivo(node *no, Visita visita, void *aux){
    if(no != NULL){
        traverseRecursivo(no->esq, visita, aux);
        visita(no->dado, aux);
        traverseRecursivo(no->dir, visita, aux);
    }
}

static void KillRecursivo(node *no, Visita destruir){
    if(no != NULL){
        KillRecursivo(no->esq, destruir);
        KillRecursivo(no->dir, destruir);

        if(destruir != NULL){
            destruir(no->dado, NULL);
        }
        free(no);
    }
}

static int AlturaRecursiva(node *no){
    if(no == NULL){
        return -1;
    }

    int esq = AlturaRecursiva(no->esq);
    int dir = AlturaRecursiva(no->dir);
    return(esq > dir ? esq : dir) + 1;
}

/// --- Funções principais públicas : --- ///

Arvore Criar_arv(Comparador comp){
    stArvore *arv = malloc(sizeof(stArvore));
    if(arv == NULL){
        return NULL;
    }
    arv->raiz = NULL;
    arv->comp = comp;

    return ((stArvore*)arv);
}

bool InsertArv(Arvore arvore, void *dado){
    stArvore *arv = ((stArvore*)arvore);
    if(arv == NULL || dado == NULL){
        return false;
    }

    bool inseriu = false;
    arv->raiz = InserirRecursivo(arv->raiz, dado, arv->comp, &inseriu);
    return inseriu;
}

void *searchArv(Arvore arvore, void *chave){
    stArvore *arv = ((stArvore*)arvore);
    if(arv == NULL || chave == NULL){
        return;
    }    

    return BuscarRecursivo(arv->raiz, chave, arv->comp);
}

bool removeArv(Arvore arvore, void *chave, Visita destruir){
    stArvore *arv = ((stArvore*)arvore);
    if(arv == NULL || chave == NULL){
        return false;
    }    
    
    bool removeu = false;
    arv->raiz = removerRecursivo(arv->raiz, chave, arv->comp, destruir, removeu);
    return removeu;
}

void killArv(Arvore arvore, Visita destruir){
    stArvore *arv = ((stArvore*)arvore);
    if(arv == NULL){
        return;
    }     

    KillRecursivo(arv->raiz, destruir);
    free(arv);
}

int Get_altura(Arvore arvore){
    stArvore *arv = ((stArvore*)arvore);
    if(arv == NULL){
        return 0;
    } 

    return AlturaRecursiva(arv->raiz);
    
}