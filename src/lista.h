#ifndef LISTA_H
#define LISTA_H
#include "formas.h"
#include <stdbool.h>

typedef void* Lista;
/*
    Arquivo .h relacionado a uma lista duplamente encadeada e suas funções básicas.
*/

/// @brief Cria e retorna uma estrutura lista
/// @return Ponteiro para a lista
Lista Criar_Lista();


/// @brief Função que desaloca toda a memória ocupada pela lista
/// @param l Ponteiro apontando para a lista
/// @param Destruir_Elemento Funçã que destrói cada elemento da lista
void Destruir_lista(Lista l, void (*DestruirForma)(void*));


/// @brief Insere um elemento no ínicio da lista
/// @param l Ponteiro apontando para a lista
/// @param f Ponteiro para a forma que será inserida na lista
/// @return 'true' se a inseção for bem sucedida e 'false' se não for
bool Inserir_inicio(Lista l, Forma f);


/// @brief Insere um elemento no final da lista
/// @param l Ponteiro apontando para a lista
/// @param f Ponteiro apontando para a forma que será inserida na lista
/// @return 'true' se a inseção for bem sucedida e 'false' se não for
bool Inserir_fim(Lista l, Forma f);


/// @brief Remove o retorna o primeiro elemento da lista
/// @param l Ponteiro apontando para a lista
/// @return O elemento que foi retirado do ínicio
Forma Remover_inicio(Lista l);


/// @brief Remove e retorna o último elemento da lista
/// @param l Ponteiro apontando para a lista
/// @return O elemento que foi retirado do fim
Forma Remover_fim(Lista l);


/// @brief Remove um elemento específico da lista
/// @param l Ponteiro apontando para a lista
/// @param Ponteiro apontando para a forma que deverá ser removida
/// @return 'true' se a remoção for bem sucedida e 'false' se não for
bool RemoverElemento(Lista l, Forma f);


/// @brief Remove e retorna um elemento da lista caso ele satisfaça uma condição
/// @param l Ponteiro apontando para a lista
/// @param condicao Função que retorna 'true' para o elemento a remover
/// @param contexto Dados auxiliares para a função condição
/// @return Ponteiro para o elemento removido
Forma Remover_condicional(Lista l, bool (*condicao)(void*, void*), void* contexto);


/// @brief Busca um elemento na lista e retorna caso ele esteja lá
/// @param l Ponteiro apontando para a lista
/// @param condicao Função que retorna 'true' quando encontrar
/// @param contexto Dados auxiliares para a função condição
/// @return O elemento que foi encontrado
Forma Buscar_elemento(Lista l, bool (*condicao)(void*, void*), void* contexto);


/// @brief Percorre a lista e aplica uma função em cada elemento
/// @param l Ponteiro apontando para a lista
/// @param condicao Função que será aplicada em cada elemento
/// @param contexto Dados auxiliares para a função condição
void Percorrer_lista(Lista l, void (*acao)(void*, void*), void* contexto);


/// @brief Conta quantos elementos da lista satisfazem determinada condição
/// @param l Ponteiro apontando para a lista
/// @param condicao Função que retorna 'true' para contar
/// @param contexto Dados auxiliares
/// @return Número de elementos que satisfazem a condição
int Contar_lista(Lista l, bool (*condicao)(void*, void*), void* contexto);


/// @brief Confere se a lista está vazia ou não
/// @param l Ponteiro apontando para a lista
/// @return 'true' se estiver vazia, 'false' se não estiver vazia
bool Lista_vazia(Lista l);


/// @brief Retorna o número de elementos presentes na lista
/// @param l Ponteiro apontando para a lista
/// @return Número de elementos da lista
int Tamanho_lista(Lista l);


/// @brief Filtra uma lista pré-existente e cria uma nova lista com os elementos filtrados
/// @param l Ponteiro apontando pra a lista original
/// @param condicao Função que retorna 'true' para incluir
/// @param contexto Dados auxiliares
/// @return A nova lista
Lista Filtrar_lista(Lista l, bool (*condicao)(void*, void*), void* contexto);


#endif