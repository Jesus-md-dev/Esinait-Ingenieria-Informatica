#include "partida.h"

/*
int njugadores_EE (usuario *u);

void lobby (usuario **u,configuracion c,int indice,jmapa **jm,mochila **m,objetos *o);
*/
int op_usuario_partida(usuario *u,configuracion c);
int njugadores_EJ (usuario *u);
int id_objeto(objetos *o,mochila *m,usuario *u,int indice);
int njugadores_EE (usuario *u);
int op_admin_partida(usuario *u,configuracion c);
void jugadores_espera(usuario *u, configuracion c);
void iniciar_jugadores_partida(usuario **u,jmapa **jm,configuracion c);
void terminar_partida_jugadores(usuario **u,jmapa **jm);
void movimiento(jmapa **jm,int indice,configuracion c);
void usar_arma(usuario **u,jmapa *jm,mochila **m,int turno,int alcance);

void lobby (usuario **u,configuracion c,int *indice,jmapa **jm,mochila **m,objetos *o)
{
	int op,turno=0,idob=-1,acciones=0;
	do
	{
		system("cls");
		if(strcmp((*u)[*indice].estado,"EJ")==0)
		{
			do
			{
				do
				{
					*indice=indice_usuario((*u),(*jm)[turno].id);

					printf(" |%s|  Vida: %d/100  Acciones %d/%d\n\n",(*jm)[turno].id,(*u)[(*indice)].vida,c.n_acciones-acciones,c.n_acciones);
					printf(" Arma: ");
					if(idob==-1) {printf("Predeterminada\n\n");}
					else printf("%s\n\n",o[idob].item_ID);
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
				case 1:
				idob=id_objeto(o,(*m),(*u),*indice);break;
				case 2:
				if(idob!=-1)
				{
					if(o[idob].alcance==0) usar_arma(&(*u),(*jm),&(*m),turno,o[idob].alcance,o[idob].porcentaje_d_e);
					else printf("Cura/Escudo Mantenimiento \n");
				}
				else usar_arma(&(*u),(*jm),&(*m),turno,c.dist_fisico,5);
				system("pause");break;
				case 3: 
				movimiento(&(*jm),turno,c);
				acciones++;break;
				case 4: 
				printf("Mantenimiento\n");
				system("pause");break;
				case 5:
				printf("Mantenimiento\n");
				system("pause");break;
				case 6: 
				printf("\n Posicion: (%d,%d)\n",(*jm)[turno].x,(*jm)[turno].y);break;
				case 7: 
				acciones=c.n_acciones;break;
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
int id_objeto(objetos *o,mochila *m,usuario *u,int indice)
{
	int i,id = usarMochila(m,indice,u);
	for(i=0;i<nobjetos;i++)
	{
		if(strcmp(o[i].item_ID,m[id].idobj)==0) return i;
	}
	return -1;
}

void usar_arma(usuario **u,jmapa *jm,mochila **m,int turno,int alcance)
{
	int op,i,dist;
	char nick;
	do{
		for(i=0;i<njugando;i++)
		{
			if(i!=turno)
			{
				dist=distancia(jm,jm[turno].id,jm[i].id);
				if(distancia > alcance){prin(" Fuera de Rango");}
				printf(" %s\n",jm[i].id);
			}
		}
		printf(" 1.Elegir objetivo\n");
		printf(" 0.Salir\n");
		printf("	Opcion: ");
		scanf("%d",&op);
	}while(op!=0 || op!=1);
	if(op==1)
	{
		printf(" Introduce su id: ");
		scanf("%s",&nick);
		for(i=0;i<n;i++)
		{
			if(strcmp(nick,jm[i].id)==0)
		}
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

int distancia(jmapa *jm,char *u1,char *u2)
{
	int x,y,dist,i,id1,id2;
	for(i=0;i<njugando;i++){
		if(strcmp(jm[i].id,u1)==0) id1=i;
		if(strcmp(jm[i].id,u2)==0) id2=i;
	}
	x=jm[id1].x-jm[id2].x;
	y=jm[id1].y-jm[id2].y;
	printf("\n\n-----------------------------------\n\n");
	printf("%d = %d - %d\n",x,jm[id1].x,jm[id2].x);
	printf("%d = %d - %d\n",y,jm[id1].y,jm[id2].y);
	dist=sqrt(pow(x,2)+pow(y,2));
	printf("%d = Raiz( %d^2 + %d^2 )\n",dist,x,y);
	return dist;
}