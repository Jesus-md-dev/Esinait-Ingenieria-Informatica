#ifndef configuracion_H_
#define configuracion_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
	int radio_mapa;
	int dist_recoger;
	int dist_fisico;
	int dinero_defecto;
	int min_jugadores;
	int dist_paso;
	int tam_mochila;
	int partidas_nivel;
	int n_acciones;
}configuracion;

void fixstring(char *a);

void cargar_configuracion(configuracion *c);

void guardar_configuracion(configuracion c);

void mostrar_configuracion(configuracion *c);

#endif