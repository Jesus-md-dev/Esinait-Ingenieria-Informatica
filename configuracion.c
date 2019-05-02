#include "configuracion.h"

/*
void fixstring(char *a);

void cargar_configuracion(configuracion *c);

void guardar_configuracion(configuracion c);

void mostrar_configuracion(configuracion *c);
*/

void fixstring(char *a)
{
	a[strlen(a)-1]='\0';
}

void cargar_configuracion(configuracion *c){
	char cadena [100];
	char *ptr;
	char *delim="/";
	FILE *f;
	f=fopen("configuracion.txt","r+");
	if(f==NULL)
	{
		(*c).radio_mapa=1200;
		(*c).dist_recoger=5;
		(*c).dist_fisico=10;
		(*c).dinero_defecto=250;
		(*c).min_jugadores=2;
		(*c).dist_paso=5;
		(*c).tam_mochila=7;
		(*c).partidas_nivel=2;
		(*c).n_acciones=5;
	}
	else
	{	
		if(fgets(cadena,100,f)!=NULL)
		{
			fixstring(cadena);
			fflush(stdin);
			ptr=strtok(cadena,delim);
			(*c).radio_mapa=atoi(ptr);
			ptr=strtok(NULL,delim);
			(*c).dist_recoger=atoi(ptr);
			ptr=strtok(NULL,delim);
			(*c).dist_fisico=atoi(ptr);
			ptr=strtok(NULL,delim);
			(*c).dinero_defecto=atoi(ptr);
			ptr=strtok(NULL,delim);
			(*c).min_jugadores=atoi(ptr);
			ptr=strtok(NULL,delim);
			(*c).dist_paso=atoi(ptr);
			ptr=strtok(NULL,delim);
			(*c).tam_mochila=atoi(ptr);
			ptr=strtok(NULL,delim);
			(*c).partidas_nivel=atoi(ptr);
			ptr=strtok(NULL,delim);
			(*c).n_acciones=atoi(ptr);
		}
	}
	fclose(f);
}

void guardar_configuracion(configuracion c)
{
	FILE *f;
	int i;
	f=fopen("configuracion.txt","w+");
	fprintf(f,"%i/%i/%i/%i/%i/%i/%i/%i/%i\n",c.radio_mapa,c.dist_recoger,c.dist_fisico,c.dinero_defecto,c.min_jugadores,c.dist_paso,c.tam_mochila,c.partidas_nivel,c.n_acciones);
	fclose(f);
}

void mostrar_configuracion(configuracion *c)
{
	int op,valor;
	do{
		do{
			system("cls");
			printf(" |CONFIGURACION|\n");
			printf(" 1.Radio Mapa: %d\n",(*c).radio_mapa);
			printf(" 2.Distancia Recoger: %d\n",(*c).dist_recoger);
			printf(" 3.Distancia A.Fisico: %d\n",(*c).dist_fisico);
			printf(" 4.Dinero Base: %d\n",(*c).dinero_defecto);
			printf(" 5.Minimo Jugadores: %d\n",(*c).min_jugadores);
			printf(" 6.Distancia Paso: %d\n",(*c).dist_paso);
			printf(" 7.Tamanio Mochila: %d\n",(*c).tam_mochila);
			printf(" 8.Victorias Nivel: %d\n",(*c).partidas_nivel);
			printf(" 9.Numero Acciones: %d\n",(*c).n_acciones);
			printf("\n 1-9.Modificar\n 0.Salir\n Opcion: ");
			scanf("%d",&op);
		}while(op<0&&op>9);
		if(op!=0)
		{
			printf("Introduce nuevo valor: ");
			scanf("%d",&valor);
			switch(op)
			{
				case 1:(*c).radio_mapa=valor;break;
				case 2:(*c).dist_recoger=valor;break;
				case 3:(*c).dist_fisico=valor;break;
				case 4:(*c).dinero_defecto=valor;break;
				case 5:(*c).min_jugadores=valor;break;
				case 6:(*c).dist_paso=valor;break;
				case 7:(*c).tam_mochila=valor;break;
				case 8:(*c).partidas_nivel=valor;break;
				case 9:(*c).n_acciones=valor;break;
			}
		}
	}while(op!=0);
}