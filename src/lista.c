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
    Stlista *l = malloc(sizeof(Stlista));
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

        if(atual->forma != NULL){
            DestruirForma(atual->forma);
        }

        free(atual);
        atual = prox;
    }

    free(lista);
}


void Inserir_inicio(Lista lista, Forma f){
    Stlista *l = ((Stlista*)lista);
    if(l == NULL || f == NULL){
        return;
    }

    node *novo = malloc(sizeof(node));
    if(novo == NULL){
        printf("Não foi possível alocar memória para o novo nó da lista!\n");
        return;
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
}


void Inserir_fim(Lista lista, Forma f){
    Stlista *l = ((Stlista*)lista);
    if(l == NULL || f == NULL){
        return;
    }
    
    node *novo = malloc(sizeof(node));
    if(novo == NULL){
        printf("Erro ao alocar memória para o novo nó!\n");
        return;
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


void RemoverElemento(Lista lista, Forma f){
    Stlista *l = ((Stlista*)lista);
    if(l == NULL || f == NULL){
        return NULL;
    }    

    node *atual = l->inicio;
    while(atual != NULL){
        if(atual->forma == f){
            removerNo(l, atual);
            return;
        }
        atual = atual->prox;
    }

    return;
}


Forma Remover_condicional(Lista lista, bool (*condicao)(void*, void*), void* contexto){
    Stlista *l = ((Stlista*)lista);
    if(l == NULL || condicao == NULL){
        return NULL;
    }
    
    node *atual = l->inicio;
    while(atual != NULL){
        if(condicao(atual->forma, contexto)){
            Forma forma = atual->forma;
            removerNo(l, atual);
            free(atual);
            l->tamanho--;
            return forma;
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





