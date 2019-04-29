#ifndef _MAPA_H_
#define _MAPA_H_

//LIBRERIAS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "usuario.h"
//#include "tormenta.h"

//MACROS
#define N1 -50 //Eje x negativo del MAPA
#define N2 50 //Eje x positivo del MAPA
#define M1 -50 //Eje y negativo del MAPA
#define M2 50 //Eje y positivo del MAPA
#define R 50 //Radio del mapa

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

void cargar_mapa(Elemento **vector, usuario *u);//Guardar en estructura
void guardar_mapa(Elemento *vector);//Guardar en ficheros

#endif
