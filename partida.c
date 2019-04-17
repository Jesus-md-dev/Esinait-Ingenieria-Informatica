#include "partida.h"

/*
int njugadores_EE (usuario *u);

void lobby (usuario **u,configuracion c,int indice);
*/
int op_usuario_partida(usuario *u,configuracion c);
int op_admin_partida(usuario *u,configuracion c);
void jugadores_espera(usuario *u, configuracion c);
void iniciar_jugadores_partida(usuario **u,jmapa **jm,configuracion c);
void terminar_partida_jugadores(usuario **u,jmapa **jm);
void lista_indices(int *v,int indice);

void lobby (usuario **u,configuracion c,int indice,jmapa **jm)
{
	int op,turno;
	do
	{
		system("cls");
		if(strcmp((*u)[indice].estado,"EJ")==0)
		{
			//ADFAGSAFGSDFG
			printf(" Vida: (*u)[i].\n");
			printf(" 1.Mover\n");
			printf(" 2.Mochila\n");
			printf(" 3.Jugadores\n");
			printf(" 4.Mapa\n");
			printf(" 0.Salir\n");
			printf("pene")
		}
		else if(strcmp((*u)[indice].estado,"GO")==0)
		{
			printf("Has muerto\n");
			printf("F\n");
			system("pause");
			strcpy((*u)[indice].estado,"ON");
			op=0;//Apaño
		}
		else
		{
			if(strcmp((*u)[indice].perfil,"JGD")==0)
			{
				op = op_usuario_partida(*u,c);
			}
			else if(strcmp((*u)[indice].perfil,"ADM")==0)
			{
				op = op_admin_partida((*u),c);
			}
			switch(op)
			{
				case 1: strcpy((*u)[indice].estado,"EE");break;
				case 2: strcpy((*u)[indice].estado,"ON");break;
				case 3: iniciar_jugadores_partida(&(*u),&(*jm),c);break;
				case 4: terminar_partida_jugadores(&(*u),&(*jm));break;
			}
		}
	}while (op!=0);
	system("cls");
}

int op_usuario_partida(usuario *u,configuracion c)
{
	int r;
	{
		printf("\t ||JUGADORES ESPERA||\n\n");
		jugadores_espera(u,c);
		printf(" 1.Unirse\n");
		printf(" 2.Salir lista\n");
		printf(" 0.Salir\n");
		printf("\t Opcion: ");
		scanf("%d",&r);
		system("cls");
	}while (r<0&&r>2);
	return r;
}

int op_admin_partida(usuario *u,configuracion c)
{
	int r;
	do
	{
		printf("||JUGADORES ESPERA||\n");
		jugadores_espera(u,c);
		printf(" 1.Unirse\n");
		printf(" 2.Salir lista\n");
		printf(" 3.Iniciar Partida\n");
		printf(" 4.Terminar Partida\n");
		printf(" 0.Salir\n");
		printf("\t Opcion: ");
		scanf("%d",&r);
		system("cls");
	}while (r<0&&r>4);
	return r;
}

void jugadores_espera(usuario *u, configuracion c)
{
	int i;
	int n=0;
	for (i=0;i<nusuarios;i++)
	{
		if(strcmp(u[i].estado,"EE")==0) 
		{
			printf(" -%s\n",u[i].nick);
			n++;
		}
	}
	printf("\n(%d/%d) Jugadores (Minimo) unidos a la partida\n",njugadores_EE(u),c.min_jugadores);
}

void iniciar_jugadores_partida(usuario **u,jmapa **jm,configuracion c)
{
	if(njugadores_EE(*u) > c.min_jugadores){
		srand (time(NULL));
		int i,aux,vindice,n=0;
		int *v;
		v = (int*) malloc (n*sizeof(int));
		for(i=0;i<nusuarios;i++)
		{
			if(strcmp((*u)[i].estado,"EE")==0)
			{
				strcpy((*u)[i].estado,"EJ");
				n++;
				v = (int*) realloc (v,n*sizeof(int));
				v[n-1] = i;
				lista_indices(v,n);
			}
		}
		srand (time(NULL));
		do
		{
			njugando++;
			(*jm)=(jmapa*)realloc((*jm),njugando*sizeof(jmapa));
			vindice = rand() % n;
			strcpy((*jm)[njugando-1].id,(*u)[v[vindice]].nick);
			v[vindice] = v[n-1];
			n--;
			v = (int*) realloc (v,n*sizeof(int));	
		}while(n>0);

	////////////////////////
		for(int i=0;i<njugando;i++)
		{
			printf("%i %s\n",i,(*jm)[i].id);
		}
	}
	else
	{ 
		printf(" Minimo de jugadores no superado\n");
		system("pause");
	}

}

void terminar_partida_jugadores(usuario **u,jmapa **jm)
{
	int i;
	for (i=0;i<nusuarios;i++)
	{
		if(strcmp((*u)[i].estado,"EJ")==0||strcmp((*u)[i].estado,"GO")==0) strcpy((*u)[i].estado,"ON");
	}
	free(*jm);
}

int njugadores_EE (usuario *u)
{
	int i;
	int n=0;
	for (i=0;i<nusuarios;i++)
	{
		if(strcmp(u[i].estado,"EE")==0)n++;
	}
	return n;
}




/////////////////////////////////////
void lista_indices(int *v,int indice)
{
	int i=0;
	for(i=0;i<indice;i++)
	{
		printf("%i ",v[i]);
	}
	printf("\n");
}