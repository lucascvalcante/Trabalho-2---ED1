#ifndef VISIBILIDADE_H
#define VISIBILIDADE_H
#include "poligono.h"


typedef void* Ponto;
/*
    Arquivo .h relacionado ao algortimo da região de visibilidade da bomba
*/


/// @brief Aloca e inicializa um novo ponto
/// @param x Coordenada x do novo ponto
/// @param y Coordenada y do novo ponto
/// @return Um ponteiro para o novo ponto
Ponto init_ponto(double x, double y);


/// @brief Retorna a coordenada X do ponto P
/// @param p Ponteiro apontando para o ponto
/// @return A coordenada X
double get_ponto_x(Ponto p);


/// @brief Retorna a coordenada Y do ponto P
/// @param p Ponteiro apontando para o ponto
/// @return A coordenada Y
double get_ponto_y(Ponto p);


/// @brief Retorna a memória alocada pelo ponto
/// @param p Ponteiro apontando para o ponto
void free_ponto(Ponto p);


/// @brief Calcula e retorna a região de visibilidade(polígono) a partir de um ponto de origem
/// @param origem Ponto de origem
/// @param anteparos Lista de anteparos
/// @param tipo_ord Tipo de ordenação, 'q' para qsort e 'm' para mergesort
/// @param raio_max Alcance máximo da bomba
/// @param threshold_i Limite para insertionSort no mergesort
/// @return Polígono da região de visibilidade da explosão
Poligono calc_regiao_visibilidade(Ponto origem, Lista anteparos, char tipo_ord, double raio_max, int threshold_i);


#endif