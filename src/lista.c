#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include <stdbool.h>
#include "formas.h"

typedef struct node{
    Forma forma;
    struct node *prox;
    struct node *ant;
}node;

typedef struct lista{
    node *inicio;
    node *fim;
    int tamanho;
}Stlista;


/// -- Função auxiliar : -- ///

///Remove um nó específico da lista e retorna seu elemento

static Forma removerNo(Lista lista, node *no){
    Stlista *l = ((Stlista*)lista);
    if(l == NULL || no == NULL){
        return NULL;
    }
    
    Forma forma = no->forma;
    if(no->ant != NULL){
        no->ant->prox = no->prox;
    }else{
        l->inicio = no->prox;
    }

    if(no->prox != NULL){
        no->prox->ant = no->ant;
    }else{
        l->fim = no->ant;
    }    
    
    free(no);
    l->tamanho--;
    return forma;
}

/// -- Funções principais : -- ///

Lista Criar_Lista(){
    Stlista *l = malloc(sizeof(Stlista));
    if(l == NULL){
        return NULL;
    }

    l->tamanho = 0;
    l->fim = NULL;
    l->inicio = NULL;

    return ((Stlista*)l);
}


void Destruir_lista(Lista lista, void (*DestruirForma)(void*)){
    Stlista *l = ((Stlista*)lista);
    if(l == NULL){
        return;
    }

    node *atual = l->inicio;
    while(atual != NULL){
        node* prox = atual->prox;

        if(atual->forma != NULL && DestruirForma != NULL){
            DestruirForma(atual->forma);
        }

        free(atual);
        atual = prox;
    }

    free(lista);
}


bool Inserir_inicio(Lista lista, Forma f){
    Stlista *l = ((Stlista*)lista);
    if(l == NULL || f == NULL){
        return false;
    }

    node *novo = malloc(sizeof(node));
    if(novo == NULL){
        printf("Não foi possível alocar memória para o novo nó da lista!\n");
        return false;
    }

    novo->forma = f;

    if(l->inicio == NULL){
        l->inicio = novo;
        l->fim = novo;
        novo->ant = NULL;
        novo->prox = NULL;
    } else{
        novo->ant = NULL;
        novo->prox = l->inicio;
        l->inicio->ant = novo;
        l->inicio = novo;
    }

    l->tamanho++;
    return true;
}


bool Inserir_fim(Lista lista, Forma f){
    Stlista *l = ((Stlista*)lista);
    if(l == NULL || f == NULL){
        return false;
    }
    
    node *novo = malloc(sizeof(node));
    if(novo == NULL){
        printf("Erro ao alocar memória para o novo nó!\n");
        return false;
    }

    novo->forma = f;
    if(l->fim == NULL){
        l->fim = novo;
        l->inicio = novo;
        novo->ant = NULL;
        novo->prox = NULL;
    }else{
        l->fim->prox = novo;
        novo->ant = l->fim;
        l->fim = novo;
        novo->prox = NULL;
    }

    l->tamanho++;
    return true;
}


Forma Remover_inicio(Lista lista){
    Stlista *l = ((Stlista*)lista);
    if(l == NULL){
        return NULL;
    }    

    if(l->inicio == NULL){
        return NULL;
    }

    return removerNo(l, l->inicio);
}


Forma Remover_fim(Lista lista){
    Stlista *l = ((Stlista*)lista);
    if(l == NULL){
        return NULL;
    }
    
    if(l->fim == NULL){
        return NULL;
    }

    return removerNo(l, l->fim);
}


bool RemoverElemento(Lista lista, Forma f){
    Stlista *l = ((Stlista*)lista);
    if(l == NULL || f == NULL){
        return false;
    }    

    node *atual = l->inicio;
    while(atual != NULL){
        if(atual->forma == f){
            removerNo(l, atual);
            return true;
        }
        atual = atual->prox;
    }

    return false;
}


Forma Remover_condicional(Lista lista, bool (*condicao)(void*, void*), void* contexto){
    Stlista *l = ((Stlista*)lista);
    if(l == NULL || condicao == NULL){
        return NULL;
    }
    
    node *atual = l->inicio;
    while(atual != NULL){
        if(condicao(atual->forma, contexto)){
            return removerNo(l, atual);
        }
        atual = atual->prox;
    }

    return NULL;
}


Forma Buscar_elemento(Lista lista, bool (*condicao)(void*, void*), void* contexto){
    Stlista *l = ((Stlista*)lista);
    if(l == NULL || condicao == NULL){
        return NULL;
    }
    
    node *atual = l->inicio;
    while(atual != NULL){
        if(condicao(atual->forma, contexto)){
            return atual->forma;
        }
        atual = atual->prox;
    }

    return NULL;
}


void Percorrer_lista(Lista lista, void (*acao)(void*, void*), void* contexto){
    Stlista *l = ((Stlista*)lista);
    if(l == NULL || acao == NULL){
        return;
    }
    
    node *atual = l->inicio;
    while(atual != NULL){
        acao(atual->forma, contexto);
        atual = atual->prox;
    }
}

int Contar_lista(Lista lista, bool (*condicao)(void*, void*), void* contexto){
    Stlista *l = ((Stlista*)lista);
    if(l == NULL || condicao == NULL){
        return 0;
    }

    int cont = 0;
    node *atual = l->inicio;
    while(atual != NULL){
        if(condicao(atual->forma, contexto)){
            cont++;
        }
        atual = atual->prox;
    }
    return cont;
}

bool Lista_vazia(Lista lista){
    Stlista *l = ((Stlista*)lista);
    return (l == NULL || l->inicio == NULL);
}

int Tamanho_lista(Lista lista){
    Stlista *l = ((Stlista*)lista);
    if(l == NULL){
        return 0;
    }

    return l->tamanho;
}

Lista Filtrar_lista(Lista lista, bool (*condicao)(void*, void*), void* contexto){
    Stlista *l = ((Stlista*)lista);
    if(l == NULL || condicao == NULL){
        return NULL;
    }

    node *atual = l->inicio;
    Lista filtrada = Criar_Lista();
    Stlista *lf = ((Stlista*)filtrada);

    if(filtrada == NULL){
        return NULL;
    }

    while(atual != NULL){
        if(condicao(atual->forma, contexto)){
            if(!Inserir_fim(lf, atual->forma)){
                Destruir_lista(filtrada, NULL);
                return NULL;
            }
        }
        atual = atual->prox;
    }

    return filtrada;
}





