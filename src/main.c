#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "processador_geo.h" 
#include "processador_qry.h"     
#include "svg.h"     
#include "formas.h" 

#define PATH_SIZE 1024

// --- FUNÇÕES AUXILIARES  ---

void monta_caminho(char* path_completo, const char* base_dir, const char* nome_arquivo) {
    if (base_dir != NULL && strlen(base_dir) > 0) {
        // Verifica se o base_dir já termina com '/'
        if (base_dir[strlen(base_dir) - 1] == '/') {
            sprintf(path_completo, "%s%s", base_dir, nome_arquivo);
        } else {
            sprintf(path_completo, "%s/%s", base_dir, nome_arquivo);
        }
    } else {
        strcpy(path_completo, nome_arquivo);
    }
}

void extrair_nome_base(const char *caminho, char *nome_base) {
    const char *ultimo_slash = strrchr(caminho, '/');
#ifdef _WIN32
    const char *ultimo_backslash = strrchr(caminho, '\\');
    if (ultimo_backslash > ultimo_slash) ultimo_slash = ultimo_backslash;
#endif
    
    const char *inicio = ultimo_slash ? ultimo_slash + 1 : caminho;
    strcpy(nome_base, inicio);
    char* ponto_ext = strrchr(nome_base, '.');
    if (ponto_ext) {
        *ponto_ext = '\0';
    }
}

void destruir_forma_void(void* f) {
    DestruirForma((Forma)f);
}

extern void DesenharFormaSvg(void* item, void* aux);


int main(int argc, char *argv[]) {
    char *path_entrada = NULL;
    char *path_saida = NULL;
    char *nome_geo = NULL;
    char *nome_qry = NULL;
    
    int threshold_i = 10; 
    char tipo_ord = 'q';  

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) path_entrada = argv[++i];
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) nome_geo = argv[++i];
        else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc) nome_qry = argv[++i];
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) path_saida = argv[++i];
        else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) threshold_i = atoi(argv[++i]); 
        else if (strcmp(argv[i], "-in") == 0 && i + 1 < argc) threshold_i = atoi(argv[++i]);
        else if (strcmp(argv[i], "-to") == 0 && i + 1 < argc) tipo_ord = argv[++i][0];
    }

    if (nome_geo == NULL || path_saida == NULL) {
        printf("ERRO: Parâmetros obrigatórios faltando.\n");
        printf("Uso: %s -e <dir_in> -f <arquivo.geo> -q <arquivo.qry> -o <dir_out>\n", argv[0]);
        return 1;
    }

    Lista anteparos = Criar_Lista();
    char path_geo_completo[PATH_SIZE];
    monta_caminho(path_geo_completo, path_entrada, nome_geo);

    printf("Lendo GEO: %s\n", path_geo_completo);
    Lista formas = ProcessaGeo(path_geo_completo); 

    if(formas == NULL){
        printf("ERRO FATAL: Falha ao processar o arquivo GEO ou lista vazia.\n");
        return 1;        
    }

    char base_geo[256];
    extrair_nome_base(nome_geo, base_geo);

    char nome_final[512];
    
    if (nome_qry != NULL) {
        char base_qry[256];
        extrair_nome_base(nome_qry, base_qry);
        sprintf(nome_final, "%s-%s", base_geo, base_qry);
    } else {
        strcpy(nome_final, base_geo);
    }

    char path_svg_final[PATH_SIZE];
    char path_txt_final[PATH_SIZE];
    
    sprintf(path_svg_final, "%s/%s.svg", path_saida, nome_final);
    sprintf(path_txt_final, "%s/%s.txt", path_saida, nome_final);

    printf("Criando SVG Final: %s\n", path_svg_final);
    Svg svg_handle = CriarSvg(path_svg_final);
    Percorrer_lista(formas, DesenharFormaSvg, svg_handle);

    if (nome_qry != NULL) {
        char path_qry_completo[PATH_SIZE];
        monta_caminho(path_qry_completo, path_entrada, nome_qry);

        printf("Processando QRY: %s\n", path_qry_completo);
        printf(" -> Log: %s\n", path_txt_final);
        
        processa_qry(path_qry_completo, path_txt_final, 
                formas, anteparos, 
                path_saida, nome_final, svg_handle, 
                threshold_i, tipo_ord);
        
         Percorrer_lista(anteparos, DesenharFormaSvg, svg_handle);
    }

    FinalizarSvg(svg_handle);

    printf("Limpando memória...\n");
    Destruir_lista(formas, destruir_forma_void);
    Destruir_lista(anteparos, destruir_forma_void);

    printf("Concluído.\n");
    return 0;
}