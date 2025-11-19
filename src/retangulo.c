#include "retangulo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Retangulo{
    int id;
    double x, y, w, h;
    char *corp, *corb;
}StRetangulo;

Retangulo Criar_Retangulo(int id, double x, double y, double w, double h, char *corp, char *corb){
    StRetangulo *r = malloc(sizeof(StRetangulo));
    if(r == NULL){
        printf("Não foi possível alocar memória para a criação do retângulo!\n");
        exit(1);
    }

    r->id = id;
    r->x = x;
    r->y = y;
    r->w = w;
    r->h = h;

    r->corb = malloc(strlen(corb)+1);
    if(r->corb == NULL){
        printf("Não foi possível alocar memória para a cor de borda!\n");
        free(r);
        exit(1);
    }
    strcpy(r->corb, corb);

    r->corp = malloc(strlen(corp)+1);
    if(r->corp == NULL){
        printf("Não foi possível alocar memória para a cor de preenchimento!\n");
        free(r->corb);
        free(r);
        exit(1);
    }
    strcpy(r->corp, corp);

    return ((StRetangulo*)r);
}

int GetIDRetangulo(Retangulo r){
    return ((StRetangulo*)r)->id;
}

double GetXRetangulo(Retangulo r){
    return ((StRetangulo*)r)->x;
}

double GetYRetangulo(Retangulo r){
    return ((StRetangulo*)r)->y;
}

double GetWRetangulo(Retangulo r){
    return ((StRetangulo*)r)->w;
}

double GetHRetangulo(Retangulo r){
    return ((StRetangulo*)r)->h;
}

char *GetCorpRetangulo(Retangulo r){
    return ((StRetangulo*)r)->corp;
}

char *GetCorbRetangulo(Retangulo r){
    return ((StRetangulo*)r)->corb;
}

void SetIDRetangulo(Retangulo r, int id){
    ((StRetangulo*)r)->id = id; 
}

void SetXRetangulo(Retangulo r, double x){
    ((StRetangulo*)r)->x = x;
}

void SetYRetangulo(Retangulo r, double y){
    ((StRetangulo*)r)->y = y;
}

void SetWRetangulo(Retangulo r, double w){
    ((StRetangulo*)r)->w = w;
}

void SetHRetangulo(Retangulo r, double h){
    ((StRetangulo*)r)->h = h;
}

void SetCorpRetangulo(Retangulo r, char *corp){
    StRetangulo *re = ((StRetangulo*)r);
    if(re == NULL || corp == NULL){
        return;
    }

    char *novacor = realloc(re->corp, strlen(corp)+1);
    if(novacor == NULL){
        return;
    }
    re->corp = novacor;
    strcpy(re->corp, corp);
}

void SetCorbRetangulo(Retangulo r, char *corb){
    StRetangulo *re = ((StRetangulo*)r);
    if(re == NULL || corb == NULL){
        return;
    }

    char *novacor = realloc(re->corb, strlen(corb)+1);
    if(novacor == NULL){
        return;
    }
    re->corb = novacor;
    strcpy(re->corb, corb);
}

double AreaRetangulo(Retangulo r){
    return ((StRetangulo*)r)->w * ((StRetangulo*)r)->h;
}

void KillRetangulo(Retangulo r){
    StRetangulo *re = ((StRetangulo*)r);
    if(re == NULL){
        return;
    }
    
    free(re->corb);
    free(re->corp);
    free(re);
}