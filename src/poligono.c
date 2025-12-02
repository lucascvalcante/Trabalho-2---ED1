#include <stdio.h>
#include <stdlib.h>
#include <float.h> 
#include <math.h>
#include "poligono.h"
#include "lista.h"
#include "linha.h" 
#include "formas.h"


typedef struct stPontoInterno {
    double x, y;
} StPonto;

typedef struct stPoligono {
    Lista vertices; 
} StPoligono;

/// --- Função privada auxiliar: --- ///

static StPonto* alocar_ponto(double x, double y) {
    StPonto* p = malloc(sizeof(StPonto));
    if (p) {
        p->x = x;
        p->y = y;
    }
    return p;
}

/// --- Funções principais:  --- ///

Poligono criaPoligono() {
    StPoligono* poly = malloc(sizeof(StPoligono));
    if (poly) {
        poly->vertices = Criar_Lista();
    }
    return (Poligono)poly;
}

void insertVertice(Poligono p, double x, double y) {
    StPoligono* poly = (StPoligono*)p;
    if (poly) {
        StPonto* pt = alocar_ponto(x, y);
        Inserir_fim(poly->vertices, pt);
    }
}

void insertSegmento(Poligono p, Linha seg) {
    StPoligono* poly = (StPoligono*)p;
    if (!poly || !seg) return;

    double x1 = GetX1Linha(seg);
    double y1 = GetY1Linha(seg);
    double x2 = GetX2Linha(seg);
    double y2 = GetY2Linha(seg);
    insertVertice(p, x1, y1);
    insertVertice(p, x2, y2);
}

void getBoundingBox(Poligono p, double *x, double *y, double *w, double *h) {
    StPoligono* poly = (StPoligono*)p;
    if (!poly || Lista_vazia(poly->vertices)) {
        *x = 0; *y = 0; *w = 0; *h = 0;
        return;
    }

    double minX = DBL_MAX, minY = DBL_MAX;
    double maxX = -DBL_MAX, maxY = -DBL_MAX;

    void* node = GetFirst(poly->vertices);
    while (node != NULL) {
        StPonto* pt = (StPonto*)GetData(node);
        
        if (pt->x < minX) minX = pt->x;
        if (pt->x > maxX) maxX = pt->x;
        if (pt->y < minY) minY = pt->y;
        if (pt->y > maxY) maxY = pt->y;

        node = GetNext(node);
    }

    *x = minX;
    *y = minY;
    *w = maxX - minX;
    *h = maxY - minY;
}

bool isInside(Poligono p, double x, double y) {
    StPoligono* poly = (StPoligono*)p;
    if (!poly) return false;
    
    int n = Tamanho_lista(poly->vertices);
    if (n < 3) return false; 

    StPonto** pts = malloc(sizeof(StPonto*) * n);
    void* node = GetFirst(poly->vertices);
    int k = 0;
    while(node) {
        pts[k++] = (StPonto*)GetData(node);
        node = GetNext(node);
    }

    bool inside = false;
    int i, j;
    for (i = 0, j = n - 1; i < n; j = i++) {
        double xi = pts[i]->x, yi = pts[i]->y;
        double xj = pts[j]->x, yj = pts[j]->y;

        if (((yi > y) != (yj > y)) &&
            (x < (xj - xi) * (y - yi) / (yj - yi) + xi)) {
            inside = !inside; 
        }
    }

    free(pts);
    return inside;
}

Lista getVertices(Poligono p) {
    StPoligono* poly = (StPoligono*)p;
    return poly ? poly->vertices : NULL;
}

Lista getSegmentos(Poligono p) {
    StPoligono* poly = (StPoligono*)p;
    if (!poly || Lista_vazia(poly->vertices)) return NULL;

    Lista listaSegs = Criar_Lista();
    if (!listaSegs) return NULL;

    void* node = GetFirst(poly->vertices);
    StPonto* primeiro = (StPonto*)GetData(node);
    StPonto* anterior = primeiro;
    
    node = GetNext(node);
    
    int id_temp = 0; 

    while (node != NULL) {
        StPonto* atual = (StPonto*)GetData(node);
        
        Linha l = Criar_Linha(id_temp++, anterior->x, anterior->y, atual->x, atual->y, "red");
        
        Forma f = Criar_Forma(LINHA, l);
        Inserir_fim(listaSegs, f);

        anterior = atual;
        node = GetNext(node);
    }

    Linha l_final = Criar_Linha(id_temp++, anterior->x, anterior->y, primeiro->x, primeiro->y, "red");
    Forma f_final = Criar_Forma(LINHA, l_final);
    Inserir_fim(listaSegs, f_final);

    return listaSegs;
}

void killPoligono(Poligono p) {
    StPoligono* poly = (StPoligono*)p;
    if (poly) {
        Destruir_lista(poly->vertices, free); 
        free(poly);
    }
}