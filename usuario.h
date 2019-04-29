#ifndef usuario_H_
#define usuario_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "configuracion.h"

typedef struct
{
	char nick[50];
	char nombre[50];
	int nivel;	
	int vida;
	int escudo;
	char estado[5]; //Offline (OFF), Online (ON), Bloqueado (BQ), En Juego (EJ), En Espera (EE), Eliminado (GO)
	int dinero;
	int pjugadas;
	int pganadas;
	char perfil[4]; //usuario (JGD) o administrador (ADM).
	char contrasenia[20];	
}usuario;

typedef struct
{
	char nick_user[50];
	char nick_amig[50];
}amigo;

int nusuarios;

int namigos;

void cargar_usuarios(usuario **u);

void guardar_usuarios(usuario *u);

void cargar_amigos(amigo **a);

void guardar_amigos(amigo *a);

void ver_perfil(usuario *u,int i);

void lista_usuarios (usuario *u);

void lista_usuarios_on(usuario *u);

void m_admin (usuario **u);

int iniciar_sesion(usuario **u,configuracion c);

void m_amigos(amigo **a,char *nick,usuario *u);

int indice_usuario(usuario *u,char id[100]);

int njugadores_EE (usuario *u);

int njugadores_EJ (usuario *u);

#endif