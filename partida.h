#ifndef partida_H_
#define partida_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "usuario.h"
#include "Mochila.h"

typedef struct 
{
	char id[50];
	int x;
	int y;
}jmapa;

int njugando;

typedef struct
{
	char id;
}objeto;


void lobby (usuario **u,configuracion c,int indice,jmapa **jm,mochila **m);

int njugadores_EE (usuario *u);

#endif