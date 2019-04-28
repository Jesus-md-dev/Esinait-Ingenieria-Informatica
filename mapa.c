#include "mapa.h"

//FUNCIONES

void generar_mapa (Elemento **vector, usuario *u);//Guardar en estructura
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
void cargar_mapa (Elemento **vector, usuario *u){

	int i,j=0, njugadores, obj_id;

    njugadores= njugadores_EE(u);

	for(i=0; i<njugadores; i++){//Bucle para guardar jugadores

		nelementos++;
		(*vector)= (Elemento*) realloc((*vector), nelementos*sizeof(Elemento));

		strcpy((*vector)[i].tipo, "Jugador");

		while(strcmp(u[j].estado, "EJ")!=0){
			i++;
		};

		strcpy((*vector)[i].nombre, u[j].nick);

		aleatorio(&(*vector)[i].posx, &(*vector)[i].posy);

	}

	for( ; i<(njugadores*3) ; i++){//Bucle para guardar objetos

        nelementos++;
        (*vector)= (Elemento*) realloc((*vector), nelementos*sizeof(Elemento));

        strcpy((*vector)[i].tipo, "Objeto");

        obj_id=rand() % 7;//Numero de objetos

        switch(obj_id){

            case 0: strcpy((*vector)[i].nombre, "PTL01");break;
            case 1: strcpy((*vector)[i].nombre, "ESC01");break;
            case 2: strcpy((*vector)[i].nombre, "BLL01");break;
            case 3: strcpy((*vector)[i].nombre, "BOT01");break;
            case 4: strcpy((*vector)[i].nombre, "POC01");break;
            case 5: strcpy((*vector)[i].nombre, "VEN01");break;
            default: strcpy((*vector)[i].nombre, "PTL01");break;
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
