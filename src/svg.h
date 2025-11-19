#ifndef SVG_H
#define SVG_H

#include "texto.h"
#include "circulo.h"
#include "linha.h"
#include "retangulo.h"
#include "fila.h"
#include "arena.h"
#include "formas.h"

/*
    Arquivo .h relacionado a manipulação do arquivo em formato svg. Com funções para escrever e inserir formas no arquivo
*/

typedef void* Svg;

/// @brief Cria, abre e escreve o cabeçalho SVG em um arquivo
/// @param nomearquivo O nome do arquivo que será criado
/// @return Um ponteiro para a estrutura SVG
Svg CriarSvg(const char* nomearquivo);


/// @brief Insere a forma 'círculo' no svg
/// @param svg Ponteiro para a estrutura svg
/// @param c A forma círculo que será desenhada
void InserirCirculoSvg(Svg svg, Circulo c);


/// @brief Insere a forma 'retângulo' no svg
/// @param svg Ponteiro para a estrutura svg
/// @param r A forma retângulo que será desenhada
void InserirRetanguloSvg(Svg svg, Retangulo r);


/// @brief Insere a forma 'texto' no svg
/// @param svg Ponteiro para a estrutura svg
/// @param t A forma texto que será desenhada
void InserirTextoSvg(Svg svg, Texto t);


/// @brief Insere a forma 'círculo' no svg
/// @param svg Ponteiro para a estrutura svg
/// @param l A forma círculo que será desenhada
void InserirLinhaSvg(Svg svg, Linha l);


/// @brief Finaliza e fecha o arquivo svg
/// @param svg Ponteiro para a estrutura svg
void FinalizarSvg(Svg svg);


/// @brif Recebe uma fila de formas que serão geradas no svg
/// @param path_svg Nome do arquivo .svg
/// @param filaSvg Fila com as formas que serão adicionadas 
void GerarSvg(const char* path_svg, Fila filaSvg);


/// @brief Função para desenhar em um svg uma única forma genérica
/// @param item Forma que será desenhada
/// @param aux Ponteiro para dados auxiliares
void DesenharFormaSvg(void* item, void* aux);


#endif