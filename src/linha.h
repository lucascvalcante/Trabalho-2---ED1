#ifndef LINHA_H
#define LINHA_H

typedef void *Linha;
/*
    Arquivo .h relacionado a uma linha, com funções de set, get e cálculo de área
*/

/// @brief 
/// @param id 
/// @param x1 
/// @param y1 
/// @param x2 
/// @param y2 
/// @param cor 
/// @return 
Linha Criar_Linha(int id, double x1, double y1, double x2, double y2, char *cor);


/// @brief Retorna o número de identificação da linha
/// @param l A linha
/// @return O número de identificação
int GetIDLinha(Linha l);


/// @brief Retorna a coordenada X do primeiro ponto da linha
/// @param l A linha
/// @return A coordenada X1
double GetX1Linha(Linha l);


/// @brief Retorna a coordenada Y do primeiro ponto da linha
/// @param l A linha
/// @return A coordenada Y1
double GetY1Linha(Linha l);


/// @brief Retorna a coordenada X do segundo ponto da linha
/// @param l A linha
/// @return A coordenada X2
double GetX2Linha(Linha l);


/// @brief Retorna a coordenada Y do segundo ponto da linha
/// @param l A linha
/// @return A coordenada Y2
double GetY2Linha(Linha l);


/// @brief Retorna a cor da linha
/// @param l A linha
/// @return A cor
char *GetCorLinha(Linha l);


/// @brief Define o número de identificação da linha
/// @param l A linha
/// @param id O novo número de identificação
void SetIDLinha(Linha l, int id);


/// @brief Define a coordenada X do primeiro ponto da linha
/// @param l A linha
/// @param x1 A nova coordenada X1
void SetX1Linha(Linha l, double x1);


/// @brief Define a coordenada Y do primeiro ponto da linha
/// @param l A linha
/// @param y1 A nova coordenada Y1
void SetY1Linha(Linha l, double y1);


/// @brief Define a coordenada X do segundo ponto da linha
/// @param l A linha
/// @param x2 A nova coordenada X2
void SetX2Linha(Linha l, double x2);


/// @brief Define a coordenada Y do segundo ponto da linha
/// @param l A linha
/// @param y2 A nova coordenada Y2
void SetY2Linha(Linha l, double y2);


/// @brief Define a cor da linha
/// @param l A linha
/// @param cor A nova cor
void SetCorLinha(Linha l, char *cor);


/// @brief Calcula e retorna a área da linha
/// @param l A linha
/// @return A área calculada
double AreaLinha(Linha l);

/// @brief Libera toda a memória ocupada pela linha
/// @param l Ponteiro apontando para a linha
void KillLinha(Linha l);

#endif