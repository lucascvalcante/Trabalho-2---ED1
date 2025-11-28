#ifndef ORDENACAO_H
#define ORDENACAO_H
#include <stdlib.h>



/// @brief Função de comparação 
/// retorna < 0 se (a < b)
/// 0 se (a == b)
/// > 0 se (a > b)
typedef int (*Comparador)(const void *a, const void *b);


/// @brief Algoritmo de ordenação por merge sort otimizado
/// @param vetor array de ponteiros a ser ordenado
/// @param n números de elementos no vetor
/// @param comp Função de comparação
/// @param limiar_inserction Tamanho do subvetor onde o algoritmo troca para InsertionSort (parâmetro -i).
void mergeSort(void **vetor, int n, Comparador comp, int limiar_inserction);


/// @brief Algoritmo de ordenaçao por insertion sort
/// @param vetor array de ponteiros a ser ordenado
/// @param n Números de elementos no vetor
/// @param comp Função de comparação
void insertionSort(void **vetor, int n, Comparador comp);



#endif