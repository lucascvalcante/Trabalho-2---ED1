#ifndef COLISAO_H
#define COLISAO_H
#include "stdbool.h"
#include "formas.h"
#include "circulo.h"
#include "retangulo.h"
#include "texto.h"
#include "linha.h"
#include "poligono.h"

/* 
    Arquivo .h relacionado a 'colisões', checando se duas formas se sobrepõem 
*/


/// @brief Verifica se duas formas genéricas se sobrepõem
/// @param f1 Ponteiro para a primeira forma genérica 
/// @param f2 Ponteiro para a segunda forma genérica 
/// @return 'True' se eles se sobrepõem, 'false' se eles não se sobrepõem 
bool FormaSobrepoe(Forma f1, Forma f2);



/// @brief Verifica se uma forma e um polígono se sobrepõem
/// @param f Ponteiro apontando para a forma
/// @param p Ponteiro apontando para o polígono
/// @return 'True' se eles se sobrepõem, 'false' se eles não se sobrepõem 
bool FormaSobrepoePoligono(Forma f, Poligono p);



#endif