#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processador_qry.h"
#include "lista.h"
#include "formas.h"
#include "linha.h"
#include "svg.h"          
#include "visibilidade.h" 
#include "poligono.h"     
#include "colisao.h"  
#define BUFFER_SIZE 512


/// --- FUNÇÕES PRIVADAS AUXILIARES : --- ///


static Lista cemiterio_formas = NULL;


static Lista GetCemiterio() {
    if (cemiterio_formas == NULL) {
        cemiterio_formas = Criar_Lista();
    }
    return cemiterio_formas;
}


static void comando_a(char *buffer, Lista formas, Lista anteparos, FILE *txt) {
    int i, j; 
    char orientacao;
    
    sscanf(buffer, "a %d %d %c", &i, &j, &orientacao);
    if (txt) fprintf(txt, "a %d %d %c\n", i, j, orientacao);
    Lista transmutados = Criar_Lista();

    void* node = GetFirst(formas);
    while (node != NULL) {
        Forma f = (Forma)GetData(node);
        int id = GetIDForma(f);

        if (id >= i && id <= j) {
            
            if (txt) fprintf(txt, "Processando Forma Original -> ID: %d, Tipo: %d\n", id, GetTipoForma(f));

            Linha** segs = Transforma_anteparo(f, orientacao);
            
            if (segs) {
                int k = 0;
                while (segs[k] != NULL) {
                    Linha l = segs[k]; 
                    if (txt) {
                        fprintf(txt, "  -> Segmento Gerado ID: %d | (%.2f, %.2f) -> (%.2f, %.2f)\n",
                                GetIDLinha(l), 
                                GetX1Linha(l), GetY1Linha(l), 
                                GetX2Linha(l), GetY2Linha(l));
                    }

                    Forma f_seg = Criar_Forma(LINHA, l);
                    Inserir_fim(anteparos, f_seg); 
                    k++;
                }
                free(segs);
                Inserir_fim(transmutados, f);
            }
        }    
        node = GetNext(node);
    }

    node = GetFirst(transmutados);
    while(node != NULL) {
        Forma f = (Forma)GetData(node);
        RemoverElemento(formas, f); 
        Inserir_fim(GetCemiterio(), f);          
        node = GetNext(node);
    }
    Destruir_lista(transmutados, NULL);
}


static void comando_d(char *buffer, Lista formas, Lista anteparos, FILE *txt,
                      const char *path_saida, const char *nome_base, Svg svg_final,
                      int threshold, char tipo_ord) {
    
    double x, y; char sfx[64];
    sscanf(buffer, "d %lf %lf %s", &x, &y, sfx);
    if (txt) fprintf(txt, "\n[*] d %.2lf %.2lf %s\n", x, y, sfx);

    Ponto origem = init_ponto(x, y);
    Poligono poly = calc_regiao_visibilidade(origem, anteparos, tipo_ord, 10000.0, threshold);

    Lista mortos = Criar_Lista();
    void* node = GetFirst(formas);
    while (node != NULL) {
        Forma f = (Forma)GetData(node);
        if (FormaSobrepoePoligono(f, poly)) {
            if (txt) fprintf(txt, "Forma Destruida -> ID: %d\n", 
                             GetIDForma(f));
            Inserir_fim(mortos, f);
        }
        node = GetNext(node);
    }

    Lista anteparos_mortos = Criar_Lista();
    node = GetFirst(anteparos);
    while (node != NULL) {
        Forma f = (Forma)GetData(node);
        Linha l = (Linha)GetDadosForma(f);

        if (GetIDLinha(l) < 9000) {
            if (FormaSobrepoePoligono(f, poly)) {
                if (txt) fprintf(txt, "Anteparo Destruido -> ID: %d, Tipo: LINHA\n", GetIDForma(f));
                Inserir_fim(anteparos_mortos, f);
            }
        }
        node = GetNext(node);
    }

    node = GetFirst(mortos);
    while(node) {
        Forma f = (Forma)GetData(node);
        RemoverElemento(formas, f);
        DestruirForma(f);
        node = GetNext(node);
    }

    node = GetFirst(anteparos_mortos);
    while(node) {
        Forma f = (Forma)GetData(node);
        RemoverElemento(anteparos, f); 
        DestruirForma(f);              
        node = GetNext(node);
    }

    Destruir_lista(mortos, NULL);
    Destruir_lista(anteparos_mortos, NULL);

    if (strcmp(sfx, "-") != 0) {
        char path_full[512];
        sprintf(path_full, "%s/%s-%s.svg", path_saida, nome_base, sfx);
        Svg svg_bomba = CriarSvg(path_full);
        if (svg_bomba) {
            InserirPoligonoSvg(svg_bomba, poly);    
            InserirBombaSvg(svg_bomba, x, y);      
            InserirBoundingBoxSvg(svg_bomba, poly); 
            FinalizarSvg(svg_bomba);
        }
    } else if (svg_final != NULL) {
        InserirPoligonoSvg(svg_final, poly);
        InserirBombaSvg(svg_final, x, y);
    }

    free_ponto(origem);
    killPoligono(poly);
}



static void comando_p(char *buffer, Lista formas, Lista anteparos, FILE *txt, const char *path_saida, const char *nome_base,
                 Svg svg_final, int threshold, char tipo_ord) {

    double x, y; char cor[64], sfx[64];
    sscanf(buffer, "p %lf %lf %s %s", &x, &y, cor, sfx);
    fprintf(txt, "\n[*] p %.2lf %.2lf %s\n", x, y, cor);

    Ponto origem = init_ponto(x, y);
    Poligono poly = calc_regiao_visibilidade(origem, anteparos, tipo_ord, 10000.0, threshold);

    void* node = GetFirst(formas);
    while (node != NULL) {
        Forma f = (Forma)GetData(node);
        
        if (FormaSobrepoePoligono(f, poly)) {
            fprintf(txt, "Pintado ID %d com %s\n", GetIDForma(f), cor);
            SetCorbForma(f, cor);
            SetCorpForma(f, cor);
        }
        node = GetNext(node);
    }
    
    node = GetFirst(anteparos);
    while (node != NULL) {
        Forma f = (Forma)GetData(node);
    
        if (FormaSobrepoePoligono(f, poly)) {
             SetCorbForma(f, cor);
        }
        node = GetNext(node);
    }

    if (strcmp(sfx, "-") != 0) {
        char path_full[512];
        sprintf(path_full, "%s/%s-%s.svg", path_saida, nome_base, sfx);
        
        Svg svg_bomba = CriarSvg(path_full);
        if (svg_bomba) {
            InserirPoligonoSvg(svg_bomba, poly);   
            InserirBoundingBoxSvg(svg_bomba, poly); 
            InserirBombaSvg(svg_bomba, x, y);     
            FinalizarSvg(svg_bomba);
        }
    } else if (svg_final != NULL) {
        InserirPoligonoSvg(svg_final, poly);
        InserirBoundingBoxSvg(svg_final, poly);
        InserirBombaSvg(svg_final, x, y);
    }

    free_ponto(origem);
    killPoligono(poly);
}



static void comando_cln(char *buffer, Lista formas, Lista anteparos, FILE *txt, const char *path_saida, const char *nome_base,
                 Svg svg_final, int threshold, char tipo_ord) {

    double x, y, dx, dy; char sfx[64];
    static int id_clone_generator = 50000;
    sscanf(buffer, "cln %lf %lf %lf %lf %s", &x, &y, &dx, &dy, sfx);
    fprintf(txt, "\n[*] cln %.2lf %.2lf\n", x, y);

    Ponto origem = init_ponto(x, y);
    Poligono poly = calc_regiao_visibilidade(origem, anteparos, tipo_ord, 10000.0, threshold);
    
    Lista clones = Criar_Lista();

    void* node = GetFirst(formas);
    while (node != NULL) {
        Forma f = (Forma)GetData(node);
        
        if (FormaSobrepoePoligono(f, poly)) {
            Forma novo = ClonarForma(f); 
            
            double nx = GetXForma(novo) + dx;
            double ny = GetYForma(novo) + dy;
            SetPosicaoForma(novo, nx, ny);

            fprintf(txt, "Clonado ID %d -> Novo em (%.2lf, %.2lf)\n", GetIDForma(f), nx, ny);
            Inserir_fim(clones, novo);
        }
        node = GetNext(node);

        if (cemiterio_formas != NULL) {
            void* node = GetFirst(cemiterio_formas);
            while (node != NULL) {
                Forma f = (Forma)GetData(node);
                

                if (FormaSobrepoePoligono(f, poly)) {
                    Forma novo = ClonarForma(f);
                    SetIDForma(novo, ++id_clone_generator);
                    double nx = GetXForma(novo) + dx;
                    double ny = GetYForma(novo) + dy;
                    SetPosicaoForma(novo, nx, ny);
                    
                    if (txt) {
                        fprintf(txt, "RESGATADO E CLONADO (Antigo Anteparo) ID %d -> Novo ID %d em (%.2f, %.2f)\n", 
                                GetIDForma(f), GetIDForma(novo), nx, ny);
                    }
                    
                    Inserir_fim(clones, novo);
                }
                node = GetNext(node);
            }
        }
    }

    node = GetFirst(clones);
    while(node != NULL) {
        Inserir_fim(formas, GetData(node));
        node = GetNext(node);
    }
    Destruir_lista(clones, NULL);


    if (strcmp(sfx, "-") != 0) {
        char path_full[512];
        sprintf(path_full, "%s/%s-%s.svg", path_saida, nome_base, sfx);
        
        Svg svg_bomba = CriarSvg(path_full);
        if (svg_bomba) {
            InserirPoligonoSvg(svg_bomba, poly);   
            InserirBoundingBoxSvg(svg_bomba, poly); 
            InserirBombaSvg(svg_bomba, x, y);     
            FinalizarSvg(svg_bomba);
        }
    } else if (svg_final != NULL) {
        InserirPoligonoSvg(svg_final, poly);
        InserirBoundingBoxSvg(svg_final, poly);
        InserirBombaSvg(svg_final, x, y);
    }

    free_ponto(origem);
    killPoligono(poly);
}

/// --- FUNÇÃO PRINCIPAL --- ///

void processa_qry(const char* path_qry, const char* path_txt, 
             Lista formas, Lista anteparos, 
             const char* path_saida, const char* nome_base_geo, Svg svg_final,
             int threshold_i, char tipo_ord) {

    FILE *qry = fopen(path_qry, "r");
    FILE *txt = fopen(path_txt, "w");
    if (!qry || !txt) return;

    char buffer[BUFFER_SIZE];
    char cmd[16];

    while (fgets(buffer, sizeof(buffer), qry)) {
        if (buffer[0] == '\n' || buffer[0] == '#') continue;
        sscanf(buffer, "%s", cmd);

        if (strcmp(cmd, "a") == 0) {
            comando_a(buffer, formas, anteparos, txt);
        }
        else if (strcmp(cmd, "d") == 0) {
            comando_d(buffer, formas, anteparos, txt, path_saida, nome_base_geo, svg_final, threshold_i, tipo_ord);
        }
        else if (strcmp(cmd, "p") == 0) {
            comando_p(buffer, formas, anteparos, txt, path_saida, nome_base_geo, svg_final, threshold_i, tipo_ord);
        }
        else if (strcmp(cmd, "cln") == 0) {
            comando_cln(buffer, formas, anteparos, txt, path_saida, nome_base_geo, svg_final, threshold_i, tipo_ord);
        }
    }

    fclose(qry);
    fclose(txt);

    if (cemiterio_formas != NULL) {
        void* node = GetFirst(cemiterio_formas);
        while(node) {
            Forma f = (Forma)GetData(node);
            DestruirForma(f);
            node = GetNext(node);
        }
        Destruir_lista(cemiterio_formas, NULL);
        cemiterio_formas = NULL; 
    }
}
