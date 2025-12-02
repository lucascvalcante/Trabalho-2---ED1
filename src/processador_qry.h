#ifndef PROCESSADOR_QRY_H
#define PROCESSADOR_QRY_H
#include "lista.h"
#include "svg.h"


/// @brief Processa o arquivo de consultas (.qry). Lê os comandos do arquivo .qry e executa as operações
/// correspondentes, gerando relatórios em TXT e desenhos em SVG
/// @param path_qry Caminho completo para o arquivo de entrada .qry
/// @param path_txt Caminho completo para o arquivo de relatório .txt (saída)
/// @param formas Lista contendo as formas lidas do .geo 
/// @param anteparos Lista  onde serão guardados os segmentos gerados pelo comando 'a'
/// @param path_saida Diretório base para salvar os SVGs gerados pelas bombas
/// @param nome_base_geo Nome base do arquivo geo para compor nomes de arquivos
/// @param svg_final Ponteiro para o arquivo SVG principal
/// @param threshold_i Limiar para o InsertionSort
/// @param tipo_ord Tipo de ordenação ('m' para merge, 'q' para qsort)
void processa_qry(const char* path_qry, const char* path_txt, 
             Lista formas, Lista anteparos, 
             const char* path_saida, const char* nome_base_geo, Svg svg_final,
             int threshold_i, char tipo_ord);


#endif