#ifndef partida_H_
#define partida_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "tormenta.h"
#include "tienda.h"
#include "usuario.h"
#include "mapa.h"
#include "Mochila.h"

void lobby (usuario **u,configuracion c,int *indice,Elemento **jm,mochila **m,objetos *o,tormenta **t);

#endif