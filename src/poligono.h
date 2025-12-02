#ifndef POLIGONO_H
#define POLIGONO_H
#include <stdbool.h>
#include "lista.h"

typedef void* Poligono;
/*
    Arquivo .h relacionado a um polígono
*/

/// @brief Cria um polígono vazio
/// @return O polígono 
Poligono criaPoligono();


/// @brief Insere um vértice no polígono
/// @param p Ponteiro apontando para o polígono
/// @param x Coordenada X do vértice
/// @param y Coordenada Y do vértice
void insertVertice(Poligono p, double x, double y);


/// @brief Insere um segmento no polígono 
/// @param p Ponteiro apontando para o polígono
/// @param seg O segmento que será inserido
void insertSegmento(Poligono p, Linha seg);


/// @brief Calcula o retângulo envolvente (Bounding Box)
/// @param p Ponteiro apontando para o polígono
/// @param x, y  Ponteiros para retornar o canto inferior esquerdo
/// @param w, h Ponteiros para retornar largura e altura 
void getBoundingBox(Poligono p, double *x, double *y, double *w, double *h);


/// @brief Verifica se um ponto está dentro do polígono
/// @param p Ponteiro apontando para o polígono 
/// @param x Coordenada X do ponto
/// @param y Coordenada Y do ponto
/// @return 'true' se estiver dentro, 'false' se não estiver
bool isInside(Poligono p, double x, double y);


/// @brief Retorna a lista de vértices
/// @param p ponteiro apontando para o polígono
/// @return A lista
Lista getVertices(Poligono p);


/// @brief Gera e retorna uma nova lista contendo os segmentos do polígono
/// @param p Ponteiro apontando para o polígono
/// @return A nova lista
Lista getSegmentos(Poligono p);


/// @brief Libera toda a memória alocada pelo polígono
/// @param p Ponteiro apontando para o polígono
void killPoligono(Poligono p);


#endif