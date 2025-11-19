#include "texto.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Estilo{
    char *fFamily, *fWeight, *fSize;
}StEstilo;

typedef struct Texto{
    int id;
    double x, y;
    char *corb, *corp;
    char a;
    char *txto;
    Estilo st;
}StTexto;

Texto Criar_Texto(int id, double x, double y, char *corb, char *corp, char a, char *txto, Estilo st){
    StTexto *t = malloc(sizeof(StTexto));
    if(t == NULL){
        printf("Não foi possível alocar memória para a criação do texto!\n");
        exit(1);
    }

    t->id = id;
    t->x = x;
    t->y = y;
    t->a = a;
    t->st = st;

    t->corb = malloc(strlen(corb)+1);
    if(t->corb == NULL){
        printf("Não foi possível alocar memória para a cor de borda do texto!\n");
        free(t);
        exit(1);
    }
    strcpy(t->corb, corb);

    t->corp = malloc(strlen(corp)+1);
    if(t->corp == NULL){
        printf("Não foi possível alocar memória para a cor de preenchimento do texto!\n");
        free(t->corb);
        free(t);
        exit(1);
    }
    strcpy(t->corp, corp);

    t->txto = malloc(strlen(txto)+1);
    if(t->txto == NULL){
        printf("Não foi possível alocar memória para o texto!\n");
        free(t->corb);
        free(t->corp);
        free(t);
        exit(1);
    }
    strcpy(t->txto, txto);

    return ((StTexto*)t);
}

Estilo Criar_Estilo(char *fFamily, char *fWeight, char *fSize){
    StEstilo *st = malloc(sizeof(StEstilo));
    if(st == NULL){
        printf("Não foi possível alocar memória para a criação do esilo de texto!\n");
        exit(1);
    }
    
    st->fFamily = malloc(strlen(fFamily)+1);
    if(st->fFamily == NULL){
        printf("Não foi possível alocar memória para a família do texto!\n");
        free(st);
        exit(1);
    }
    strcpy(st->fFamily, fFamily);

    st->fWeight = malloc(strlen(fWeight)+1);
    if(st->fWeight == NULL){
        printf("Não foi possível alocar memória para o weight do texto!\n");
        free(st->fFamily);
        free(st);
        exit(1);
    }
    strcpy(st->fWeight, fWeight);

    st->fSize = malloc(strlen(fSize)+1);
    if(st->fSize == NULL){
        printf("Não foi possível alocar memória para o tamanho do texto!\n");
        free(st->fFamily);
        free(st->fWeight);
        free(st);
        exit(1);
    }
    strcpy(st->fSize, fSize);

    return ((StEstilo*)st);

}

char *GetfFamily(Estilo st){
    return ((StEstilo*)st)->fFamily;
}

char *GetfSize(Estilo st){
    return ((StEstilo*)st)->fSize;
}

char *GetfWeight(Estilo st){
    return ((StEstilo*)st)->fWeight;
}

void SetfFamily(Estilo st, char *fFamily){
    StEstilo *e = ((StEstilo*)st);
    if(e == NULL){
        return;
    }
    char *novoestilo = realloc(e->fFamily, strlen(fFamily)+1);
    if(novoestilo == NULL){
        return;
    }
    e->fFamily = novoestilo;
    strcpy(e->fFamily, fFamily);
}

void SetfSize(Estilo st, char *fSize){
    StEstilo *e = ((StEstilo*)st);
    if(e == NULL){
        return;
    }
    char *novoestilo = realloc(e->fSize, strlen(fSize)+1);
    if(novoestilo == NULL){
        return;
    }
    e->fSize = novoestilo;
    strcpy(e->fSize, fSize);
}

void SetfWeight(Estilo st, char *fWeight){
    StEstilo *e = ((StEstilo*)st);
    if(e == NULL){
        return;
    }
    char *novoestilo = realloc(e->fWeight, strlen(fWeight)+1);
    if(novoestilo == NULL){
        return;
    }
    e->fWeight = novoestilo;
    strcpy(e->fWeight, fWeight);
}

int GetIDTexto(Texto t){
    return ((StTexto*)t)->id;
}

double GetXTexto(Texto t){
    return ((StTexto*)t)->x;
}

double GetYTexto(Texto t){
    return ((StTexto*)t)->y;
}

char *GetCorbTexto(Texto t){
    return ((StTexto*)t)->corb;
}

char *GetCorpTexto(Texto t){
    return ((StTexto*)t)->corp;
}

char GetATexto(Texto t){
    return ((StTexto*)t)->a;
}

char *GetTxtoTexto(Texto t){
    return ((StTexto*)t)->txto;
}

double AreaTexto(Texto t){
    return 20 * strlen(((StTexto*)t)->txto);
}

void SetIDTexto(Texto t, int id){
    ((StTexto*)t)->id = id;
}

void SetXTexto(Texto t, double x){
    ((StTexto*)t)->x = x;
}

void SetYTexto(Texto t, double y){
    ((StTexto*)t)->y = y;
}

void SetCorbTexto(Texto t, char *corb){
    StTexto *te = ((StTexto*)t);
    if(te == NULL){
        return;
    }
    char *novacor = realloc(te->corb, strlen(corb)+1);
    if(novacor == NULL){
        return;
    }
    te->corb = novacor;
    strcpy(te->corb, corb);
}

void SetCorpTexto(Texto t, char *corp){
    StTexto *te = ((StTexto*)t);
    if(te == NULL){
        return;
    }
    char *novacor = realloc(te->corp, strlen(corp)+1);
    if(novacor == NULL){
        return;
    }
    te->corp = novacor;
    strcpy(te->corp, corp);
}

void SetATexto(Texto t, char a){
    ((StTexto*)t)->a = a;
}

void SetTxtoTexto(Texto t, char *txto){
    StTexto *te = ((StTexto*)t);
    if(te == NULL){
        return;
    }
    char *novotxto = realloc(te->txto, strlen(txto)+1);
    if(novotxto == NULL){
        return;
    }
    te->txto = novotxto;
    strcpy(te->txto, txto);
}

Estilo GetEstilo(Texto t){
    return ((StTexto*)t)->st;
}

void KillTexto(Texto t){
    StTexto *te = ((StTexto*)t);
    if(te == NULL){
        return;
    } 

    if(te->txto != NULL) free(te->txto);
    if(te->corb != NULL) free(te->corb);
    if(te->corp != NULL) free(te->corp);
    if(te->st != NULL) KillEstilo(te->st);

    free(te);
}


void KillEstilo(Estilo st){
    StEstilo *e = ((StEstilo*)st);
    if(e == NULL){
        return;
    }
    free(e->fFamily);
    free(e->fSize);
    free(e->fWeight);
    free(e);
}

Estilo CriarCopiaEstilo(Estilo st){
    StEstilo *e = ((StEstilo*)st);
    if(e == NULL){
        return NULL;
    }

    return Criar_Estilo(e->fFamily, e->fWeight, e->fSize);
}

