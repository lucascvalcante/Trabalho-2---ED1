#include "processador_geo.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "linha.h"
#include "texto.h"
#include "retangulo.h"
#include "circulo.h"
#include "formas.h"


/// @brief estrutura interna usada para controlar o estado do estilo
typedef struct estilo{
    char familia[64];
    char peso[16];
    char tamanho[16];
}StEstilo;

/// --- Funções privadas auxiliares: --- ///

static void extrair_texto(const char *linha, int offset, char *destino, size_t max){
    if(offset <= 0){
        destino[0] = '\0';
        return;
    }
    const char *inicio = linha + offset;
    while(*inicio && (*inicio == ' ' || *inicio == '\t')){
        inicio++;
    }

    strncpy(destino, inicio, max - 1);
    destino[max - 1] = '\0';
    destino[strcspn(destino, "\r\n")] = '\0';
}

static void processar_circulo(const char* linha, Lista lista) {
    int id; 
    double x, y, r;
    char corb[64], corp[64];

    if (sscanf(linha, "c %d %lf %lf %lf %s %s", &id, &x, &y, &r, corb, corp) == 6) {
        Circulo c = Criar_Circulo(id, x, y, r, corb, corp);
        Forma f = Criar_Forma(CIRCULO, c);
        Inserir_fim(lista, f);
    }
}

static void processar_retangulo(const char* linha, Lista lista) {
    int id; double x, y, w, h;
    char corb[64], corp[64];

    if (sscanf(linha, "r %d %lf %lf %lf %lf %s %s", &id, &x, &y, &w, &h, corb, corp) == 7) {
        Retangulo r = Criar_Retangulo(id, x, y, w, h, corb, corp);
        Forma f = Criar_Forma(RETANGULO, r);
        Inserir_fim(lista, f);
    }
}

static void processar_linha(const char* linha, Lista lista) {
    int id; double x1, y1, x2, y2;
    char cor[64];

    if (sscanf(linha, "l %d %lf %lf %lf %lf %s", &id, &x1, &y1, &x2, &y2, cor) == 6) {
        Linha l = Criar_Linha(id, x1, y1, x2, y2, cor);
        Forma f = Criar_Forma(LINHA, l);
        Inserir_fim(lista, f);
    }
}

static void processar_texto(const char* linha, Lista lista, StEstilo *est_atual) {
    int id; double x, y;
    char corb[64], corp[64], ancora;
    int offset = 0;

    if (sscanf(linha, "t %d %lf %lf %s %s %c %n", &id, &x, &y, corb, corp, &ancora, &offset) >= 6) {
        char conteudo[256];
        extrair_texto(linha, offset, conteudo, sizeof(conteudo));
        Estilo e = NULL;
        Texto t = Criar_Texto(id, x, y, corb, corp, ancora, conteudo, e);
        Forma f = Criar_Forma(TEXTO, t);
        Inserir_fim(lista, f);
    }
}

static void processar_estilo(const char* linha, StEstilo *est) {
    sscanf(linha, "ts %s %s %s", est->familia, est->peso, est->tamanho);

}

/// --- Função principal pública : --- ///

Lista ProcessaGeo(const char *caminhoGeo){
    FILE *geo = fopen(caminhoGeo, "r");
    if(geo == NULL){
        printf("Erro ao abrir o arquivo .geo!\n");
        exit(1);
    }

    StEstilo estilo_atual = {"sans", "normal", "12px"};
    char buffer[1024];
    char comando[16];
    Lista lista = Criar_Lista();
    if(lista == NULL){
        fclose(geo);
        return NULL;
    }

    while(fgets(buffer, sizeof(buffer), geo)){
        if(buffer[0] == '\n' || buffer[0] == '#') continue;

        if(sscanf(buffer, "%s", comando) == 1){
            if(strcmp(comando, "c") == 0) processar_circulo(buffer, lista);
            else if(strcmp(comando, "r") == 0) processar_retangulo(buffer, lista);
            else if(strcmp(comando, "l") == 0) processar_linha(buffer, lista);
            else if(strcmp(comando, "t") == 0) processar_texto(buffer, lista, &estilo_atual);
            else if(strcmp(comando, "ts") == 0) processar_estilo(buffer, &estilo_atual);
        }
    }

    fclose(geo);
    return lista;

}