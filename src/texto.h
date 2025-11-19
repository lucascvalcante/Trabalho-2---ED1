#ifndef TEXTO_H
#define TEXTO_H

typedef void *Texto;
typedef void *Estilo;
/*
    Arquivo .h relacionado a um texto, com operações de get, set, cálculo de área e manipulação do estilo de texto
*/


/// @brief Função que cria e rotorna um estilo de texto
/// @param fFamily Família da fonte
/// @param fWeight Weight da fonte
/// @param fSize Tamanho da fonte
/// @return O estilo criado
Estilo Criar_Estilo(char *fFamily, char *fWeight, char *fSize);



/// @brief Função que criar e retorna um texto com os atributos selecionados
/// @param id Número de identificação do texto
/// @param x Coordenada X do texto
/// @param y Coordenada Y do texto
/// @param corb Cor da borda do texto
/// @param corp Cor de preenchimento do texto
/// @param a Posição da âncora do texto
/// @param txto O conteúdo do texto
/// @param st O estilo do texto
/// @return O texto
Texto Criar_Texto(int id, double x, double y, char *corb, char *corp, char a, char *txto, Estilo st);


/// @brief Retorna a família da fonte do texto
/// @param st O estilo
/// @return A família
char *GetfFamily(Estilo st);


/// @brief Retorna o weight da fonte do texto
/// @param st O estilo 
/// @return O weight
char *GetfWeight(Estilo st);


/// @brief Retorna o tamanho da fonte do texto
/// @param st O estilo 
/// @return O tamanho
char *GetfSize(Estilo st);


/// @brief Define a família da fonte do texto
/// @param st O estilo
/// @param fFamily A nova familia da fonte
void SetfFamily(Estilo st, char *fFamily);


/// @brief Define a weight da fonte do texto
/// @param st O estilo
/// @param fWeight A nova weight da fonte
void SetfWeight(Estilo st, char *fWeight);

/// @brief Define o tamanho da fonte do texto
/// @param st O estilo
/// @param fSize O novo tamanho da fonte
void SetfSize(Estilo st, char *fSize);


/// @brief Retorna o número de identificação do texto
/// @param t O texto
/// @return O número de identificação
int GetIDTexto(Texto t);


/// @brief Retorna a coordenada X do texto
/// @param t O texto
/// @return A coordenada X
double GetXTexto(Texto t);


/// @brief Retorna a coordenada Y do texto
/// @param t O texto
/// @return A coordenada Y
double GetYTexto(Texto t);


/// @brief Retorna a cor da borda do texto
/// @param t O texto
/// @return A cor da borda
char *GetCorbTexto(Texto t);


/// @brief Retorna a cor de preenchimento do texto
/// @param t O texto
/// @return A cor de preenchimento
char *GetCorpTexto(Texto t);


/// @brief Retorna a posição da âncora do texto(i: inicio, m: meio, f: fim)
/// @param t O texto
/// @return A posição do texto
char GetATexto(Texto t);


/// @brief Retorna o conteúdo do texto
/// @param t O texto
/// @return O conteúdo
char *GetTxtoTexto(Texto t);


/// @brief Retorna o estilo do texto
/// @param t O texto
/// @return O estilo
Estilo GetEstilo(Texto t);


/// @brief Define o número de identificação do texto
/// @param t O texto
/// @param id O novo número de identificação
void SetIDTexto(Texto t, int id);


/// @brief Define a coordenada X do texto do texto
/// @param t O texto
/// @param x A nova coordenada X
void SetXTexto(Texto t, double x);


/// @brief Define a coordenada Y do texto do texto
/// @param t O texto
/// @param y A nova coordenada Y
void SetYTexto(Texto t, double y);


/// @brief Define a cor da borda do texto
/// @param t O texto
/// @param corb A nova cor da borda
void SetCorbTexto(Texto t, char *corb);


/// @brief Define a cor de preenchimento do texto
/// @param t O texto
/// @param corp A nova cor de preenchimento
void SetCorpTexto(Texto t, char *corp);


/// @brief Define a posição da âncora do texto(i: inicio, m: meio, f: fim)
/// @param t O texto
/// @param a A nova posição da âncora
void SetATexto(Texto t, char a);


/// @brief Define o conteúdo do texto
/// @param t O texto
/// @param txto O novo conteúdo do texto
void SetTxtoTexto(Texto t, char *txto);


/// @brief Calcula e retorna a área do texto
/// @param t O texto
/// @return A área calculada
double AreaTexto(Texto t);


/// @brief Libera toda a memória ocupada pelo texto
/// @param t Ponteiro apontando para o texto
void KillTexto(Texto t);


/// @brief Libera toda a memória ocupada pelo estilo do texto
/// @param st Ponteiro apontando para o estilo
void KillEstilo(Estilo st);


/// @brief Cria um cópia de um estilo com os mesmos dados
/// @param st Estilo original
/// @return Ponteiro para o novo estilo clonado
Estilo CriarCopiaEstilo(Estilo st);


#endif