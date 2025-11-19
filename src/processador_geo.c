#include "processador_geo.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "chao.h"
#include "linha.h"
#include "texto.h"
#include "retangulo.h"
#include "circulo.h"

Chao ProcessaGeo(const char *caminhoGeo){
    FILE *arqGeo = fopen(caminhoGeo, "r");
    if(arqGeo == NULL){
        printf("Não foi possível realizar a leitura do arquivo!\n");
        return NULL;
    }

    char buffer[1024];
    Chao chao = Cria_chao();
    if(chao == NULL){
        printf("Erro ao criar o chão!\n");
        fclose(arqGeo);
        return NULL;
    }
    Estilo estiloAtual = Criar_Estilo("sans-serif", "bold", "30px");

    while (fgets(buffer, sizeof(buffer), arqGeo) != NULL){
        if (buffer[0] == '\n' || buffer[0] == '#') {
            continue;
        }

        char comando[16];
        sscanf(buffer, "%s", comando);

         if (strcmp(comando, "ts") == 0) {
            char fFamily[100], fWeight[100], fSize[100];
            int itens_lidos = sscanf(buffer, "%*s %99s %99s %99s", fFamily, fWeight, fSize);
            if(itens_lidos != 3){
                fprintf(stderr, "ERRO: linha de comando 'ts' ignorada: %s\n", buffer);
                continue;
            }
            
            if(estiloAtual != NULL){
                KillEstilo(estiloAtual);
            }
            estiloAtual = Criar_Estilo(fFamily, fWeight, fSize);
            if(estiloAtual == NULL){
                exit(1);
            }
        }
        else {

            if (strcmp(comando, "c") == 0) {
                int id; double x, y, r; char corb[100], corp[100];
                int itens_lidos = sscanf(buffer, "%*s %d %lf %lf %lf %99s %99s", &id, &x, &y, &r, corb, corp);
                if(itens_lidos != 6){
                    fprintf(stderr, "ERRO: linha de comando 'c' ignorada: %s\n", buffer);
                    continue;
                }
                
                Circulo c = Criar_Circulo(id, x, y, r, corp, corb);
                if(c){
                    Forma f = Criar_Forma(CIRCULO, c);
                    if(f){
                        InserirChao(chao, f);
                    }else{
                        KillCirculo(c);
                    }
                }
            }
            else if (strcmp(comando, "r") == 0) {
            int id; double x, y, w, h; char corb[100], corp[100];
            int itens_lidos = sscanf(buffer, "%*s %d %lf %lf %lf %lf %99s %99s", &id, &x, &y, &w, &h, corb, corp);
            if(itens_lidos != 7){
                fprintf(stderr, "ERRO: Linha de comando 'r' ignorada: %s\n", buffer);
                continue;
            }

                Retangulo rt = Criar_Retangulo(id, x, y, w, h, corp, corb);
                if(rt){
                    Forma f = Criar_Forma(RETANGULO, rt);
                    if(f){
                        InserirChao(chao, f);
                    }else{
                        KillRetangulo(rt);
                    }
                }
            }
            else if (strcmp(comando, "l") == 0) {
                int id; double x1, y1, x2, y2; char cor[100];
                int itens_lidos = sscanf(buffer, "%*s %d %lf %lf %lf %lf %99s", &id, &x1, &y1, &x2, &y2, cor);
                if(itens_lidos != 6){
                fprintf(stderr, "ERRO: Linha de comando 'l' ignorada: %s\n", buffer);
                continue;
                }

                Linha l = Criar_Linha(id, x1, y1, x2, y2, cor);
                if(l){
                   Forma f = Criar_Forma(LINHA, l);
                    if(f){
                        InserirChao(chao, f);
                    }else{
                        KillLinha(l);
                    }
                }
            }
            else if (strcmp(comando, "t") == 0) {
                int id, chars_lidos = 0;
                double x, y; char corb[100], corp[100], a;
                
                int itens_lidos = sscanf(buffer, "%*s %d %lf %lf %99s %99s %c %n", &id, &x, &y, corb, corp, &a, &chars_lidos);
                if(itens_lidos != 6){
                fprintf(stderr, "ERRO: Linha de comando 't' ignorada: %s\n", buffer);
                continue;   
                }

                char *conteudo_texto = buffer + chars_lidos;
                conteudo_texto[strcspn(conteudo_texto, "\r\n")] = 0;
                Estilo novo_estilo = CriarCopiaEstilo(estiloAtual);
                Texto t = Criar_Texto(id, x, y, corb, corp, a, conteudo_texto, novo_estilo);
                if(t){
                    Forma f = Criar_Forma(TEXTO, t);
                    if(f){
                        InserirChao(chao, f);
                    }else{
                        KillTexto(t);
                    }
                }                
            }
        }
    }

    KillEstilo(estiloAtual);
    fclose(arqGeo);
    return chao;
}