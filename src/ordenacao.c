#include "ordenacao.h"
#include <stdlib.h>
#include <stdio.h>


/// --- Função auxiliar: --- ///

static void merge(void **vetor, int meio, int n, Comparador comp){
    int i = 0;
    int j = meio;
    int k = 0;

    void **aux = malloc(n * sizeof(void*));
    if(aux == NULL){
        fprintf(stderr, "Erro de alocação no mergesort!\n");
        exit(1);
    }

    while (i < meio && j < n) {
        if (comp(vetor[i], vetor[j]) <= 0) {
            aux[k++] = vetor[i++];
        } else {
            aux[k++] = vetor[j++];
        }
    }

     while (i < meio) {
        aux[k++] = vetor[i++];
    }

     while (j < n) {
        aux[k++] = vetor[j++];
    }

     for (i = 0; i < n; i++) {
        vetor[i] = aux[i];
    }

    free(aux);
}

/// --- Funções principais : --- ///

void insertionSort(void **vetor, int n, Comparador comp){
    for(int i = 1; i < n; i++){
        void *aux = vetor[i];
        int j = i - 1;
    

        while(j >= 0 && comp(vetor[j], aux) > 0){
            vetor[j+1] = vetor[j];
            j--;
        }
        vetor[j+1] = aux;
    }

}

void mergeSort(void **vetor, int n, Comparador comp, int limiar_insertion){
    if(n <= limiar_insertion){
        insertionSort(vetor, n, comp);
        return;
    }

    int meio = n / 2;

    mergeSort(vetor, meio, comp, limiar_insertion);
    mergeSort(vetor + meio, n - meio, comp, limiar_insertion);

    merge(vetor, meio, n, comp);
}