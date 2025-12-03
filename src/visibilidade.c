#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "visibilidade.h"
#include "ordenacao.h"
#include "lista.h"
#include "linha.h"
#include "formas.h"
#include "arvore.h" 

#define M_PI 3.14159265358979323846
#define EPSILON 0.001 

typedef struct stPontoBomba {
    double x;
    double y;
} StPonto;

typedef struct {
    double angulo;
    double x_destino, y_destino; 
} EventoAngulo;

static double g_ox, g_oy; 
static double g_dx, g_dy; 


static double calcular_distancia_interseccao(double ox, double oy, double dx, double dy, Linha l, double *ix, double *iy) {
    double x1 = GetX1Linha(l), y1 = GetY1Linha(l);
    double x2 = GetX2Linha(l), y2 = GetY2Linha(l);

    double r_dx = dx, r_dy = dy;
    double s_dx = x2 - x1, s_dy = y2 - y1;

    double denom = r_dx * s_dy - r_dy * s_dx;
    if (fabs(denom) < 0.000001) return DBL_MAX;

    double r_mag = (x1 - ox) * s_dy - (y1 - oy) * s_dx;
    double t = r_mag / denom; 
    
    double u;
    if (fabs(s_dx) > fabs(s_dy))
        u = (ox + r_dx * t - x1) / s_dx;
    else
        u = (oy + r_dy * t - y1) / s_dy;

    if (t > 0.001 && u >= -EPSILON && u <= (1.0 + EPSILON)) {
        if (ix) *ix = ox + r_dx * t;
        if (iy) *iy = oy + r_dy * t;
        return t;
    }

    return DBL_MAX;
}

static int comparar_segmentos_ativos(void* a, void* b) {
    Linha l1 = (Linha)GetDadosForma((Forma)a);
    Linha l2 = (Linha)GetDadosForma((Forma)b);

    double dist1 = calcular_distancia_interseccao(g_ox, g_oy, g_dx, g_dy, l1, NULL, NULL);
    double dist2 = calcular_distancia_interseccao(g_ox, g_oy, g_dx, g_dy, l2, NULL, NULL);

    if (dist1 < dist2 - EPSILON) return -1;
    if (dist1 > dist2 + EPSILON) return 1;

    int id1 = GetIDLinha(l1);
    int id2 = GetIDLinha(l2);
    if (id1 < id2) return -1;
    if (id1 > id2) return 1;

    return 0;
}

static int comparar_eventos(const void* a, const void* b) {
    EventoAngulo* e1 = *((EventoAngulo**)a);
    EventoAngulo* e2 = *((EventoAngulo**)b);
    if (e1->angulo < e2->angulo) return -1;
    if (e1->angulo > e2->angulo) return 1;
    return 0;
}

// --- Funções Públicas ---

Ponto init_ponto(double x, double y) {
    StPonto* p = malloc(sizeof(StPonto));
    if (p) { p->x = x; p->y = y; }
    return (Ponto)p; 
}
double get_ponto_x(Ponto p) { return ((StPonto*)p)->x; }
double get_ponto_y(Ponto p) { return ((StPonto*)p)->y; }
void free_ponto(Ponto p) { if (p) free(p); }



Poligono calc_regiao_visibilidade(Ponto origem, Lista anteparos, char tipo_ord, double raio_max, int threshold_i) {
    if (!origem || !anteparos) return NULL;

    StPonto* pt_origem = (StPonto*)origem;
    double ox = pt_origem->x;
    double oy = pt_origem->y;

    Poligono poly = criaPoligono();
    int qtd_segmentos = Tamanho_lista(anteparos);
    if (qtd_segmentos == 0) return poly;

    int max_eventos = qtd_segmentos * 2 * 3;
    EventoAngulo** eventos = malloc(sizeof(EventoAngulo*) * max_eventos);
    int num_eventos = 0;

    void* node = GetFirst(anteparos);
    while (node != NULL) {
        Forma f = (Forma)GetData(node);
        if (GetTipoForma(f) == LINHA) {
            Linha l = (Linha)GetDadosForma(f);
            double x1 = GetX1Linha(l), y1 = GetY1Linha(l);
            double x2 = GetX2Linha(l), y2 = GetY2Linha(l);
            double coords[2][2] = {{x1, y1}, {x2, y2}};
            for (int k = 0; k < 2; k++) {
                double px = coords[k][0];
                double py = coords[k][1];
                double angulo_base = atan2(py - oy, px - ox);
                
                double offsets[] = {-EPSILON, 0, EPSILON};
                for (int j = 0; j < 3; j++) {
                    EventoAngulo* evt = malloc(sizeof(EventoAngulo));
                    evt->angulo = angulo_base + offsets[j];
                    evt->x_destino = cos(evt->angulo);
                    evt->y_destino = sin(evt->angulo);
                    eventos[num_eventos++] = evt;
                }
            }
        }
        node = GetNext(node);
    }

    if (tipo_ord == 'm') {
        mergeSort((void**)eventos, num_eventos, comparar_eventos, threshold_i);
    } else {
        qsort(eventos, num_eventos, sizeof(EventoAngulo*), comparar_eventos);
    }

    g_ox = ox; g_oy = oy;

    Arvore arvore_ativos = Criar_arv(comparar_segmentos_ativos);
    
    node = GetFirst(anteparos);
    while (node != NULL) {
        Forma f = (Forma)GetData(node);
        InsertArv(arvore_ativos, f);
        node = GetNext(node);
    }

    for (int i = 0; i < num_eventos; i++) {
        double dx = eventos[i]->x_destino;
        double dy = eventos[i]->y_destino;
        g_dx = dx; g_dy = dy;

        double best_x = ox + dx * raio_max;
        double best_y = oy + dy * raio_max;

        Forma f_prox = (Forma)GetMinArvore(arvore_ativos);

        if (f_prox != NULL) {
            Linha l_prox = (Linha)GetDadosForma(f_prox);
            double ix, iy;
            if (calcular_distancia_interseccao(ox, oy, dx, dy, l_prox, &ix, &iy) < DBL_MAX) {
                best_x = ix;
                best_y = iy;
            }
        }

        insertVertice(poly, best_x, best_y);
    }

    killArv(arvore_ativos, NULL);

    for (int i = 0; i < num_eventos; i++) free(eventos[i]);
    free(eventos);

    return poly;
}