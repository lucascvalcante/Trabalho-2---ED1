#include "linha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "formas.h"

typedef struct{
    int id;
    double x1, y1, x2, y2;
    char *cor;
}StLinha;


Linha Criar_Linha(int id, double x1, double y1, double x2, double y2, char *cor){
    StLinha *l = malloc(sizeof(StLinha));
    if(l == NULL){
        printf("Não foi possível alocar memória para criar a linha!\n");
        exit(1);
    } 
    l->id = id;
    l->x1 = x1;
    l->y1 = y1;
    l->x2 = x2;
    l->y2 = y2;

    l->cor = malloc(strlen(cor)+1);
    if(l->cor == NULL){
        printf("Não foi possível alocar memória para a cor da linha!\n");
        free(l);
        exit(1);
    }
    strcpy(l->cor, cor);

    return ((StLinha*)l);
}

int GetIDLinha(Linha l){
    return ((StLinha*)l)->id;
}

double GetX1Linha(Linha l){
    return ((StLinha*)l)->x1;
}

double GetY1Linha(Linha l){
    return ((StLinha*)l)->y1;
}

double GetX2Linha(Linha l){
    return ((StLinha*)l)->x2;
}

double GetY2Linha(Linha l){
    return ((StLinha*)l)->y2;
}

char *GetCorLinha(Linha l){
    return ((StLinha*)l)->cor;
}

void SetIDLinha(Linha l, int id){
    ((StLinha*)l)->id = id;
}

void SetX1Linha(Linha l, double x1){
    ((StLinha*)l)->x1 = x1;
}

void SetY1Linha(Linha l, double y1){
    ((StLinha*)l)->y1 = y1;
}

void SetX2Linha(Linha l, double x2){
    ((StLinha*)l)->x2 = x2;
} 

void SetY2Linha(Linha l, double y2){
    ((StLinha*)l)->y2 = y2;
}

void SetCorLinha(Linha l, char *cor){
    StLinha *li = ((StLinha*)l);
    if(li == NULL || cor == NULL){
        return;
    } 

    char *novacor = realloc(li->cor, strlen(cor)+1);
    if(novacor == NULL){
        return;
    }
    li->cor = novacor;
    strcpy(li->cor, cor);
}


double AreaLinha(Linha l){
    return 2 * sqrt((pow( ((StLinha*)l)->x2 - ((StLinha*)l)->x1, 2)) + pow( ((StLinha*)l)->y2 - ((StLinha*)l)->y1, 2)); 
}

void KillLinha(Linha l){
    StLinha *li = ((StLinha*)l);
    if(li == NULL){
        return;
    } 

    free(li->cor);
    free(li);
}