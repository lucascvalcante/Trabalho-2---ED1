#ifndef RETANGULO_H
#define RETANGULO_H

typedef void *Retangulo;
/*
    Arquivo .h relacionado a um retângulo, com funções de set, get e cálculo de área
*/


/// @brief Função que cria e retorna um retângulo com os atributos fornecidos
/// @param i Número de identificação do retângulo
/// @param x Coordenada X da âncora do retângulo
/// @param y Coordenada Y da âncora do retângulo
/// @param w Largura do retângulo
/// @param h Altura do retângulo
/// @param corb Cor de borda do retângulo
/// @param corp Cor de preenchimento do retângulo
/// @return Retorna o retângulo criado
Retangulo Criar_Retangulo(int i, double x, double y, double w, double h, char *corb, char *corp);


/// @brief Retorna o número de identificação do retângulo
/// @param r O retângulo
/// @return o Número de identicação
int GetIDRetangulo(Retangulo r);


/// @brief Retorna a coordenada X da âncora do retângulo
/// @param r O retângulo
/// @return A coordenada X da âncora
double GetXRetangulo(Retangulo r);


/// @brief Retorna a coordenada Y da âncora do retângulo
/// @param r O retângulo
/// @return A coordenada Y da âncora
double GetYRetangulo(Retangulo r);


/// @brief Retorna a largura do retângulo
/// @param r O retângulo
/// @return A largura
double GetWRetangulo(Retangulo r);


/// @brief Retorna a altura do retângulo
/// @param r O retângulo
/// @return A altura
double GetHRetangulo(Retangulo r);


/// @brief Retorna a cor de preenchimento do retângulo
/// @param r O retângulo
/// @return A cor de preenchimento
char *GetCorpRetangulo(Retangulo r);


/// @brief Retorna a cor da borda do retângulo
/// @param r O retângulo
/// @return A cor de borda
char *GetCorbRetangulo(Retangulo r);


/// @brief Define o número de identificação do retângulo
/// @param r O retângulo 
/// @param i O novo número de identificação 
void SetIDRetangulo(Retangulo r, int id);


/// @brief Define a coordenada X da âncora do retângulo
/// @param r O retângulo 
/// @param i A nova coordenada X
void SetXRetangulo(Retangulo r, double x);


/// @brief Define a coordenada Y da âncora do retângulo
/// @param r O retângulo 
/// @param i A nova coordenada Y
void SetYRetangulo(Retangulo r, double y);


/// @brief Define a largura do retângulo
/// @param r O retângulo 
/// @param i A nova largura
void SetWRetangulo(Retangulo r, double w);


/// @brief Define a altura do retângulo
/// @param r O retângulo 
/// @param i A nova altura
void SetHRetangulo(Retangulo r, double h);


/// @brief Define a cor de preenchimento do retângulo
/// @param r O retângulo 
/// @param i A nova cor de preenchimento
void SetCorpRetangulo(Retangulo r, char *corp);


/// @brief Define a cor da borda do retângulo
/// @param r O retângulo 
/// @param i A nova cor da borda
void SetCorbRetangulo(Retangulo r, char *corb);


/// @brief Calcula e retorna a área do retângulo
/// @param r O retângulo 
/// @param i A área calculada
double AreaRetangulo(Retangulo r);


/// @brief Libera toda a memória alocada pelo retângulo 
/// @param r Ponteiro apontando para o retângulo
void KillRetangulo(Retangulo r);


#endif