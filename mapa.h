#ifndef _MAPA_H_
#define _MAPA_H_

//LIBRERIAS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "usuario.h"
#include "tienda.h"
#include "configuracion.h"
//#include "tormenta.h"

//VARIABLES
int nelementos;

//ESTRUCTURAS
typedef struct{
	char tipo[8];
	char nombre[16];
	int posx;
	int posy;
}Elemento;

//FUNCIONES

void generar_mapa (Elemento **vector, usuario **u,objetos *o,configuracion c);//Guardar en estructura
void guardar_mapa(Elemento *vector,int indice);//Guardar en ficheros
void borrar_elemento(Elemento **vector,int id);
void cargar_mapa(Elemento **e);
void elementos_mapa(Elemento *e);
int n_jugadores(Elemento *jm);
void borrar_mapa(Elemento **jm);

#endif
