#include "circulo.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "formas.h"    

#define pi 3.14159265359

typedef struct Circulo{
    int id;
    double x, y, r;
    char *corb, *corp;
}StCirculo;


Circulo Criar_Circulo(int id, double x, double y, double r, char *corp, char *corb){
    
    StCirculo *c = malloc(sizeof(StCirculo));
    if(c == NULL){
        printf("Nao foi possivel alocar memoria para criar o circulo!\n");
        exit(1);
    } 

    c->id = id;
    c->r = r;
    c->x = x;
    c->y = y;

    c->corb = malloc(strlen(corb)+1);
    if(c->corb == NULL){
        printf("Nao foi possivel alocar memoria para a cor de borda!\n");
        free(c);
        exit(1);
    }
    strcpy(c->corb, corb);

    c->corp = malloc(strlen(corp)+1);
    if(c->corp == NULL){
        printf("Nao foi possivel alocar memória para a cor de preenchimento!\n");
        free(c->corb);
        free(c);
        exit(1);
    }
    strcpy(c->corp, corp);

    return ((StCirculo*)c);

}

int GetIDCirculo(Circulo c){
    return ((StCirculo*)c)->id;
}

double GetXCirculo(Circulo c){
    return ((StCirculo*)c)->x;
}

double GetYCirculo(Circulo c){
    return ((StCirculo*)c)->y;
}

double GetRCirculo(Circulo c){
    return ((StCirculo*)c)->r;
}

char *GetCorpCirculo(Circulo c){
    return ((StCirculo*)c)->corp;
}

char *GetCorbCirculo(Circulo c){
    return ((StCirculo*)c)->corb;
}

void SetIDCirculo(Circulo c, int id){
    ((StCirculo*)c)->id = id;
}

void SetXCirculo(Circulo c, double x){
    ((StCirculo*)c)->x = x;
}

void SetYCirculo(Circulo c, double y){
    ((StCirculo*)c)->y = y;
}

void SetRCirculo(Circulo c, double r){
    ((StCirculo*)c)->r = r;
}

void SetCorpCirculo(Circulo c, char *corp){
    StCirculo *circ = ((StCirculo*)c);

    if(circ == NULL || corp == NULL){
        return;
    }
    char *novacor = realloc(circ->corp, strlen(corp)+1);
    if(novacor == NULL){
        return;
    }

    circ->corp = novacor;
    strcpy(circ->corp, corp);
}

void SetCorbCirculo(Circulo c, char *corb){
    StCirculo *circ = ((StCirculo*)c);
    if(circ == NULL || corb == NULL){
        return;
    } 
    char *novacor = realloc(circ->corb, strlen(corb)+1);
    if(novacor == NULL){
        return;
    }

    circ->corb = novacor;
    strcpy(circ->corb, corb);
}

double AreaCirculo(Circulo c){
    return pi * pow(((StCirculo*)c)->r, 2);
}

void KillCirculo(Circulo c){
    StCirculo *circ = ((StCirculo*)c);
    if(circ == NULL){
        return;
    }
    
    free(circ->corb);
    free(circ->corp);
    free(circ);
}