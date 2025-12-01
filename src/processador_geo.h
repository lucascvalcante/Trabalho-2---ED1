#ifndef PROCESSADOR_GEO_H
#define PROCESSADOR_GEO_H
#include "lista.h"



/// @brief Lê um arquivo .geo, cria e insere as formas na lista
/// @param caminhoGeo O caminho para o arquivo.geo a ser lido
/// @return Ponteiro para a lista, preenchido com as formas do arquivo .geo
Lista ProcessaGeo(const char *caminhoGeo);


#endif