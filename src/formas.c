#include "formas.h"
#include <stdio.h>
#include <stdlib.h>
#include "circulo.h"
#include "retangulo.h"
#include "texto.h"
#include "linha.h"
#include "string.h"

typedef struct formas{
    Tipo_Forma tipo;
    void *dados;
}Stforma;


Forma Criar_Forma(Tipo_Forma tipo, void *dados){
    Stforma *f = malloc(sizeof(Stforma));
    if(f == NULL){
        printf("Erro ao alocar memória para criar forma!\n");
        exit(1);
    } 

    f->tipo = tipo;
    f->dados = dados;

    return ((Stforma*)f);
}

Tipo_Forma GetTipoForma(Forma f){
    return ((Stforma*)f)->tipo;
}

void *GetDadosForma(Forma f){
    return ((Stforma*)f)->dados;
}

double GetAreaForma(Forma f){
    if(f == NULL){
        return 0;
    }

    switch (((Stforma*)f)->tipo) {
    case CIRCULO: return AreaCirculo(((Stforma*)f)->dados); 
    case RETANGULO: return AreaRetangulo(((Stforma*)f)->dados);
    case TEXTO: return AreaTexto(((Stforma*)f)->dados);
    case LINHA: return AreaLinha(((Stforma*)f)->dados);

    }

    return 0;
}

void SetPosicaoForma(Forma f, double x, double y){
        if(f == NULL){
            return;
        }
        switch (((Stforma*)f)->tipo) {
        case CIRCULO: {
            Circulo c = ((Stforma*)f)->dados;
            SetXCirculo(c, x);
            SetYCirculo(c, y);
            break;
        }

        case RETANGULO:{
            Retangulo r = ((Stforma*)f)->dados;
            SetXRetangulo(r, x);
            SetYRetangulo(r, y);
            break;
        }

        case LINHA:{
            Linha l = ((Stforma*)f)->dados;
        
            double x1Antigo = GetX1Linha(l);
            double x2Antigo = GetX2Linha(l);
            double y1Antigo = GetY1Linha(l);
            double y2Antigo = GetY2Linha(l);

            double dx = x - x1Antigo;
            double dy = y - y1Antigo;

            SetX1Linha(l, x);
            SetY1Linha(l, y);
            SetX2Linha(l, x2Antigo + dx);
            SetY2Linha(l, y2Antigo + dy);
            break;
        }

        case TEXTO: {
            Texto t = ((Stforma*)f)->dados;

            SetXTexto(t, x);
            SetYTexto(t, y);  
            break;
        } 

        default: {
            printf("Forma inválida!\n");
            break;
        }
    
    }
}

void DestruirForma(Forma forma){
    Stforma *f = ((Stforma*)forma);
    if(f == NULL){
        return;
    } 

    switch (f->tipo) {

    case CIRCULO:
        KillCirculo(f->dados);
        break;
    case RETANGULO: 
        KillRetangulo(f->dados);
        break;
    case LINHA: 
        KillLinha(f->dados);
        break;
    case TEXTO: 
        KillTexto(f->dados);
        break;
    default:
        printf("Forma inválida!\n");
        break;
    }

    free(f);
}

double GetXForma(Forma forma){
    Stforma *f = ((Stforma*)forma);
    if(f == NULL){
        return 0.0;
    } 

    Tipo_Forma tipo = GetTipoForma(f);
    void* dados = GetDadosForma(f);

    switch (tipo){
    case CIRCULO:
        return GetXCirculo(dados);
        break;
    case RETANGULO: 
        return GetXRetangulo(dados);
        break;
    case TEXTO:
        return GetXTexto(dados);
        break;
    case LINHA:
        return GetX1Linha(dados);
        break;

    default:
        printf("Forma inválida!\n");
        return 0.0;
        break;
    }
}

double GetYForma(Forma forma){
    Stforma *f = ((Stforma*)forma);
    if(f == NULL){
        return 0.0;
    } 

    Tipo_Forma tipo = GetTipoForma(f);
    void* dados = GetDadosForma(f);

    switch (tipo){
    case CIRCULO:
        return GetYCirculo(dados);
        break;
    case RETANGULO: 
        return GetYRetangulo(dados);
        break;
    case TEXTO:
        return GetYTexto(dados);
        break;
    case LINHA:
        return GetY1Linha(dados);
        break;

    default:
        printf("Forma inválida!\n");
        return 0.0;
        break;
    }
}

int GetIDForma(Forma forma){
    Stforma *f = ((Stforma*)forma);
    if(f == NULL){
        return 0.0;
    } 
    
    Tipo_Forma tipo = GetTipoForma(f);
    void* dados = GetDadosForma(f);

    switch (tipo){
    case CIRCULO:
        return GetIDCirculo(dados);
        break;
    case RETANGULO: 
        return GetIDRetangulo(dados);
        break;
    case TEXTO: 
        return GetIDTexto(dados);
        break;
    case LINHA:
        return GetIDLinha(dados);
        break;
    default:
        printf("Forma inválida!\n");
        return 0;
        break;
    }

}

char *GetCorbForma(Forma forma){
    Stforma *f = ((Stforma*)forma);
    if(f == NULL){
        return NULL;
    } 

    Tipo_Forma tipo = GetTipoForma(f);
    void* dados = GetDadosForma(f);

    switch (tipo){
    case CIRCULO:
        return GetCorbCirculo(dados);
        break;
    case RETANGULO:
        return GetCorbRetangulo(dados);
        break;
    case LINHA: 
        return GetCorLinha(dados);
        break;
    case TEXTO: 
        return GetCorbTexto(dados);
        break;
    default:
        printf("Forma inválida!\n");
        return NULL;
        break;
    }
}

char *GetCorpForma(Forma forma){
    Stforma *f = ((Stforma*)forma);
    if(f == NULL){
        return NULL;
    } 

    Tipo_Forma tipo = GetTipoForma(f);
    void* dados = GetDadosForma(f);

    switch (tipo){
    case CIRCULO:
        return GetCorpCirculo(dados);
        break;
    case RETANGULO:
        return GetCorpRetangulo(dados);
        break;
    case LINHA: 
        return GetCorLinha(dados);
        break;
    case TEXTO: 
        return GetCorpTexto(dados);
        break;
    default:
        printf("Forma inválida!\n");
        return NULL;
        break;
    }
}

Forma ClonarForma(Forma forma){
    Stforma *f = ((Stforma*)forma);
    if(f == NULL){
        return NULL;
    } 

    static int id_base = 10000;
    int id_clone = ++id_base;
    Tipo_Forma tipo = GetTipoForma(f);
    void* dados_base = GetDadosForma(f);
    void* dados_clone = NULL;

    switch (tipo){
    case CIRCULO:
        Circulo c = (Circulo)dados_base;
        dados_clone = Criar_Circulo(id_clone, GetXCirculo(c), GetYCirculo(c), GetRCirculo(c), GetCorbCirculo(c), GetCorpCirculo(c));
        break;
    case RETANGULO: 
        Retangulo r = (Retangulo)dados_base;
        dados_clone = Criar_Retangulo(id_clone, GetXRetangulo(r), GetYRetangulo(r), GetWRetangulo(r), GetHRetangulo(r), GetCorbRetangulo(r), GetCorpRetangulo(r));
        break;
    case LINHA: 
        Linha l = (Linha)dados_base;
        dados_clone = Criar_Linha(id_clone, GetX1Linha(l), GetY1Linha(l), GetX2Linha(l), GetY2Linha(l), GetCorLinha(l));
        break;
    case TEXTO: 
        Texto t = (Texto)dados_base;
        Estilo st_base = GetEstilo(t);
        Estilo st_clone = NULL;

        if(st_base != NULL){
            st_clone = Criar_Estilo(GetfFamily(st_base), GetfWeight(st_base), GetfSize(st_base));
        }
        dados_clone = Criar_Texto(id_clone, GetXTexto(t), GetYTexto(t), GetCorbTexto(t), GetCorpTexto(t), GetATexto(t), GetTxtoTexto(t), st_clone);
        break;
    default:
        printf("Forma inválida!\n");
        return NULL;
        break;
    }
    if(dados_clone != NULL){
        return Criar_Forma(tipo, dados_clone);
    }
    return NULL;
}


char *GetCorComplementar(const char* cor_original){
    int r = 0, g = 0, b = 0;
    
    if(cor_original != NULL && cor_original[0] != '\0'){
        const char *hex_str = (cor_original[0] == '#') ? cor_original + 1 : cor_original;
        size_t len = strlen(hex_str);

        if(len == 6){
            sscanf(hex_str, "%02x%02x%02x", &r, &g, &b);
        }else if(len == 3){
            int r_s, g_s, b_s;
            sscanf(hex_str, "%1x%1x%1x", &r_s, &g_s, &b_s);
            r = r_s * 17;
            g = g_s * 17;
            b = b_s * 17;
        } else{
            fprintf(stderr, "Formado de cor inválido ('%s')!, preto será usado como padrão.\n", cor_original);
        }
    } 

    int comp_r = 255 - r;
    int comp_g = 255 - g;
    int comp_b = 255 - b;

    char* cor_complementar = malloc(8);
    if(cor_complementar == NULL){
        printf("Erro ao alocar memória para a cor complementar!\n");
        return NULL;
    }

    sprintf(cor_complementar, "#%02x%02x%02x", comp_r, comp_g, comp_b);

    return cor_complementar;
}

void SetCorbForma(Forma forma, char *corb){
    Stforma *f = ((Stforma*)forma);
    if(f == NULL || corb == NULL){
        return;
    } 
    
    Tipo_Forma tipo = GetTipoForma(f);
    void* dados = GetDadosForma(f);

    switch (tipo){
    case CIRCULO:
        SetCorbCirculo(dados, corb);
        break;
    case RETANGULO:
        SetCorbRetangulo(dados, corb);
        break;
    case LINHA:
        SetCorLinha(dados, corb);
        break;
    case TEXTO: 
        SetCorbTexto(dados, corb);
        break;
    default:
        printf("Forma inválida!\n");
        break;
    }
}

void SetCorpForma(Forma forma, char *corp){
    Stforma *f = ((Stforma*)forma);
    if(f == NULL || corp == NULL){
        return;
    } 
    
    Tipo_Forma tipo = GetTipoForma(f);
    void* dados = GetDadosForma(f);

    switch (tipo){
    case CIRCULO:
        SetCorpCirculo(dados, corp);
        break;
    case RETANGULO:
        SetCorpRetangulo(dados, corp);
        break;
    case LINHA:
        SetCorLinha(dados, corp);
        break;
    case TEXTO: 
        SetCorpTexto(dados, corp);
        break;
    default:
        printf("Forma inválida!\n");
        break;
    }
}


void TrocaCoresForma(Forma forma) {
    Stforma *f = ((Stforma*)forma);
    if (f == NULL) {
        return;
    }

	char *cor_borda = GetCorbForma(f);
	char *cor_preenchimento = GetCorpForma(f);

	if (cor_borda == NULL || cor_preenchimento == NULL) {
		return;
	}

	char *copia_preenchimento = malloc(strlen(cor_preenchimento) + 1);
    char *copia_borda = malloc(strlen(cor_borda)+1);
	if (copia_preenchimento == NULL || copia_borda == NULL) {
		fprintf(stderr, "Erro ao alocar memória na função de trocar cores!\n");
        free(copia_borda);
        free(copia_preenchimento);
		return;
	}

	strcpy(copia_preenchimento, cor_preenchimento);
    strcpy(copia_borda, cor_borda);

	SetCorpForma(f, copia_borda);
	SetCorbForma(f, copia_preenchimento);

	free(copia_preenchimento);
    free(copia_borda);
}


void InserirDadosTxt(Forma forma, FILE *txt, char *reportQry){
    Stforma *f = ((Stforma*)forma);
    if(f == NULL){
        return;
    } 

    Tipo_Forma tipo = GetTipoForma(f);
    if(f == NULL){
        return;
    } 

    void* dados = GetDadosForma(f);
    const char* report = (reportQry != NULL) ? reportQry : "";

    switch (tipo){
    case CIRCULO:
        fprintf(txt, "%s\nCírculo\nAncora em: (%.2lf, %.2lf)\nRaio: %.2lf\nPreenchimento: %s\nBorda: %s\n", 
        report, GetXCirculo(dados), GetYCirculo(dados), GetRCirculo(dados), GetCorpCirculo(dados), GetCorbCirculo(dados));
        break;
    case RETANGULO: 
        fprintf(txt, "%s\nRetângulo\nAncora em: (%.2lf, %.2lf)\nLargura: %.2lf\nAltura: %.2lf\nPreenchimento: %s\nBorda: %s\n", 
        report, GetXRetangulo(dados), GetYRetangulo(dados), GetWRetangulo(dados), GetHRetangulo(dados), GetCorpRetangulo(dados), GetCorbRetangulo(dados));
        break;
    case TEXTO: 
        Texto t = (Texto)dados;
        Estilo e = GetEstilo(t);
        fprintf(txt, "%s\nTexto\nAncora em: (%.2lf, %.2lf)\nPosição da âncora: %c\nConteúdo do texto: %s\nPreenchimento: %s\nBorda: %s\n", 
        report, GetXTexto(dados), GetYTexto(dados), GetATexto(dados), GetTxtoTexto(dados), GetCorpTexto(dados), GetCorbTexto(dados)); 
        if(e != NULL){
            fprintf(txt, "\nFamília: %s\nWeight: %s\nSize: %s\n", GetfFamily(e), GetfWeight(e), GetfSize(e));
        }else{
            fprintf(txt, "\n");
        }
        break;
    case LINHA: 
        fprintf(txt, "%s\nLinha\nAncora inicial em: (%.2lf, %.2lf)\nAncora final em: (%.2lf, %.2lf)\nCor: %s\n", 
        report, GetX1Linha(dados), GetY1Linha(dados), GetX2Linha(dados), GetY2Linha(dados), GetCorLinha(dados)); 
        break;   
    default:
        fprintf(txt, "Forma inválida!\n");
        break;
    }
}


