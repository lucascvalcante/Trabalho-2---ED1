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

    node *elemento = l->inicio;
    Forma forma = elemento->forma;
    if(l->inicio->prox == NULL){
        l->inicio = NULL;
        l->fim = NULL;
    }else{
        l->inicio->prox->ant = NULL;
        l->inicio = l->inicio->prox;
    }

    free(elemento);
    l->tamanho--;
    return forma;
}


Forma Remover_fim(Lista lista){
    Stlista *l = ((Stlista*)lista);
    if(l == NULL){
        return NULL;
    }
    
    if(l->fim == NULL){
        return NULL;
    }

    node* elemento = l->fim;
    Forma forma = elemento->forma;

    if(l->fim->ant == NULL){
        l->fim = NULL;
        l->inicio = NULL;
    }else{
        l->fim->ant->prox = NULL;
        l->fim = l->fim->ant;
    }

    free(elemento);
    l->tamanho--;
    return forma;
}


