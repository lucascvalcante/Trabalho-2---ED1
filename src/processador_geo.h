#ifndef PROCESSADOR_GEO_H
#define PROCESSADOR_GEO_H

#include "chao.h"
#include "texto.h"


/// @brief Lê um arquivo .geo, cria e insere as formas no chão
/// @param caminhoGeo O caminho para o arquivo.geo a ser lido
/// @return Ponteiro para o chão, preenchido com as formas do arquivo .geo
Chao ProcessaGeo(const char *caminhoGeo);


#endif