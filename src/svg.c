#include <stdio.h>
#include <stdlib.h>
#include "svg.h"
#include "formas.h"     
#include "circulo.h"    
#include "retangulo.h"  
#include "texto.h"      
#include "linha.h"      
#include "string.h"     
#include <math.h>
#include "visibilidade.h"

typedef struct Svg{
    FILE* arquivo;
}Stsvg;



Svg CriarSvg(const char* nomearquivo){
    Stsvg *s = malloc(sizeof(Stsvg));
    if(s == NULL){
        printf("Não foi possível alocar memória para a criação do svg!\n");
        exit(1);
    }

    s->arquivo = fopen(nomearquivo, "w");
    if(s->arquivo == NULL){
        printf("Não foi possível abrir o arquivo para escrita!\n");
        free(s);
        exit(1);
    }

    fprintf(s->arquivo, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
    fprintf(s->arquivo, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1000\" height=\"1000\">\n");

    return s;
} 

void InserirCirculoSvg(Svg svg, Circulo c){
    Stsvg *s = ((Stsvg*)svg);

    if(s == NULL || c == NULL || s->arquivo == NULL){
        return;
    }

    int id = GetIDCirculo(c);
    double x = GetXCirculo(c);
    double y = GetYCirculo(c);
    double r = GetRCirculo(c);
    char* Corb = GetCorbCirculo(c);
    char* Corp = GetCorpCirculo(c);

    fprintf(s->arquivo, "\t<circle id=\"%d\" cx=\"%.2lf\" cy=\"%.2lf\" r=\"%.2lf\" stroke=\"%s\" fill=\"%s\" opacity=\"%lf\" stroke-width=\"%lf\" />\n", id, x, y, r, Corb, Corp, 0.5, 1.5);
}

void InserirRetanguloSvg(Svg svg, Retangulo r){
    Stsvg *s = ((Stsvg*)svg);

    if(s == NULL || r == NULL || s->arquivo == NULL){
    return;
    }

    int id = GetIDRetangulo(r);
    double x = GetXRetangulo(r);
    double y = GetYRetangulo(r);
    double w = GetWRetangulo(r);
    double h = GetHRetangulo(r);
    char *Corb = GetCorbRetangulo(r);
    char *Corp = GetCorpRetangulo(r);

    fprintf(s->arquivo, "\t<rect id=\"%d\" x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" stroke=\"%s\" fill=\"%s\" opacity=\"%lf\" stroke-width=\"%lf\" />\n", id, x, y, w, h, Corb, Corp, 0.5, 1.5);
     
} 

void InserirTextoSvg(Svg svg, Texto t){
    Stsvg *s = ((Stsvg*)svg);

    if(s == NULL || t == NULL || s->arquivo == NULL){
    return;
    }

    int id = GetIDTexto(t);
    double x = GetXTexto(t);
    double y = GetYTexto(t);
    char* Corp = GetCorpTexto(t);
    char *Corb = GetCorbTexto(t);
    char Ancorachar = GetATexto(t);
    char* Conteudo = GetTxtoTexto(t);

    char* Ancorasvg;
    switch (Ancorachar){
    case 'i':
        Ancorasvg = "start";
        break;
    case 'm': 
        Ancorasvg = "middle";
        break;
    case 'f':
        Ancorasvg = "end";
        break;
    default:
        Ancorasvg = "start";
        break;
    }

    Estilo st = GetEstilo(t);
    if(st != NULL){
        char *fFamily = GetfFamily(st);
        char *fWeight = GetfWeight(st);
        char *fSize = GetfSize(st);

    fprintf(s->arquivo, "\t<text id=\"%d\" x=\"%.2lf\" y=\"%.2lf\" fill=\"%s\" stroke=\"%s\" stroke-width=\"1px\" text-anchor=\"%s\" font-family=\"%s\" font-weight=\"%s\" font-size=\"%s\">%s</text>\n",
               id, x, y, Corp, Corb, Ancorasvg, fFamily, fWeight, fSize, Conteudo);

    }else{
        fprintf(s->arquivo, "\t<text x=\"%.2lf\" y=\"%.2lf\" fill=\"%s\" stroke=\"%s\" stroke-width=\"1px\" text-anchor=\"%s\">%s</text>\n",
                x, y, Corp, Corb, Ancorasvg, Conteudo);
    }
}

void InserirLinhaSvg(Svg svg, Linha l){
    Stsvg *s = ((Stsvg*)svg);

    if(s == NULL || l == NULL || s->arquivo == NULL){
        return;
    } 

    int id = GetIDLinha(l);
    double x1 = GetX1Linha(l);
    double y1 = GetY1Linha(l);
    double x2 = GetX2Linha(l);
    double y2 = GetY2Linha(l);
    char *Cor = GetCorLinha(l);

    fprintf(s->arquivo, "\t<line id=\"%d\" x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" stroke=\"%s\" stroke-width=\"%lf\" />\n", id, x1, y1, x2, y2, Cor, 1.5);
}

void FinalizarSvg(Svg svg){
    Stsvg *s = ((Stsvg*)svg);

    if(s == NULL || s->arquivo == NULL){
        return;
    }

    fprintf(s->arquivo, "</svg>\n");
    fclose(s->arquivo);
    free(s);
}


void DesenharFormaSvg(void* item, void* aux){
    Forma f = (Forma)item;
    Svg svg_handle = (Svg)aux;
    if(f == NULL || svg_handle == NULL){
        return;
    } 

    Tipo_Forma tipo = GetTipoForma(f);
    void* dados = GetDadosForma(f);

    switch (tipo)
    {
    case CIRCULO:
        InserirCirculoSvg(svg_handle, (Circulo)dados);
        break;
    case RETANGULO:
        InserirRetanguloSvg(svg_handle, (Retangulo)dados);
        break;
    case LINHA: 
        InserirLinhaSvg(svg_handle, (Linha)dados);
        break;
    case TEXTO: 
        InserirTextoSvg(svg_handle, (Texto)dados);
        break;
    default:
        printf("Forma inválida!\n");
        return;
        break;
    }
}

void GerarSvg(const char* path_svg, Lista listaSvg){
    if(path_svg == NULL || listaSvg == NULL){
        printf("Erro: Argumentos nulos fornecidos para a função de gerar svg!\n");
        return;
    } 


    Svg svg_handle = CriarSvg(path_svg);
    if(svg_handle == NULL){
        printf("Erro ao criar svg!\n");
        return;
    }

    Percorrer_lista(listaSvg, DesenharFormaSvg, svg_handle);

    FinalizarSvg(svg_handle);
}


void InserirBombaSvg(Svg svg, double x, double y){
    Stsvg *s = (Stsvg*)svg;
    if (s == NULL || s->arquivo == NULL) return;

	fprintf(s->arquivo, "<circle cx=\"%lf\" cy=\"%lf\" r=\"1\" stroke-opacity=\"0.5\" fill=\"none\""
			  " stroke=\" #FF0000\" stroke-width=\"2\" stroke-dasharray=\"1, 1\" />\n", x, y);

	fprintf(s->arquivo, "<circle cx=\"%lf\" cy=\"%lf\" r=\"3\" stroke-opacity=\"0.5\" fill=\"none\""
			  " stroke=\" #FF0000\" stroke-width=\"2\" stroke-dasharray=\"1, 1\" />\n", x, y);

	fprintf(s->arquivo, "<circle cx=\"%lf\" cy=\"%lf\" r=\"2\" stroke-opacity=\"0.5\" fill=\"none\""
			  " stroke=\"#FF00FF\" stroke-width=\"2\" stroke-dasharray=\"1, 1\" />\n", x, y);
}


void InserirPoligonoSvg(Svg svg, Poligono poly){
    Stsvg *s = (Stsvg*)svg;
    if (s == NULL || s->arquivo == NULL || poly == NULL) return;

    Lista pontos = getVertices(poly);
    if (pontos == NULL || Tamanho_lista(pontos) < 3) return;

    fprintf(s->arquivo, "\t<polygon points=\"");
    
    void* node = GetFirst(pontos);
    while (node != NULL) {
        Ponto p = (Ponto)GetData(node);
        double px = get_ponto_x(p);
        double py = get_ponto_y(p);
        
        fprintf(s->arquivo, "%.2lf,%.2lf ", px, py);
        
        node = GetNext(node);
    }

    fprintf(s->arquivo, "\" fill=\"yellow\" opacity=\"0.5\" stroke=\"none\" />\n");
}

void InserirBoundingBoxSvg(Svg svg, Poligono poly){
    Stsvg *s = (Stsvg*)svg;
    if (s == NULL || s->arquivo == NULL || poly == NULL) {
        return;
    }

    double x, y, w, h;
    getBoundingBox(poly, &x, &y, &w, &h);

    if (w <= 0.001 || h <= 0.001) return;

    fprintf(s->arquivo, "\t<rect x=\"%.2lf\" y=\"%.2lf\" width=\"%.2lf\" height=\"%.2lf\" "
                        "fill=\"none\" stroke=\"blue\" stroke-width=\"1\" "
                        "stroke-dasharray=\"5,5\" />\n", 
                        x, y, w, h);
}
