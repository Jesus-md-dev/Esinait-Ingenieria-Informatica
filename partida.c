#include "partida.h"

int op_usuario_partida(usuario *u,configuracion c);
int id_objeto(objetos *o,mochila *m,usuario *u,int indice);
int op_admin_partida(usuario *u,configuracion c);
void jugadores_espera(usuario *u, configuracion c);
void terminar_partida_jugadores(usuario **u,Elemento **jm);
void movimiento(Elemento **jm,int indice,configuracion c);
int distancia_e(Elemento *jm,char *u1,char *u2);
int distancia(int x1,int y1,int x2,int y2);
void usar_arma(usuario **u,Elemento **jm,mochila **m,int turno,int alcance,int danio,int *ido,objetos *o);
void mostrar_jugadores_cercanos(Elemento *jm,int idm,int alcance);
void mostrar_objetos_cercanos(Elemento **jm,int *idm,configuracion c,mochila **m,usuario *u,int indice);
int turno_jugador(Elemento *jm,char *nick);

void lobby (usuario **u,configuracion c,int *indice,Elemento **jm,mochila **m,objetos *o)
{
	int op,turno=0,idob=-1,acciones=0;
	do
	{
		if(strcmp((*u)[*indice].estado,"EJ")==0)
		{
			do
			{
				do
				{
					while(strcmp((*jm)[turno].tipo,"Jugador")!=0) 
					{
						turno++;
						if(turno>=nelementos-1) turno=0;
					}
					printf(" |%s|  Vida: %d/100  Acciones %d/%d\n\n",(*jm)[turno].nombre,(*u)[(*indice)].vida,c.n_acciones-acciones,c.n_acciones);
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
					if(o[idob].alcance==0) printf("Cura/Escudo Mantenimiento \n");
					else usar_arma(&(*u),&(*jm),&(*m),turno,o[idob].alcance,o[idob].porcentaje_d_e,&idob,o);
				}
				else usar_arma(&(*u),&(*jm),&(*m),turno,c.dist_fisico,5,&idob,o);
				system("pause");break;
				case 3: 
				movimiento(&(*jm),turno,c);
				acciones++;break;
				case 4: 
				mostrar_objetos_cercanos(&(*jm),&turno,c,&(*m),(*u),*indice);
				break;
				case 5:
				if(idob!=-1){mostrar_jugadores_cercanos(*jm,turno,o[idob].alcance);}
				else mostrar_jugadores_cercanos(*jm,turno,c.dist_fisico);
				system("pause");
				break;
				case 6: 
				printf("\n Posicion: (%d,%d)\n",(*jm)[turno].posx,(*jm)[turno].posy);system("pause");break;
				case 7: 
				acciones=c.n_acciones;break;
				}
				if(acciones>=c.n_acciones)
				{
					idob = -1;
					acciones = 0;
					do{
						turno++;
						if(turno>=nelementos-1) turno=0;
					}while(strcmp((*jm)[turno].tipo,"Jugador")!=0);
					if(turno > nelementos)turno = 0;
				}
				
				if(njugadores_EJ(*u)==1) {terminar_partida_jugadores(&(*u),&(*jm));}
			} while (op != 0);
			*indice=indice_usuario((*u),(*jm)[turno].nombre);
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
				case 3: 
				if(njugadores_EE(*u) >= c.min_jugadores)
				{
					generar_mapa(&(*jm),&(*u),o,c);
					printf("Turno: %i\n",turno);
					printf("Jugador: %s\n",(*jm)[turno].nombre);
					system("pause");
				}
				else
				{ 
					printf(" Minimo de jugadores no superado\n");
					system("pause");
				}
				break;
			}
		}
	}while (op!=0);
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

void terminar_partida_jugadores(usuario **u,Elemento **jm)
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

void movimiento(Elemento **jm,int indice,configuracion c)
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
	case 1: (*jm)[indice].posx += c.dist_paso;break;
	case 2: (*jm)[indice].posx -= c.dist_paso;break;
	case 3: (*jm)[indice].posy -= c.dist_paso;break;
	case 4: (*jm)[indice].posy += c.dist_paso;break;
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

void usar_arma(usuario **u,Elemento **jm,mochila **m,int turno,int alcance,int danio,int *ido,objetos *o)
{
	int op,i,r=0,dist,indice,cont=0,indicemapa;
	char nick[50];
	do{
		mostrar_jugadores_cercanos((*jm),turno,alcance);
		printf(" 1.Elegir objetivo\n");
		printf(" 0.Salir\n");
		printf("	Opcion: ");
		fflush(stdin);
		scanf("%d",&op);
	}while(op!=0 && op!=1);
	if(op==1)
	{
		printf(" Introduce su id: ");
		fflush(stdin);
		fgets(nick,50,stdin);
		fixstring(nick);
		printf("%s\n",nick);
		for(i=0;i<nelementos;i++)
		{
			printf("Tipo: %s\n",(*jm)[i].tipo);
			if(strcmp((*jm)[i].tipo,"Jugador")==0)
			{
				printf("Nombre: %s\n",(*jm)[i].nombre);
				if(strcmp(nick,(*jm)[i].nombre)==0) r=1;
			}
		}
	}
	if(r==0) printf(" Usuario no encontrado\n");
	if(r==1) 
	{
		indice=indice_usuario((*u),nick);
		printf(" %i ->",(*u)[indice].vida);
		(*u)[indice].vida-=danio;
		printf(" %i\n",(*u)[indice].vida);
		if(*ido!=-1)
		{
			r=0;
			for(i=0;i<nmochilas;i++)
			{
				printf(" %s = %s\n",nick,(*jm)[turno].nombre);
				if(strcmp(nick,(*jm)[turno].nombre)==0)
				{
					printf(" %s = %s\n",o[*ido].item_ID,(*m)[i].idobj);
					if(strcmp(o[*ido].item_ID,(*m)[i].idobj)==0)
					{ 
						if(r=0) 
						{
							eliminarobjeto(&(*m),i);
							r=1;
						}
						cont++;
					}
				}
			}
			if(cont==1) *ido=-1;
		}
		if((*u)[indice].vida==0)
		{
			strcpy((*u)[indice].estado,"GO");
			indicemapa=turno_jugador((*jm),(*u)[indice].nick);
			borrar_elemento(&(*jm),indicemapa);
		}
	}
}

int distancia_e(Elemento *jm,char *u1,char *u2)
{
	int x,y,dist,i,id1,id2;
	for(i=0;i<nelementos;i++){
		if(strcmp(jm[i].nombre,u1)==0) id1=i;
		if(strcmp(jm[i].nombre,u2)==0) id2=i;
	}
	x=jm[id1].posx-jm[id2].posx;
	y=jm[id1].posy-jm[id2].posy;
	dist=sqrt(pow(x,2)+pow(y,2));
	return dist;
}

void mostrar_jugadores_cercanos(Elemento *jm,int idm,int alcance)
{
	int i;
	for(i=0;i<nelementos;i++)
	{
		if(strcmp(jm[i].tipo,"Jugador")==0)
		{
			if(i!=idm)
			{
				if(distancia(jm[idm].posx,jm[idm].posy,jm[i].posx,jm[i].posy) <= alcance) printf(" -%s (%i,%i)\n",jm[i].nombre,jm[i].posx,jm[i].posy);
			}
		}
	}
}

void mostrar_objetos_cercanos(Elemento **jm,int *idm,configuracion c,mochila **m,usuario *u,int indice)
{
	int i,op,id=-1;
	char nombre[50];
	do{
		do{
			for(i=0;i<nelementos;i++)
			{
				if(strcmp((*jm)[i].tipo,"Objeto")==0);
				{
					if(distancia((*jm)[*idm].posx,(*jm)[*idm].posy,(*jm)[i].posx,(*jm)[i].posy)<=c.dist_recoger) printf(" -%s (%i,%i)\n",(*jm)[i].nombre,(*jm)[i].posx,(*jm)[i].posy);
				}
			}
			printf(" 1.Recoger Objeto\n");
			printf(" 0.Salir\n");
			printf("\n Opcion: ");
			scanf("%d",&op);
		}while(op != 0 && op !=1);
		if(op == 1)
		{
			printf(" Introduce el id del objeto: ");
			fflush(stdin);
			fgets(nombre,50,stdin);
			fixstring(nombre);
			for(i=0;i<nelementos;i++)
			{
				if(strcmp((*jm)[i].tipo,"Objeto")==0)
				{
					if(strcmp(nombre,(*jm)[i].nombre)==0)
					{ 
						if(distancia((*jm)[*idm].posx,(*jm)[*idm].posy,(*jm)[i].posx,(*jm)[i].posy)<=c.dist_recoger) id = i;
					}
				}
			}
			if(id==-1) {printf(" El objeto no existe o esta fuera de rango");}
			else
			{
				printf("Objeto (%s) recogido\n",(*jm)[i].nombre);
				guardar_mochila(&(*m),(*jm)[i].nombre,indice,u,c);
				borrar_elemento(&(*jm),i);
				*idm = turno_jugador((*jm),u[indice].nick);

			}
		}
	}while(op !=0);
}

int distancia(int x1,int y1,int x2,int y2){return sqrt(pow(x1-x2,2)+pow(y1-y2,2));}

int turno_jugador(Elemento *jm,char *nick)
{
	int i;
	for(i=0;i<nelementos;i++)
	{
		if(strcmp(nick,jm[i].nombre)) return i;
	}
	printf(" Usuario no encontrado\n");
	return -1;
}