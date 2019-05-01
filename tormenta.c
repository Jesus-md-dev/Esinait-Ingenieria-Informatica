#include "tormenta.h"

void aleatorio_tormenta(int* x, int* y,tormenta *t,int indice);

void cargar_tormenta(tormenta **t){
	char cadena[100];
	char *ptr;
	char *delim="/";
	FILE *f;
	ntormentas=0;
	f=fopen("tormenta.txt","r");
	if(f==NULL)
	{
		printf("No se ha podido abrir el fichero tormenta.txt\n");
		system("pause");
	}
	else
	{
		while(fgets(cadena,100,f)!=NULL)
		{
			fixstring(cadena);
			fflush(stdin);
			*t=(tormenta* )realloc((*t),(ntormentas+1)*sizeof(tormenta));
			ntormentas++;
            ptr=strtok(cadena,delim);
			(*t)[ntormentas-1].x=atoi(ptr);
			ptr=strtok(NULL,delim);
			(*t)[ntormentas-1].y=atoi(ptr);
			ptr=strtok(NULL,delim);
			(*t)[ntormentas-1].diametro=atoi(ptr);
			ptr=strtok(NULL,delim);
			(*t)[ntormentas-1].tiempo=atoi(ptr);
		}
	}
	fclose(f);
}

void guardar_tormenta(tormenta *t)
{
	FILE *f;
	int i;
	f=fopen("tormenta.txt","w");
	for(i=0;i<ntormentas;i++)
	{
		fprintf(f,"%i/%i/%i/%i\n",t[i].x,t[i].y,t[i].diametro,t[i].tiempo);
	}
	fclose(f);
}

void generar_tormentas(tormenta **t,configuracion c)
{
    int x,y,tiempo=8;
    do{
		ntormentas++;
		(*t) = (tormenta*)realloc((*t),ntormentas*sizeof(tormenta));
        if((ntormentas-1)==0)
        {
            (*t)[ntormentas-1].diametro=(c.radio_mapa*2);
            (*t)[ntormentas-1].tiempo=tiempo;
            (*t)[ntormentas-1].x=0;
            (*t)[ntormentas-1].y=0;
        }
        else{
            (*t)[ntormentas-1].diametro=((*t)[ntormentas-2].diametro/2);
            (*t)[ntormentas-1].tiempo=((*t)[ntormentas-2].diametro/2);
            aleatorio_tormenta(&x,&y,(*t),ntormentas-2);
            (*t)[ntormentas-1].x=x;
            (*t)[ntormentas-1].y=y;
        }
    }while(ntormentas < 4);
}

void aleatorio_tormenta(int* x, int* y,tormenta *t,int indice)
{
	int raiz;
	do{
		*x = (rand() % ((((t[indice].diametro/2)+1)*2)-(t[indice].diametro/2)))-t[indice].diametro/2;
		*y = (rand() % ((((t[indice].diametro/2)+1)*2)-(t[indice].diametro/2)))-t[indice].diametro/2;
		raiz = sqrt(pow(*x,2) + pow(*y,2));
	}while(raiz > (t[indice].diametro/2));
}