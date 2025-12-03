#ifndef ARVORE_H
#define ARVORE_H
#include "stdbool.h"

typedef void *Arvore;
/*
    Arquivov .h relacionado a uma árvore de busca
*/

/// @brief Função de comparação
/// retorna < 0 se (a < b)
/// 0 se (a == b)
/// > 0 se (a > b)
typedef int (*ComparadorArv)(void *a, void *b); 


/// @brief Função de visita, usada para desenhar no svg, imprimir ou reportar dados
/// @param dado Dado armazenado no nó
/// @param aux Ponteiro auxiliar
typedef void (*Visita)(void *dado, void *aux);


/// @brief Cria uma nova árvore vazia
/// @param comp Função que define a regra de ordenação da árvore
/// @return Ponteiro para a árvore criada
Arvore Criar_arv(ComparadorArv comp);


/// @brief Insere um elemento na árvore
/// @param arv Ponteiro apontando para a árvore
/// @param dado o dado genérico que será inserido
/// @return 'True' se a inserção for bem sucedidda
bool InsertArv(Arvore arv, void* dado);


/// @brief Realiza a operação de busca em um elemento da árvore
/// @param arv Ponteiro apontando para a árvore
/// @param chave Chave ponteiro contendo a chave e busca
/// @return O dado encontrado ou 'NULL' caso não encontrar nada
void* searchArv(Arvore arv, void* chave);


/// @brief Remove um elemento da árvore 
/// @param arv Ponteiro apontando para a árvore
/// @param chave A chave do elemento a ser removido
/// @param destruir Funçao para liberar a memória do dado
/// @return 'True se a remoçao foi bem sucedida
bool removeArv(Arvore arv, void* chave, Visita destruir);


/// @brief Percorre a árvore em ordem
/// @param arv Ponteiro apontando para árvore
/// @param visita Função para percorrer os elementos da árvore
/// @param aux Ponteiro auxiliar
/// @details Ideal para imprimir a árvore em relatórios ordenados
void traverseArv(Arvore arv, Visita visita, void* aux);


/// @brief Libera toda a memória ocupada pela árvore
/// @param arv Ponteiro apontando para a árvore
/// @param destruir Função que libera a memória ocupada por todos os elementos da árvore
void killArv(Arvore arv, Visita destruir);


/// @brief Retorna a altura da árvore
/// @param arv Ponteiro apontando para a árvore
/// @return A altura
int Get_altura(Arvore arv);

#endif