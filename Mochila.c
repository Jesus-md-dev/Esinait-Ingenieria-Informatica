#include"Mochila.h"

//Cabecera: void cargarficheroMochila (mochila **eMochila)
//Precondicion: informacion escrita en documento de texto
//Poscondicion: carga del fichero mochila a cada estructura mochila

void cargarficheroMochila (mochila **eMochila)
{
    FILE *f;

    char linea [100];
    char *token;
    nmochilas=0;

    f=fopen("Mochilas.txt","r+");
    if (f==NULL)
    {
        printf ("El fichero Mochila.txt no ha podido abrirse.\n");
    }
    else
    {
        while (fgets (linea,100,f))
        {
            if(strcmp(linea,"\0"))
            {
                *eMochila=(mochila*)realloc(*eMochila,(nmochilas+1)*sizeof(mochila)); //a�ade una estructura de tipo mochila

                token=strtok(linea,"/");
                strcpy((*eMochila)[nmochilas].idusu,token);

                token=strtok(NULL,"/");
                strcpy((*eMochila)[nmochilas].idobj,token);

                token=strtok(NULL,"/");
                (*eMochila)[nmochilas].unidades=atoi(token);

				nmochilas++; //variable que va aumentando en esta funcion para avanzar en el vector
            }
        }
    }

    fclose(f);

}

//Cabecera: void guardarficheroMochila (mochila *eMochila)
//Precondicion:
//Poscondicion: guardar las estructuras mochila en el fichero mochila
void guardarficheroMochila (mochila *eMochila)
{
    int i;
    i=0;

    FILE *fich;

    fich=fopen("Mochilas.txt","w+");

    if (fich==NULL)
    {
        printf ("El fichero Mochila.txt no ha podido ser modificado.\n");
    } else
    {
            while (i<nmochilas)     // recorremos el vector de la estructura
            {
                fprintf (fich,"%s/%s/%d\n",eMochila[i].idusu,eMochila[i].idobj,eMochila[i].unidades);     // impr en el fichero linea por linea
                i++;
            }

            printf ("Se han guardado los datos correctamente.\n");
        }

        fclose(fich);

    }

//Cabecera: void leerMochila (mochila *eMochila, int j, usuario *u)
//Precondicion: estructuras inicializadas
//Poscondicion: imprime los objetos de un usuario
void leerMochila (mochila *eMochila, int j, usuario *u) //j es el usuario
{
    int i;
    printf("\n-----------------MOCHILA------------------\n");
    for (i=0;i<nmochilas;i++)
    {
        if (strcmp(u[j].nick,eMochila[i].idusu)==0)
        {
            printf("%s/%s/%d\n",eMochila[i].idusu,eMochila[i].idobj,eMochila[i].unidades);
        }
    }
}

//Cabecera: int  usarMochila (mochila *eMochila, int j, usuario *u)
//Precondicion: que haya algun objeto en la mochila
//Poscondicion: devuelve la posicion del objeto elegido para así en partida saber el daño o beneficio de ese objeto
int  usarMochila (mochila *eMochila, int j, usuario *u) //j es el usuario
{
  int i,cont,posicion;
  char op;
  char op2 [10]; //el objeto que elige el usuario
  cont=0;

  leerMochila(eMochila,j,u);

  while (cont==0)
  {
    printf ("Escribe la ID del objeto que quieres utilizar:\n");

    for (i=0;i<nmochilas;i++)
    {
        if (strcmp(u[j].nick,eMochila[i].idusu)==0)
        {
            printf ("%s\n",eMochila[i].idobj); //Imprime los objetos de un usuario
        }
    }

    fflush(stdin);
    fgets(op2,10,stdin);
    fixstring(op2);

    for (i=0;i<nmochilas;i++)
    {
            if (strcmp(op2,eMochila[i].idobj)==0) //El objeto est� en la mochila
            {
                cont++;
            }
        }
        if (cont==0) //el objeto no esta en la mochila
        {
            printf ("La ID introducida no es correcta. Introduzca otra: \n");
        } else
        { printf ("Esta seguro de que quiere usar este objeto? s/n\n");
        fflush(stdin);
        scanf("%c",&op);
        if (op=='s')
        {
            for (i=0;i<nmochilas;i++)
            {

                    if (strcmp(op2,eMochila[i].idobj)==0) //Para saber la posicion de un objeto en la mochila
                    {
                        printf ("El objeto se ha seleccionado correctamente.\n");
                        posicion=i;
                        cont++;
                    }
                }
            }
        }
    }
    return posicion;
}

//Cabecera: void eliminarobjeto (mochila **eMochila, int i)
//Precondicion: saber la i (posicion) del objeto
//Poscondicion: resta una unidad de objeto o una estructura del objeto despues de ser utilizado

void eliminarobjeto (mochila **eMochila, int i) //i es la posicion del objeto a eliminar
{
    int j;

    if ((*eMochila)[i].unidades==1) //solo hay una unidad de ese objeto
    {
        for (j=i;j<nmochilas-1;j++)
        {
        //Los datos pasan a una posicion anterior
            strcpy((*eMochila)[j].idobj,(*eMochila)[j+1].idobj);
            strcpy((*eMochila)[j].idusu,(*eMochila)[j+1].idusu);
            (*eMochila)[j].unidades=(*eMochila)[j+1].unidades;
        }
        nmochilas--;
    *eMochila=(mochila*)realloc(*eMochila,(nmochilas)*sizeof(mochila)); //se resta una estructura
    } else //hay mas de una unidad de ese objeto
    {
        (*eMochila)[i].unidades=(*eMochila)[i].unidades-1;
    }
}

//Cabecera: void guardar_mochila (mochila **eMochila, char *objeto, int j, usuario *u)
//Precondicion: haber comprado un objeto o haberlo cogido en el mapa
//Poscondicion: añadir o intercambiar el objeto en la mochila de un usuario

void guardar_mochila (mochila **eMochila, char *objeto, int j, usuario *u, configuracion c) //j es una variable que va a decir que usuario es el que inicia sesion
{
    int i,cont,cont1,cont2;
    char op;
    cont=0;
    cont1=0;
    cont2=0;
    char objetoelegido [6]; //objeto de la mochila que se reemplaza

    for (i=0;i<nmochilas;i++)
    {
        if (strcmp((*eMochila)[i].idusu,u[j].nick)==0)
        {
                cont++; //cuenta el numero de objetos que tiene el usuario
            }
        }

        if (cont==c.tam_mochila)
        {
        printf ("La mochila esta llena. Desea reemplazar el objeto por otro? s/n\n"); //porque el maximo de objetos diferetes es 7
        leerMochila(*eMochila,j,u);
        fflush(stdin);
        scanf("%c",&op);

        if (op=='s')
        {
            while (cont1==0)
            {
                printf ("Introduce el objeto que desea reemplazar: \n");
                fflush(stdin);
                fgets(objetoelegido,6,stdin);
                fixstring(objetoelegido);

                for (i=0;i<nmochilas && cont1==0;i++)
                {
                if (strcmp((*eMochila)[i].idusu,u[j].nick)==0) //usuario actual
               {
                    for (i=0;i<nmochilas;i++)
                    {
                        if (strcmp((*eMochila)[i].idobj,objetoelegido)==0) //para saber en que posicion esta el objeto que se reemplaza
                        {
                            strcpy((*eMochila)[i].idobj,objeto); //el objeto nuevo reemplaza el que ya estaba
                            (*eMochila)[i].unidades=1;
                            cont1++;
                        }
                    }
                }
                }
                if (cont1==0)
                {
                    printf ("La ID introducida no es correcta. Introduzca otra: \n");
                } else printf ("El objeto se ha reemplazado correctamente.\n");
            }
        }
    } else
    {
        //Esto se realiza si no hay ningun objeto de este tipo y el usuario tiene menos de 7 objetos
        if (cont==0)
        {
            nmochilas++;
            *eMochila=(mochila*)realloc((*eMochila),(nmochilas)*sizeof(mochila));
            strcpy((*eMochila)[nmochilas-1].idusu,u[j].nick); //nmochilas es el siguiente numero del �ltimo del vector estructura, por lo que se a�ade al final
            strcpy((*eMochila)[nmochilas-1].idobj,objeto);
            (*eMochila)[nmochilas-1].unidades=1;

            printf ("El objeto se ha agregado correctamente.\n");


        } else //Menos de 7 y mas de 0, y algun objeto de ese tipo
        {
            for (i=0;i<nmochilas;i++)
            {
                if (strcmp((*eMochila)[i].idusu,u[j].nick)==0) //usuario actual
                {
                    if (strcmp((*eMochila)[i].idobj,objeto)==0) //el objeto nuevo coincide con uno del usuario
                    {
                        (*eMochila)[i].unidades=(*eMochila)[i].unidades+1; //se incrementa una unidad el objeto
                        cont2++;
                    }
                }
            }
            if (cont2==0) //no tiene el objeto nuevo en la mochila
            {
                nmochilas++;
                *eMochila=(mochila*)realloc((*eMochila),(nmochilas)*sizeof(mochila));
                strcpy((*eMochila)[nmochilas-1].idusu,u[j].nick); //nmochilas es el siguiente numero del �ltimo del vector estructura, por lo que se a�ade al final
                strcpy((*eMochila)[nmochilas-1].idobj,objeto);
                (*eMochila)[nmochilas-1].unidades=1;
                printf ("El objeto se ha agregado correctamente.\n");
            } else //tiene el objeto nuevo en la mochila
            {
                printf ("El objeto se ha incrementado correctamente.\n");
            }
        }
    }
}

