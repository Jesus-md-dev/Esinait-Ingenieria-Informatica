#ifndef TORMENTA_H_
#define TORMENTA_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
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

#endif