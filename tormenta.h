#ifndef TORMENTA_H_
#define TORMENTA_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mapa.h"
#include "configuracion.h"

typedef struct 
{
    int x;
    int y;
    int diametro;
    int tiempo;
}tormenta;

int ntormentas;

void cargar_tormenta(tormenta **t);
void guardar_tormenta(tormenta *t);
void generar_tormentas(tormenta **t,configuracion c);
int distancia_e(Elemento *jm,char *u1,char *u2);
int distancia(int x1,int y1,int x2,int y2);
void fuera_tormenta(tormenta *t,int indice,Elemento **jm,usuario **u);

#endif