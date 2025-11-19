#include "colisao.h"
#include "math.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "formas.h"
#include "circulo.h"
#include "retangulo.h"
#include "texto.h"
#include "linha.h"


/*
    --- IMPLEMENTAÇÃO DE FUNÇÕES AUXILIARES
*/

static bool retangulo_retangulo_colide(Retangulo r1, Retangulo r2){
    double x1 = GetXRetangulo(r1);
    double y1 = GetYRetangulo(r1);
    double w1 = GetWRetangulo(r1);
    double h1 = GetHRetangulo(r1);

    double x2 = GetXRetangulo(r2);
    double y2 = GetYRetangulo(r2);
    double w2 = GetWRetangulo(r2);
    double h2 = GetHRetangulo(r2);

    return !(x1 + w1 < x2 || x2 + w2 < x1 || y1 + h1 < y2 || y2 + h2 < y1);
    
}

static bool circulo_circulo_colide(Circulo c1, Circulo c2){
    double x1 = GetXCirculo(c1);
    double y1 = GetYCirculo(c1);
    double r1 = GetRCirculo(c1);

    double x2 = GetXCirculo(c2);
    double y2 = GetYCirculo(c2);
    double r2 = GetRCirculo(c2);

    double dx = x1 - x2;
    double dy = y1 - y2;
    double distancia = sqrt(dx * dx + dy * dy);
    return distancia <= (r1 + r2);
}

static bool circulo_retangulo_colide(Circulo c, Retangulo r){
    double cx = GetXCirculo(c);
    double cy = GetYCirculo(c);
    double cr = GetRCirculo(c);

    double rx = GetXRetangulo(r);
    double ry = GetYRetangulo(r);
    double rh = GetHRetangulo(r);
    double rw = GetWRetangulo(r);

    double ponto_mais_proximo_x = fmax(rx, fmin(cx, rx + rw));
    double ponto_mais_proximo_y = fmax(ry, fmin(cy, ry + rh));
    double dx = cx - ponto_mais_proximo_x;
    double dy = cy - ponto_mais_proximo_y;
    return (dx * dx + dy * dy) <= (cr * cr);
}

static bool linha_linha_colide(double lx1, double ly1, double lx2, double ly2, double lx3, double ly3, double lx4, double ly4 ){
    double den = (ly4 - ly3) * (lx2 - lx1) - (lx4 - lx3) * (ly2 - ly1);
    if(den == 0){
        return false;
    }

    double ua_num = (lx4 - lx3) * (ly1 - ly3) - (ly4 - ly3) * (lx1 - lx3);
    double ub_num = (lx2 - lx1) * (ly1 - ly3) - (ly2 - ly1) * (lx1 - lx3);
    
    double ua = ua_num / den;
    double ub = ub_num / den;

    return(ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1);
}

static bool linha_retangulo_colide(double lx1, double ly1, double lx2, double ly2, Retangulo r){
    double rx = GetXRetangulo(r);
    double ry = GetYRetangulo(r);
    double rh = GetHRetangulo(r);
    double rw = GetWRetangulo(r);

    if((lx1 >= rx && lx1 <= rx + rw && ly1 >= ry &&ly1 <= ry +rh) || (lx2 >= rx && lx2 <= rx + rw && ly2 >= ry && ly2 <= ry + rh)){
        return true;
    }
    if(linha_linha_colide(lx1, ly1, lx2, ly2, rx, ry, rx + rw, ry)){
        return true;
    }if(linha_linha_colide(lx1, ly1, lx2, ly2, rx + rw, ry, rx + rw, ry + rh)){
        return true;
    }if(linha_linha_colide(lx1, ly1, lx2, ly2, rx + rw, ry + rh, rx, ry + rh)){
        return true;
    }if(linha_linha_colide(lx1, ly1, lx2, ly2, rx, ry + rh, rx, ry)){
        return true;
    }

    return false;
}

static bool linha_circulo_colide(double lx1, double ly1, double lx2, double ly2, Circulo c){
    double cx = GetXCirculo(c);
    double cy = GetYCirculo(c);
    double cr = GetRCirculo(c);

    if(pow(lx1 - cx, 2) + pow(ly1 - cy, 2) <= pow(cr, 2)){
        return true;
    }if(pow(lx2 - cx, 2) + pow(ly2 - cy, 2) <= pow(cr, 2)){
        return true;
    }

    double len_sq = pow(lx2 - lx1, 2) + pow(ly2 - ly1, 2);
    if(len_sq == 0.0){
        return false;
    }

    double t = fmax(0, fmin(1, ((cx - lx1) * (lx2 - lx1) + (cy - ly1) * (ly2 - ly1)) / len_sq));
    double closest_x = lx1 + t * (lx2 - lx1);
    double closest_y = ly1 + t * (ly2 - ly1);
    
    return pow(cx - closest_x, 2) + pow(cy - closest_y, 2) <= pow(cr, 2);
}

static void GetSegmentoForma(Forma f, double* x1, double* y1, double* x2, double* y2){
    if(GetTipoForma(f) == LINHA){
        Linha l = (Linha)GetDadosForma(f);
        *x1 = GetX1Linha(l);
        *y1 = GetY1Linha(l);
        *x2 = GetX2Linha(l);
        *y2 = GetY2Linha(l);
        return;
    }
    if(GetTipoForma(f) == TEXTO){
        Texto t = (Texto)GetDadosForma(f);
        double xt = GetXTexto(t);
        double yt = GetYTexto(t);
        int len = strlen(GetTxtoTexto(t));
        char ancora = GetATexto(t);

        if(ancora == 'i'){
            *x1 = xt; 
            *y1 = yt;
            *x2 = xt + 10.0 * len;
            *y2 = yt;
        } else if(ancora == 'm'){
            *x1 = xt - (10.0 * len) / 2.0;
            *y1 = yt;
            *x2 = xt + (10.0 * len) / 2.0;
            *y2 = yt;
        } else{ // 'f'
            *x1 = xt - 10.0 * len;
            *y1 = yt;
            *x2 = xt;
            *y2 = yt;
        }
    }
}


/*
    ---- FUNÇÃO PRINCIPAL DE SOBREPOSIÇÃO: -----
*/

bool FormaSobrepoe(Forma forma1, Forma forma2){
    Tipo_Forma f1 = GetTipoForma(forma1);
    Tipo_Forma f2 = GetTipoForma(forma2);

    void* dados1 = GetDadosForma(forma1);
    void* dados2 = GetDadosForma(forma2);

    if(f1 == RETANGULO && f2 == RETANGULO){
        return retangulo_retangulo_colide((Retangulo)dados1, (Retangulo)dados2);
    }if(f1 == CIRCULO && f2 == CIRCULO){
        return circulo_circulo_colide((Circulo)dados1, (Circulo)dados2);
    }if(f1 == RETANGULO && f2 == CIRCULO){
        return circulo_retangulo_colide((Circulo)dados2, (Retangulo)dados1);
    }if(f1 == CIRCULO && f2 == RETANGULO){
        return circulo_retangulo_colide((Circulo)dados1, (Retangulo)dados2);
    }

    if(f1 == LINHA || f1 == TEXTO || f2 == LINHA || f2 == TEXTO){
        double ax1, ay1, ax2, ay2;
        double bx1, by1, bx2, by2;        

        if(f1 == LINHA || f1 == TEXTO){
            GetSegmentoForma(forma1, &ax1, &ay1, &ax2, &ay2);
            if(f2 == CIRCULO){
                return linha_circulo_colide(ax1, ay1, ax2, ay2, (Circulo)dados2);
            }if(f2 == RETANGULO){
                return linha_retangulo_colide(ax1, ay1, ax2, ay2, (Retangulo)dados2);
            }if(f2 == LINHA || f2 == TEXTO){
                GetSegmentoForma(forma2, &bx1, &by1, &bx2, &by2);
                return linha_linha_colide(ax1, ay1, ax2, ay2, bx1, by1, bx2, by2);
            }
        }
        if(f2 == LINHA || f2 == TEXTO){
            GetSegmentoForma(forma2, &bx1, &by1, &bx2, &by2);
            if(f1 == CIRCULO){
                return linha_circulo_colide(bx1, by1, bx2, by2, (Circulo)dados1);
            }if(f1 == RETANGULO){
                return linha_retangulo_colide(bx1, by1, bx2, by2, (Retangulo)dados1);
            }
        }
    }
    return false;
}


