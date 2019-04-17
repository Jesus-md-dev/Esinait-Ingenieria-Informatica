#include "usuario.h"
#include "configuracion.h"
#include "partida.h"
#include "Mochila.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void comprarobjeto(usuario *u,objeto *o,mochila **m,int indice);
/////////////////////////////
void menu_principal();
int opciones_jugador(usuario *u,int i);
int opciones_admin(usuario *u,int i);
int opciones_general();

int main ()
{
	//<DADFGSDFGAFDSBGSAFDwgeagr
	menu_principal();
	system("cls");
	return 0;
}

void menu_principal()
{
	int op,i,opc;
	i=-1;
	usuario *u;
	configuracion c;
	amigo *a;
	jmapa *jm;
	mochila *m;
	objeto *o;
	o = (objeto*)malloc(0*sizeof(objeto));
	m = (mochila*)malloc(0*sizeof(mochila));
	u = (usuario*)malloc(0*sizeof(usuario));
	a = (amigo*)malloc(0*sizeof(amigo));
	jm = (jmapa*)malloc(0*sizeof(jmapa));
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
			case 2: lobby(&u,c,i,&jm,&m);break;
			case 3: comprarobjeto(u,o,&m,i);break;
			case 4: ver_perfil(u,i);break;
			case 5: m_amigos(&a,u[i].nick,u);break;
			case 6: lista_usuarios(u);system("pause");break;
			case 7: lista_usuarios_on(u);system("pause");break;
			case 8: mostrar_configuracion(&c);break;
			case 9: m_admin(&u);break;
		}
	}while(opc!=0);
	guardar_configuracion(c);
	guardar_usuarios(u);
	guardar_amigos(a);
	guardarficheroMochila(m);
}

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
		printf("  0.Salir del Sistema\n");
		printf("\n\tOpcion: ");
		scanf("%d",&op);
	}while(op<0&&op>5);
	return op;
}

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
		printf("  6.Listar Usuarios\n");
		printf("  7.Listar Usuarios En Linea\n");
		printf("  8.Configuracion\n");
		printf("  9.Administrador\n");
		printf("  0.Salir del Sistema\n");
		printf("\n\tOpcion: ");
		scanf("%d",&op);
	}while(op<0&&op>9);
	return op;
}

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

////////////////////////

void comprarobjeto(usuario *u,objeto *o,mochila **m,int indice)
{
	guardar_mochila(&(*m),"pstl",indice,u);
	leerMochila((*m),indice,u);
}