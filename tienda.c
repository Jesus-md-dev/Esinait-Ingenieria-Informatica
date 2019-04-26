#include "tienda.h"

void cargar_objetos(objetos **obj){

	char cadena[100];
	char *partes;
	char *delim = "/";
	FILE *f= fopen("objetos.txt","r+");

    *obj =(objetos *) calloc(nobjetos, sizeof(objetos));

	if(f == NULL)
        printf("No se ha podido abrir el fichero objetos.txt\n");

    else{

        while(fgets(cadena,100,f)!=NULL){

            fixstring(cadena);
            fflush(stdin);

            nobjetos++;
            *obj = (objetos*)realloc((*obj),(nobjetos)*sizeof(objetos));

            partes = strtok(cadena,delim);
            strcpy((*obj)[nobjetos-1].item_ID,partes);

            partes = strtok(NULL,delim);
            strcpy((*obj)[nobjetos-1].descripcion,partes);

            partes = strtok(NULL,delim);
            strcpy((*obj)[nobjetos-1].tipo,partes);

            partes = strtok(NULL,delim);
            (*obj)[nobjetos-1].coste = atoi(partes);

            partes = strtok(NULL,delim);
            (*obj)[nobjetos-1].alcance = atoi(partes);

            partes = strtok(NULL,delim);
            (*obj)[nobjetos-1].porcentaje_d_e = atoi(partes);
        }

        printf("Fichero de objetos cargado con exito.\n");

    }

	fclose(f);
    system("pause");
}


//void lista_objetos(objetos)
//precondicion: obj declarado
//postcondicion: muestra la lista de objetos
void lista_objetos(objetos *obj){

    int i;

    system("cls");

    printf("\n| LISTA DE OBJETOS |\n");
    printf("| ID | DESCRIPCION | TIPO | COSTE | ALCANCE | PORCENTAJE DE DA�O/ESCUDO |\n");

    for(i=0; i < nobjetos ;i++){

        printf("Objeto %d:\n%s/%s/%s/%d/%d/%d\n",i+1,obj[i].item_ID,obj[i].descripcion,obj[i].tipo,obj[i].coste,obj[i].alcance,obj[i].porcentaje_d_e);

    }

    system("pause");

}

void comprar_objetos(mochila **moch,objetos *obj,usuario **usua,int iuser,configuracion c){

    char compra[25];
    int a=0,j;

    printf("Objetos disponibles para comprar:\n");
    lista_objetos(obj);
    printf("Introduce el ID del objeto que quiere comprar(su dinero es %d):  ",(*usua)[iuser].dinero);
    fflush(stdin);
    gets(compra);

    for(j=0;j<nobjetos && a == 0;j++){

        if(strcmp(compra,obj[j].item_ID)==0){

            a=1;

            if((*usua)[iuser].dinero >= obj[j].coste){
                guardar_mochila(&(*moch),obj[j].item_ID,iuser,*usua,c);
                printf("Compra realizada con exito.\n");
                (*usua)[iuser].dinero = (*usua)[iuser].dinero - obj[j].coste;
                printf("Ahora su dinero es %d.\n ",(*usua)[iuser].dinero);
            }
            else printf("No tiene suficiente dinero para comprar el objeto");
        }

    }

    if(a!=1)
        printf("No existe ningun objeto con ese ID\n");

}

void registrar_objetos(objetos **obj){

    char nuevo[20];
    int j,a=0;

    printf("Introduzca el ID del objeto que desea registrar: ");
    fflush(stdin);
    gets(nuevo);

    for(j=0;j<nobjetos && a == 0;j++){

        if(strcmp(nuevo,(*obj)[j].item_ID)==0){

            printf("Ya hay un objeto registrado con ese mismo ID.\n");
            a=1;

        }

    }
    if(a!=1){

        nobjetos = nobjetos + 1;
        *obj = (objetos*)realloc((*obj),nobjetos*sizeof(objetos));
        strcpy((*obj)[nobjetos-1].item_ID,nuevo);

        printf("Introduce la descripcion del objeto: ");
        fflush(stdin);
        gets((*obj)[nobjetos-1].descripcion);

        printf("Introduce que tipo de objeto es:  ");
        fflush(stdin);
        gets((*obj)[nobjetos-1].tipo);

        printf("Introduce el coste del objeto:  ");
        scanf("%d",&(*obj)[nobjetos-1].coste);

        printf("Introduce el alcance del objeto:  ");
        scanf("%d",&(*obj)[nobjetos-1].alcance);

        printf("Introduce el porcentaje de da�o si es un arma o de reposicion si es un escudo: ");
        scanf("%d",&(*obj)[nobjetos-1].porcentaje_d_e);

        printf("Objeto registrado.\n");

    }

}

void borrar_objetos(objetos **obj){

    int j,a=0;
    char eliminar[20];

    printf("Introduce el ID del objeto que quieres borrar:  ");
    fflush(stdin);
    gets(eliminar);

    for(j=0;j<nobjetos && a == 0;j++){

        if(strcmp(eliminar,(*obj)[j].item_ID)==0){

            strcpy((*obj)[j].item_ID,(*obj)[nobjetos-1].item_ID);
            strcpy((*obj)[j].descripcion,(*obj)[nobjetos-1].descripcion);
            strcpy((*obj)[j].tipo,(*obj)[nobjetos-1].tipo);
            (*obj)[j].coste = (*obj)[nobjetos-1].coste;
            (*obj)[j].alcance = (*obj)[nobjetos-1].alcance;
            (*obj)[j].porcentaje_d_e = (*obj)[nobjetos-1].porcentaje_d_e;

            printf("Objeto eliminado\n");

            nobjetos--;
            *obj = (objetos*)realloc((*obj),nobjetos*sizeof(objetos));

            a=1;

        }

    }

    if(a!=1)
        printf("No hay ningun objeto con ese ID.\n");

    system("pause");
}

void modificar_objetos(objetos **obj){

    int j,a=0,parametro;
    char modificar[20];

    printf("Introduce el ID del objeto que quieres modificar:   ");
    fflush(stdin);
    gets(modificar);

    for(j=0;j<nobjetos && a==0;j++){

        if(strcmp(modificar,(*obj)[j].item_ID)==0){

            do{

                printf("1-Descripcion\n2-Tipo\n3-Coste\n4-Alcance\n5-Porcentaje Da�o-Escudo\n");
                scanf("%d",&parametro);

            }while(parametro < 1 && parametro > 5);

            switch(parametro){

                case 1:
                printf("Introduzca la nueva descripcion del objeto:   ");
                fflush(stdin);
                gets((*obj)[j].descripcion);
                printf("Descripcion modificada con exito.\n");
                break;

                case 2:
                printf("Introduzca el nuevo tipo del objeto:   ");
                fflush(stdin);
                gets((*obj)[j].tipo);
                printf("Tipo de objeto modificado con exito.\n");
                break;

                case 3:
                printf("Introduzca el nuevo coste del objeto:   ");
                scanf("%d",&(*obj)[j].coste);
                printf("Coste del objeto modificado con exito.\n");
                break;

                case 4:
                printf("Introduzca el nuevo alcance del objeto:   ");
                scanf("%d",&(*obj)[j].alcance);
                printf("Alcance del objeto modificado con exito\n");
                break;

                case 5:
                printf("Introduzca el nuevo porcentaje de da�o o de recuperacion de escudo del objeto:   ");
                scanf("%d",&(*obj)[j].porcentaje_d_e);
                printf("Porcentaje de da�o o de recuperacion de escudo modificado con exito.\n");
                break;

            }

            a=1;

        }

    }

    if(a!=1)
        printf("No se ha encontrado ningun objeto con esa ID");

}

void guardar_objetos(objetos *obj){

    FILE *f;
	int i;

	f=fopen("objetos.txt","w+");

	for(i=0;i<nobjetos;i++){

		fprintf(f,"%s/%s/%s/%d/%d/%d\n",obj[i].item_ID,obj[i].descripcion,obj[i].tipo,obj[i].coste,obj[i].alcance,obj[i].porcentaje_d_e);

	}

	fclose(f);

}
