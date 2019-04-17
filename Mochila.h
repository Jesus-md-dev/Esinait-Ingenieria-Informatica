#ifndef _MOCHILA_H_
#define _MOCHILA_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "usuario.h"
#include "configuracion.h"

typedef struct
{
    char idusu [15];
    char idobj [6];
    int unidades;

} mochila;

int nmochilas;

void cargarficheroMochila (mochila **eMochila);
void guardarficheroMochila (mochila *eMochila);
void leerMochila (mochila *eMochila, int j, usuario *u);
int usarMochila (mochila *eMochila, int j, usuario *u);
void eliminarobjeto (mochila **eMochila, int i);
void guardar_mochila (mochila **eMochila, char *objeto, int j, usuario *u);

#endif
