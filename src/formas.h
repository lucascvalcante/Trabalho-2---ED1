#ifndef FORMAS_H
#define FORMAS_H
#include <stdio.h>

/* 
    Arquivo .h Relacionado a formas, permitindo que diferentes formas sejam tratadas de maneira uniforme.
*/


/// @brief "Enum" que define os tipos de formas presentes
typedef enum Tipo_Forma{
    CIRCULO,
    LINHA,
    RETANGULO,
    TEXTO,
}Tipo_Forma;


typedef void *Forma;


/// @brief Cria e retorna um ponteiro para uma forma genérica
/// @param tipo O tipo da forma(Circulo, retângulo, etc)
/// @param dados Um ponteiro para a forma ja criada
/// @return Um ponteiro para a forma genérica
Forma Criar_Forma(Tipo_Forma tipo, void *dados);


/// @brief Libera memória alocada de uma forma genérica 
/// @param f A forma a ser destruída
void DestruirForma(Forma f);


/// @brief Retorna o tipo da forma(Circulo, retãngulo, etc)
/// @param f A forma
/// @return O tipo da forma
Tipo_Forma GetTipoForma(Forma f);


/// @brief Obtém e retorna um ponteiro para os dados da forma 
/// @param f A forma
/// @return O ponteiro para os dados da forma
void *GetDadosForma(Forma f);


/// @brief Calcula e retorna a área da forma genérica
/// @param f A forma
/// @return O calculo da área
double GetAreaForma(Forma f);


/// @brief Define a posição de uma forma genérica
/// @param f A forma 
/// @param x A posição na coordenada X
/// @param y A posição na coordenada Y
void SetPosicaoForma(Forma f, double x, double y);


/// @brief Insere os dados de uma forma qualquer em um arquivo .txt
/// @param f Ponteiro apontando para uma forma genérica
/// @param txt Arquivo txt no qual será feito o relatório das formas
/// @param reportQry Início padrão do .qry
void InserirDadosTxt(Forma f, FILE *txt, char *reportQry);


/// @brief Retorna a coordenada X de uma forma genérica
/// @param f Ponteiro apontando para a forma
/// @return A coordenada X
double GetXForma(Forma f);


/// @brief Retorna a coordenada Y de uma forma genérica
/// @param f Ponteiro para a forma
/// @return A coordenada Y
double GetYForma(Forma f);


/// @brief Retorna o número de identificação de uma forma genérica
/// @param f Ponteiro para a forma
/// @return O número de identificação 
int GetIDForma(Forma f);


/// @brief Retorna a cor de preenchimento da forma
/// @param f Ponteiro apontando para a forma 
/// @return A cor de preenchimento
char *GetCorpForma(Forma f);


/// @brief Retorna a cor de borda de uma forma;
/// @param f Ponteiro apontando para a forma 
/// @return A cor de borda
char *GetCorbForma(Forma f);


/// @brief Cria um cópia de uma forma qualquer
/// @param f Ponteiro apontando para a forma
/// @return Ponteiro para a forma clonada
Forma ClonarForma(Forma f);


/// @brief Retorna o nome da cor complementar para uma cor de entrada
/// @param cor_original A cor original
/// @return A cor complementar
char *GetCorComplementar(const char* cor_original);


/// @brief Define a cor de borda para uma forma qualquer 
/// @param f Ponteiro apontando para a forma
/// @param corb A cor de borda que será inserida
void SetCorbForma(Forma f, char *corb);


/// @brief Define a cor de preecnhimento para uma forma qualquer 
/// @param f Ponteiro apontando para a forma
/// @param corb A cor de preecnhimento que será inserida
void SetCorpForma(Forma f, char *corp);


/// @brief Troca a cor de borda com a cor de preenchimento de uma mesma forma
/// @param f Ponteiro apontando para a forma
void TrocaCoresForma(Forma f);


#endif