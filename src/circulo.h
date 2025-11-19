#ifndef CIRCULO_H
#define CIRCULO_H

typedef void *Circulo;
/*
    Arquivo .h relacionado a um círculo, com funções de set, get e cálculo de área
*/


/// @brief Função que cria e retorna um círculo com os atributos fornecidos
/// @param id Número de identificação do círculo
/// @param x Coordenada X do centro do círculo
/// @param y Coordenada Y do centro do círculo
/// @param r Raio do círculo
/// @param corb Cor da borda do círculo
/// @param corp Cor do preenchimento do círculo
/// @return Retorna o círculo criado
Circulo Criar_Circulo(int id, double x, double y, double r, char *corb, char *corp);


/// @brief Retorna o número de identificação do círculo 
/// @param c O círculo 
/// @return O número de identificação
int GetIDCirculo(Circulo c); 


/// @brief Retorna a coordenada X em relação ao centro do círculo
/// @param c O círculo
/// @return A coordenada X
double GetXCirculo(Circulo c);


/// @brief Retorna a coordenada Y em relação ao centro do círculo
/// @param c O círculo
/// @return A coordenada Y
double GetYCirculo(Circulo c);


/// @brief Retorna o raio do círculo
/// @param c O círculo
/// @return O raio
double GetRCirculo(Circulo c);


/// @brief Retorna a cor de preenchimento do círculo
/// @param c O círculo
/// @return A cor de preenchimento
char *GetCorpCirculo(Circulo c);


/// @brief Retorna a cor da borda do círculo
/// @param c O círculo
/// @return A cor da borda
char *GetCorbCirculo(Circulo c);


/// @brief Define um número de identificação para o círculo
/// @param c O círculo
/// @param id O novo número de identificação
void SetIDCirculo(Circulo c, int id);


/// @brief Define a coordenada X em relação ao centro do círculo
/// @param c O círculo
/// @param x A nova coordenada X
void SetXCirculo(Circulo c, double x);


/// @brief Define a coordenada Y em relação ao centro do círculo
/// @param c O círculo
/// @param y A nova coordenada Y
void SetYCirculo(Circulo c, double y);


/// @brief Define o raio do círculo 
/// @param c O círculo
/// @param r O novo raio
void SetRCirculo(Circulo c, double r);


/// @brief Define a cor de preenchimento do círculo
/// @param c O círculo
/// @param corp A nova cor de preenchimento
void SetCorpCirculo(Circulo c, char *corp);


/// @brief Define a cor de borda do círculo
/// @param c O círculo
/// @param corb A nova cor de borda
void SetCorbCirculo(Circulo c, char *corb);


/// @brief Calcula e retorna a área do círculo
/// @param c O círculo
/// @return A área calculada
double AreaCirculo(Circulo c);


/// @brief Libera toda a memória armazenada pelo círculo
/// @param c Ponteiro apontando para o círculo
void KillCirculo(Circulo c);


#endif