#include "mapa.h"

//FUNCIONES

void guardar_mapa (Elemento *vector);//Guardar en ficheros

//Cebecera: void aleatorio(int* x, int* y)
//Precondicion: x e y deben estar inicializados
//Postcondicion: Devuelve por referencia dos numeros aleatorios
void aleatorio(int* x, int* y){
	do{
		*x= rand() % (N2-N1+1) + N1;//Aleatorio para el eje x
		*y= rand() % (M2-M1+1) + M1;//Aleatorio para el eje y
	}while((sqrt(pow(*x,2)+pow(*y,2)))>R);//Mientras el modulo de las posiciones x e y sea mayor que el radio del mapa se repita ya que no se puede generar fuera
}

//Cabecera: void generar(Elementos vector[], configuracion c, usuario u[])
//Precondicion: Ninguna
//Postcondicion: Guardar en vector[] los datos de cada elemento que haya en el mapa generado
void generar_mapa (Elemento **vector, usuario **u){

	int i,njugadores,obj_id,vindice,n=0;
	int *v;
	
    njugadores= njugadores_EE((*u));
	printf("%i\n",njugadores);
    srand (time(NULL));

	v = (int*) malloc (n*sizeof(int));
    
	for(i=0;i<nusuarios;i++)
	{
		if(strcmp((*u)[i].estado,"EE")==0)
		{
			strcpy((*u)[i].estado,"EJ");
			n++;
			v = (int*) realloc (v,n*sizeof(int));
			v[n-1] = i;
		}
	}
	nelementos=0;
	
	do{//Bucle para guardar jugadores
		nelementos++;
		printf("n.elementos = %i\n",nelementos);
		(*vector)= (Elemento*) realloc((*vector), nelementos*sizeof(Elemento));
		strcpy((*vector)[nelementos-1].tipo, "Jugador");
        vindice = rand() % n;
		printf("vindice = %i\n",vindice);
		strcpy((*vector)[nelementos-1].nombre,(*u)[v[vindice]].nick);
		printf("%s = %s\n",(*vector)[nelementos-1].nombre,(*u)[v[vindice]].nick);
		aleatorio(&(*vector)[nelementos-1].posx, &(*vector)[nelementos-1].posy);
        v[vindice] = v[n-1];
		n--;
		v = (int*) realloc (v,n*sizeof(int));
	}while(n>0);

	for(i=0 ; i<(njugadores*3) ; i++){//Bucle para guardar objetos

        nelementos++;
        (*vector)= (Elemento*) realloc((*vector), nelementos*sizeof(Elemento));

        strcpy((*vector)[i].tipo, "Objeto");

        obj_id=rand() % ;//Numero de objetos

        switch(obj_id){

            case 0: strcpy((*vector)[nelementos-1].nombre, "PTL01");break;
            case 1: strcpy((*vector)[nelementos-1].nombre, "ESC01");break;
            case 2: strcpy((*vector)[nelementos-1].nombre, "BLL01");break;
            case 3: strcpy((*vector)[nelementos-1].nombre, "BOT01");break;
            case 4: strcpy((*vector)[nelementos-1].nombre, "POC01");break;
            case 5: strcpy((*vector)[nelementos-1].nombre, "VEN01");break;
            default: strcpy((*vector)[nelementos-1].nombre, "PTL01");break;
        }

        aleatorio(&(*vector)[i].posx, &(*vector)[i].posy);
	}
    
}

//Cabecera: void guardar_mapa (Elemento vector[])
//Precondicion: Que el vector vector[] de Elementos este inicializado
//Postcondicion: Imprimir en un fichero todos los datos contenidos en el vector vector[]
void guardar_mapa (Elemento *vector){

	FILE *fp;
	int i;

	if((fp= fopen("mapa.txt","w+"))==NULL){
		printf("No se ha podido crear mapa.txt\n");
		exit(1);
	}
    else{
        printf("mapa.txt se ha crado con exito\n");
        system("pause");
        for(i=0; i<nelementos; i++){
            fprintf(fp, "%s/%s/%i/%i\n",vector[i].tipo, vector[i].nombre, vector[i].posx, vector[i].posy);
        }

        fclose(fp);
    }
}

void borrar_elemento(Elemento **vector,int id)
{
    strcpy((*vector)[id].nombre,(*vector)[nelementos-1].nombre);
    strcpy((*vector)[id].tipo,(*vector)[nelementos-1].tipo);
    (*vector)[id].posx = (*vector)[nelementos-1].posx;
    (*vector)[id].posy = (*vector)[nelementos-1].posy;
    (*vector) = (Elemento*) realloc ((*vector),nelementos-1*(sizeof(Elemento)));
    nelementos--; 
}