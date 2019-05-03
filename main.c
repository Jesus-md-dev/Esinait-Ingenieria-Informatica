#include "usuario.h"
#include "configuracion.h"
#include "tormenta.h"
#include "partida.h"
#include "Mochila.h"
#include "mapa.h"
#include "tienda.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void comprarobjeto(usuario *u,objetos *o,mochila **m,int indice);
void menu_principal();
int opciones_jugador(usuario *u,int i);
int opciones_admin(usuario *u,int i);
void logoutall(usuario **u);
int opciones_general();

int main ()
{	
	menu_principal();
	system("cls");
	return 0;
}

void menu_principal()
{
	int op, i, opc;
	i=-1;
	usuario *u;
	configuracion c;
	amigo *a;
	Elemento *jm;
	mochila *m;
	objetos *o;
	tormenta *t;
	o = (objetos*)malloc(0*sizeof(objetos));
	m = (mochila*)malloc(0*sizeof(mochila));
	u = (usuario*)malloc(0*sizeof(usuario));
	a = (amigo*)malloc(0*sizeof(amigo));
	jm = (Elemento*)malloc(0*sizeof(Elemento));
	t = (tormenta*)malloc(0*sizeof(tormenta));
	cargar_tormenta(&t);
	cargar_objetos(&o);
	cargar_usuarios(&u);
	cargar_configuracion(&c);
	cargar_amigos(&a);
	cargarficheroMochila (&m);
	
	do
	{
		opc=-1;
		if(i==-1)
		{
			op=opciones_general();
			if(op==0)opc=0;
		}
		else
		{
			if((strcmp(u[i].perfil,"ADM"))==0)
			{
				op=opciones_admin(u,i);
			}
			else
			{
				if((strcmp(u[i].perfil,"JGD"))==0)
				{
					op=opciones_jugador(u,i);
				}
			}
			if(op==0)
			{
				strcpy(u[i].estado,"OFF");
				i=-1;
			}
		}
		switch(op)
		{
			case 1: i=iniciar_sesion(&u,c);break;
			case 2: lobby(&u,c,&i,&jm,&m,o,&t);break;
			case 3: comprar_objetos(&m,o,&u,i,c);system("pause");break;
			case 4: ver_perfil(u,i);break;
			case 5: m_amigos(&a,u[i].nick,u);break;
			case 6: leerMochila(m,i,u);system("pause");break;
			case 7: mostrar_configuracion(&c);break;
			case 8: m_admin(&u);break;
			case 9: m_admin_tienda(&o);break;
			
		}
	}while(opc!=0);
	logoutall(&u);
	guardar_configuracion(c);
	guardar_usuarios(u);
	guardar_amigos(a);
	guardarficheroMochila(m);
	guardar_tormenta(t);
	borrar_mapa(&jm);
}

//cabecera: int opciones_jugador(usuario *u,int i)
//precondicion: recibe la estrcutura usuario y un indice
//postcondicion: muestra las opciones del jugador
int opciones_jugador(usuario *u,int i)
{
	int op;
	do
	{
		system("cls");
		printf("\n |%s| %s",u[i].nick,u[i].perfil);
		printf("     ESINAIT\n\n");
		printf("  1.Entrar/Cambiar Usuario\n");
		printf("  2.Jugar/Continuar Partida\n");
		printf("  3.Comprar Objeto\n");
		printf("  4.Ver Perfil\n");
		printf("  5.Amigos\n");
		printf("  6.Ver Mochila\n");
		printf("  0.Salir del Sistema\n");
		printf("\n\tOpcion: ");
		scanf("%d",&op);
	}while(op < 0 && op > 6);
	return op; 
}

//cabecera: int opciones_admin(usuario *u,int i)
//precondicion: recibe la estrcutura usuario y un indice
//postcondicion: muestra las opciones del admin
int opciones_admin(usuario *u,int i)
{
	int op;
	do
	{
		system("cls");
		printf("\n |%s| %s",u[i].nick,u[i].perfil);
		printf("     ESINAIT\n\n");
		printf("  1.Entrar/Cambiar Usuario\n");
		printf("  2.Jugar/Continuar Partida\n");
		printf("  3.Comprar Objeto\n");
		printf("  4.Ver Perfil\n");
		printf("  5.Amigos\n");
		printf("  6.Ver Mochila\n");
		printf("  7.Configuracion\n");
		printf("  8.Administrador\n");
		printf("  9.Menu Admin Objetos\n");
		printf("  0.Salir del Sistema\n");
		printf("\n\tOpcion: ");
		scanf("%d",&op);
	}while(op < 0 && op > 9);
	return op;
}

//cabecera: int opciones_general()
//precondicion: 
//postcondicion: muestra las opciones para todos
int opciones_general()
{
	int op;
	do
	{
		system("cls");
		printf("\n ||");
		printf("     ESINAIT\n\n");
		printf("  1.Entrar/Cambiar Usuario\n");
		printf("  0.Salir del Sistema\n");
		printf("\n\tOpcion: ");
		scanf("%d",&op);
	}while(op!=0&&op!=1);
	return op;
}

void logoutall(usuario **u)
{
	int i;
	for(i=0;i<nusuarios;i++)
	{
		strcpy((*u)[i].estado,"OFF");
	}
}