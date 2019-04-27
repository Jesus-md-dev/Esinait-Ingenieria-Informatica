#include "partida.h"

/*
int njugadores_EE (usuario *u);

void lobby (usuario **u,configuracion c,int indice,jmapa **jm,mochila **m,objetos *o);
*/
int op_usuario_partida(usuario *u,configuracion c);
int njugadores_EJ (usuario *u);
int njugadores_EE (usuario *u);
int op_admin_partida(usuario *u,configuracion c);
void jugadores_espera(usuario *u, configuracion c);
void iniciar_jugadores_partida(usuario **u,jmapa **jm,configuracion c);
void terminar_partida_jugadores(usuario **u,jmapa **jm);
void lista_indices(int *v,int indice);
void movimiento(jmapa **jm,int indice,configuracion c);

void lobby (usuario **u,configuracion c,int *indice,jmapa **jm,mochila **m,objetos *o)
{
	int op,turno=0,idob=-1,acciones=0,i=-1;
	do
	{
		system("cls");
		if(strcmp((*u)[*indice].estado,"EJ")==0)
		{
			do
			{
				do
				{
					i=indice_usuario((*u),(*jm)[turno].id);

					printf(" |%s|  Vida: %d/100  Acciones %d/%d\n\n",(*jm)[turno].id,(*u)[(*indice)].vida,c.n_acciones-acciones,c.n_acciones);
					printf(" Arma: ");
					if(idob==-1) {printf("Predeterminada\n");}
					else printf("%s",o[idob].item_ID);
					printf(" 1.Ver/Usar Mochila\n");
					printf(" 2.Usar Objeto/Disparar\n");
					printf(" 3.Mover Jugador\n");
					printf(" 4.Ver Objetos Cercanos\n");
					printf(" 5.Ver Oponentes Cercanos\n");
					printf(" 6.Ver Posicion Actual\n");
					printf(" 7.Finalizar Turno\n");
					printf(" 0.Volver al menu principal\n");
					printf("\n\tOpcion: ");
					scanf("%d",&op);
				}while(op < 0 && op > 7);
				switch (op)
				{
				case 1: idob=usarMochila(*m,*indice,*u,o);break;
				case 2: printf("Mantenimiento\n");system("pause");break;
				case 3: movimiento(&(*jm),turno,c);acciones++;break;
				case 4: printf("Mantenimiento\n");system("pause");break;
				case 5: printf("Mantenimiento\n");system("pause");break;
				case 6: printf("\n Posicion: (%d,%d)\n",(*jm)[turno].x,(*jm)[turno].y);break;
				case 7: acciones=c.n_acciones;break;
				}

				if(acciones>=c.n_acciones)
				{
					idob = -1;
					acciones = 0;
					turno++;
					if(turno > njugando)turno = 0;
				}
				njugando=njugadores_EJ(*u)-1;
				
				//if(njugando==1) {terminar_partida_jugadores(&(*u),&(*jm));}
			} while (op != 0);
		}
		else if(strcmp((*u)[*indice].estado,"GO")==0)
		{
			printf("Has muerto\n");
			printf("F\n");
			system("pause");
			strcpy((*u)[*indice].estado,"ON");
			op=0;//Apaño
		}
		else
		{
			if(strcmp((*u)[*indice].perfil,"JGD")==0)
			{
				op = op_usuario_partida(*u,c);
			}
			else if(strcmp((*u)[*indice].perfil,"ADM")==0)
			{
				op = op_admin_partida((*u),c);
			}
			switch(op)
			{
				case 1: strcpy((*u)[*indice].estado,"EE");break;
				case 2: strcpy((*u)[*indice].estado,"ON");break;
				case 3: iniciar_jugadores_partida(&(*u),&(*jm),c);break;
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
	printf("\n (%d/%d) Jugadores (Minimo) unidos a la partida\n\n",njugadores_EE(u),c.min_jugadores);
}

void iniciar_jugadores_partida(usuario **u,jmapa **jm,configuracion c)
{
	if(njugadores_EE(*u) >= c.min_jugadores){
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
			(*jm)[njugando-1].x = 0;
			(*jm)[njugando-1].y = 0;
			v[vindice] = v[n-1];
			n--;
			v = (int*) realloc (v,n*sizeof(int));	
		}while(n>0);

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
	for(i=0;i<nusuarios;i++)
	{
		if(strcmp((*u)[i].estado,"EJ")==0) printf(" %s, has ganado");
	}
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
		if(strcmp(u[i].estado,"EE")==0) n++;
	}
	return n;
}

int njugadores_EJ (usuario *u)
{
	int i;
	int n=0;
	for (i=0;i<nusuarios;i++)
	{
		if(strcmp(u[i].estado,"EJ")==0) n++;
	}
	return n;
}

void movimiento(jmapa **jm,int indice,configuracion c)
{
	int op;
	do
	{
		printf("|MOVIMIENTOS|\n");
		printf(" 1.Arriba\n");
		printf(" 2.Abajo\n");
		printf(" 3.Izquierda\n");
		printf(" 4.Derecha\n");
		scanf("%d",&op);
	} while (op < 1 && op > 4);
	switch (op)
	{
	case 1: (*jm)[indice].x += c.dist_paso;break;
	case 2: (*jm)[indice].x -= c.dist_paso;break;
	case 3: (*jm)[indice].y -= c.dist_paso;break;
	case 4: (*jm)[indice].y += c.dist_paso;break;
	}
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