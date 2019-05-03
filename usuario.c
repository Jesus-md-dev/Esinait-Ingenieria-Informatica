#include "usuario.h"

void m_amigos(amigo **a,char *nick,usuario *u);
int confirmar_usuario(usuario *u,char *user);
void crear_usuario(usuario **u,configuracion c);
int comparar_amigo(char *nick,char *nickamig,amigo *a);
void aniadir_amigo(usuario *u,amigo **a,char *nick);
void borrar_amigo(usuario *u,amigo **a,char *nick);

//cabecera: void cargar_usuarios(usuario **u)
//precondicion: recibe por referencia el vector de estructura usuario
//postcondicion: devuelve el vector inicializado
void cargar_usuarios(usuario **u)
{
	char cadena[100];
	char *ptr;
	char *delim="/";
	FILE *f;
	nusuarios=0;
	f=fopen("usuarios.txt","r");
	if(f==NULL)
	{
		printf("No se ha podido abrir el fichero usuarios.txt\n");
		system("pause");
	}
	else
	{
		while(fgets(cadena,100,f)!=NULL)
		{
			fixstring(cadena);
			fflush(stdin);
			*u=(usuario* )realloc((*u),(nusuarios+1)*sizeof(usuario));
			nusuarios++;
			ptr=strtok(cadena,delim);
			strcpy((*u)[nusuarios-1].nick,ptr);
			ptr=strtok(NULL,delim);
			strcpy((*u)[nusuarios-1].nombre,ptr);
			ptr=strtok(NULL,delim);
			(*u)[nusuarios-1].nivel=atoi(ptr);
			ptr=strtok(NULL,delim);
			(*u)[nusuarios-1].vida=atoi(ptr);
			ptr=strtok(NULL,delim);
			(*u)[nusuarios-1].escudo=atoi(ptr);
			ptr=strtok(NULL,delim);
			strcpy((*u)[nusuarios-1].estado,ptr);
			ptr=strtok(NULL,delim);
			(*u)[nusuarios-1].dinero=atoi(ptr);
			ptr=strtok(NULL,delim);
			(*u)[nusuarios-1].pjugadas=atoi(ptr);
			ptr=strtok(NULL,delim);
			(*u)[nusuarios-1].pganadas=atoi(ptr);
			ptr=strtok(NULL,delim);
			strcpy((*u)[nusuarios-1].perfil,ptr);
			ptr=strtok(NULL,delim);
			strcpy((*u)[nusuarios-1].contrasenia,ptr);
		}
	}
	fclose(f);
}

//cabecera: void guardar_usuarios(usuario *u)
//precondicion: recibe el vector de estructura usuario
//postcondicion: guarda en un fichero la estructura
void guardar_usuarios(usuario *u)
{
	FILE *f;
	int i;
	f=fopen("usuarios.txt","w");
	for(i=0;i<nusuarios;i++)
	{
		fprintf(f,"%s/%s/%i/%i/%i/%s/",u[i].nick,u[i].nombre,u[i].nivel,u[i].vida,u[i].escudo,u[i].estado);
		fprintf(f, "%i/%i/%i/%s/%s\n",u[i].dinero,u[i].pjugadas,u[i].pganadas,u[i].perfil,u[i].contrasenia);
	}
	fclose(f);
}

//cabecera: void cargar_amigos(amigo **a)
//precondicion: recibe por referencia el vector de estructura amigo
//postcondicion: devuelve el vector inicializado
void cargar_amigos(amigo **a)
{
	char cadena[100];
	char *ptr;
	char *delim="/";
	FILE *f;
	namigos=0;
	f=fopen("amigos.txt","r");
	if(f==NULL)
	{
		printf("No se ha podido abrir el fichero amigos.txt\n");
		system("pause");
	}
	else
	{
		while(fgets(cadena,100,f)!=NULL)
		{
			fixstring(cadena);
			fflush(stdin);
			(*a)=(amigo*)realloc((*a),(namigos+1)*sizeof(amigo));
			ptr=strtok(cadena,delim);
			strcpy((*a)[namigos].nick_user,ptr);
			ptr=strtok(NULL,delim);
			strcpy((*a)[namigos].nick_amig,ptr);
			namigos++;
		}
	}
	fclose(f);
}

//cabecera: guardar_amigos(amigo *a)
//precondicion: recibe el vector de estructura amigos
//postcondicion: guarda en un fichero la estructura
void guardar_amigos(amigo *a)
{
	FILE *f;
	f=fopen("amigos.txt","w");
	int i;
	for(i=0;i<namigos;i++)
	{
		fprintf(f,"%s/%s\n",a[i].nick_user,a[i].nick_amig);
	}
	fclose(f);
}

//cabecera: int iniciar_sesion(usuario **u,configuracion c)
//precondicion: recibe el vector de estructura por referencia usuario y la estructura configuracion
//postcondicion: devuelve el indice del usuario
int iniciar_sesion(usuario **u,configuracion c)
{
	char user[50];
	char pass[6];
	int i,res,iuser;
	char op;
	printf(" Introduce usuario: ");
	fflush(stdin);
	fgets(user,50,stdin);
	fixstring(user);
	fflush(stdin);
	i=confirmar_usuario(*u,user);
	if(i!=-1)
	{
		do
		{
			printf("\n Introduce contrasenia: ");
			fgets(pass,50,stdin);
			fixstring(pass);
			fflush(stdin);
			res=strcmp(pass,(*u)[i].contrasenia);
			system("cls");
			if(res!=0)
			{
				printf(" Contrasenia incorrecta\n Volver a intentar?(s/n): ");
				scanf("%c",&op);
				fflush(stdin);
			}
		}while(op != 'n' && res != 0);
		if(op == 'n') i = -1;
		if(res == 0 && strcmp((*u)[i].estado,"OFF")==0)
		{
			strcpy((*u)[i].estado,"ON");
		}
	}
	else
	{
		printf(" Crear Nuevo Usuario?(s/n): \n");
		scanf("%c",&op);
		fflush(stdin);
		if(op=='s')
		{
			crear_usuario(&(*u),c);
		}
		i=-1;
	}
	return i;
}

//cabecera: int confirmar_usuario(usuario *u,char *usuario)
//precondicion: recibe el vector de estructura usuario y una cadena con el nick
//postcondicion: devuelve el indice si existe y -1 si no
int confirmar_usuario(usuario *u,char *usuario)
{
	int i;
	for(i=0;i<nusuarios;i++)
	{
		if(strcmp(u[i].nick,usuario)==0)
		{
			return i;
		}
	}
	printf(" Usuario no encontrado\n");
	return -1;
}

//cabecera: void crear_usuario(usuario **u,configuracion c)
//precondicion: recibe el vector de estructura usuario y la estructura configuracion
//postcondicion: añade e inicializa una nueva estructura usuario
void crear_usuario(usuario **u,configuracion c)
{
	char cadena[60];
	int i,op=0;
	printf(" |Crear Usuario|\n");
	printf(" Nick: ");
	fgets(cadena,60,stdin);
	fixstring(cadena);
	fflush(stdin);
	for(i=0;i<nusuarios;i++)
	{
		if(strcmp(cadena,(*u)[i].nick)==0) op=-1;
	}
	if(op==0){
		*u=(usuario* )realloc((*u),(nusuarios+1)*sizeof(usuario));
		nusuarios++;
		strcpy((*u)[nusuarios-1].nick,cadena);
		printf(" Nombre Completo: ");
		fgets(cadena,60,stdin);
		fixstring(cadena);
		fflush(stdin);
		strcpy((*u)[nusuarios-1].nombre,cadena);

		(*u)[nusuarios-1].nivel=1;
		(*u)[nusuarios-1].vida=100;
		(*u)[nusuarios-1].escudo=0;
		strcpy((*u)[nusuarios-1].estado,"OFF");
		(*u)[nusuarios-1].dinero=c.dinero_defecto;
		(*u)[nusuarios-1].pjugadas=0;
		(*u)[nusuarios-1].pganadas=0;

		strcpy((*u)[nusuarios-1].perfil,"JGD");

		printf(" contrasena: ");
		fgets(cadena,60,stdin);
		fixstring(cadena);
		fflush(stdin);
		strcpy((*u)[nusuarios-1].contrasenia,cadena);
	}
	else
	{
		printf(" Nick ya utilizado\n");
		system("pause");
	}
}

//cabecera: void ver_perfil(usuario *u,int i)
//precondicion: recibe el vector de estructuras usuario y un indice
//postcondicion: muestra los datos del usuario del indice
void ver_perfil(usuario *u,int i)
{
	system("cls");
	printf(" |%s|\n",u[i].nick);
	printf(" Nombre: %s\n",u[i].nombre);
	printf(" Nivel: %d\n",u[i].nivel);
	printf(" Dinero: %d\n",u[i].dinero);
	printf(" Partidas Jugadas: %d\n",u[i].pjugadas);
	printf(" Partidas Ganadas: %d\n",u[i].pganadas);
	system("pause");
}

//cabecera: void lista_amigos(amigo *a,char *nick)
//precondicion: recibe el vector de estructuras amigo y una cadena con el nick del usuario
//postcondicion: muestra tu lista de amigos

void lista_amigos(amigo *a,char *nick)
{
	system("cls");
	int i;
	printf(" ||LISTA DE AMIGOS||\n");
	for (i=0;i<namigos;i++)
	{
		if(strcmp(a[i].nick_user,nick)==0)
		{
			printf(" -%s\n",a[i].nick_amig);
		}
	}
	printf("\n");
}

//cabecera: void m_amigos(amigo **a,char *nick,usuario *u)
//precondicion: recibe el vector de estructuras amigo, una cadena nick y el vector de estructuras de usuario
//postcondicion: muestra el menu de amigos
void m_amigos(amigo **a,char *nick,usuario *u)
{
	int op;
	do
	{
		do
		{
			lista_amigos((*a),nick);
			printf(" 1.Aniadir amigo\n");
			printf(" 2.Borrar amigo\n");
			printf(" 0.Salir\n");
			printf("\tOpcion: ");
			scanf("%d",&op);
		}while(op<0&&op>2);
		switch(op)
		{
			case 1: aniadir_amigo(u,&(*a),nick);break;
			case 2: borrar_amigo(u,&(*a),nick);break;
		}
	}while(op!=0);
}

//cabecera: void aniadir_amigo(usuario *u,amigo **a,char *nick)
//precondicion: recibe los vectores de estructuras usuario, amigo y la cadena con el nick del usuario 
//postcondicion: aniade una estructura amigo asociada al nick del usuario
void aniadir_amigo(usuario *u,amigo **a,char *nick)
{
	int i;
	char cadena[50];
	char r;
	printf(" Introduce nick amigo: ");
	scanf("%s",&cadena);
	fflush(stdin);
	i=confirmar_usuario(u,cadena);
	if(i!=-1)
	{
		if(comparar_amigo(nick,u[i].nick,(*a))==-1)
		{
			printf(" Nick: %s\n",u[i].nick);
			printf(" Nombre: %s\n",u[i].nombre);
			printf("\n\tConfirmar (s/n): ");
			scanf("%c",&r);
			fflush(stdin);
			if(r=='s')
			{
				(*a)=(amigo*)realloc((*a),(namigos+1)*sizeof(amigo));
				strcpy((*a)[namigos].nick_user,nick);
				strcpy((*a)[namigos].nick_amig,u[i].nick);
				namigos++;
			}
		}
		else
		{
			printf(" Amigo ya agregado\n");
			system("pause");
		}
	}
}

//cabecera: int comparar_amigo(char *nick,char *nickamig,amigo *a)
//precondicion: recibe el nick del usuario, el nick del amigo y el vector de estructuras amigo
//postcondicion: devuelve 0 si esta agregado o -1 si no
int comparar_amigo(char *nick,char *nickamig,amigo *a)
{
	int i;
	for(i=0;i<namigos;i++)
	{
		if((strcmp(nick,a[i].nick_user))==0)
		{
			if((strcmp(nickamig,a[i].nick_amig))==0)
			{
				return i;
			}
		}
	}
	return -1;
}

//cabecera: void borrar_amigo(usuario *u,amigo **a,char *nick)
//precondicion: recibe los vectores de estructuras usuario y por referencia amigo y la cadena nick
//postcondicion: borra una estructura de amigo
void borrar_amigo(usuario *u,amigo **a,char *nick)
{
	int i,j;
	char cadena[50];
	char r;
	printf(" Introduce nick amigo: ");
	scanf("%s",&cadena);
	fflush(stdin);
	i=confirmar_usuario(u,cadena);
	if(i!=-1)
	{
		j=comparar_amigo(nick,u[i].nick,(*a));
		if(j!=-1);
		{
			printf(" Nick: %s\n",u[i].nick);
			printf(" Nombre: %s\n",u[i].nombre);
			printf("\n\tConfirmar (s/n): ");
			scanf("%c",&r);
			fflush(stdin);
			if(r=='s')
			{
				namigos--;
				strcpy((*a)[j].nick_user,(*a)[namigos].nick_user);
				strcpy((*a)[j].nick_amig,(*a)[namigos].nick_amig);
				(*a)=(amigo*)realloc((*a),(namigos)*sizeof(amigo));
			}
		}
	}
}

//cabecera: void m_admin (usuario **u)
//precondicion: recibe por referencia el vector de estructura usuario
//postcondicion: ensenia el menu de promover/quitar admin
void m_admin (usuario **u)
{
	int op,i;
	char cadena[60];
	char r1,r2;
	do
	{
		do
		{
			lista_usuarios((*u));
			printf(" 1.Promover a Admin\n");
			printf(" 2.Quitar Admin\n");
			printf(" 0.Salir\n");
			printf("\t\nOpcion: ");
			scanf("%d",&op);
		}while(op<0&&op>2);
		if(op!=0){	
			do
			{
				lista_usuarios((*u));
				printf("\n Introduce nick: ");
				fflush(stdin);
				fgets(cadena,60,stdin);
				fixstring(cadena);
				fflush(stdin);
				i=confirmar_usuario((*u),cadena);
				if(i!=-1)
				{
					printf(" Nick : %s\n Nombre: %s\n Confirmar (s/n): ",(*u)[i].nick,(*u)[i].nombre);
					scanf("%c",&r1);
					fflush(stdin);
					if(r1=='s')
					{
						if(op==1)
						{
							strcpy((*u)[i].perfil,"ADM");
						}
						else if(op==2)
						{
							strcpy((*u)[i].perfil,"JGD");
						}
						
					}
				}
				printf(" Continuar (s/n): ");
				scanf("%c",&r2);
				fflush(stdin);
			}while(r2!='n');
		}
	}while(op!=0);
}

//cabecera: int indice_usuario(usuario *u,char id[100])
//precondicion: recibe el vector de estructuras usuario y la cadena id con el nick del usuario
//postcondicion: devuelve el indice del usuario
int indice_usuario(usuario *u,char id[100])
{
	int i;
	for(i=0;i<nusuarios;i++)
	{
		if(strcmp(u[i].nick,id)==0) return i;
	}
}

//cabecera: int njugadores_EE (usuario *u)
//precondicion: recibe el vector de estructuras usuario
//postcondicion: devuelve el numero de usuarios en espera (EE)
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

//cabecera: int njugadores_EE (usuario *u)
//precondicion: recibe el vector de estructuras usuario
//postcondicion: devuelve el numero de usuarios en juego (EJ)
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

//cabecera: void inicializar_vida_escudo (usuario **u)
//precondicion: recibe el vector de estructuras por referencia usuario
//postcondicion: inicializa la vida a 100 y el escudo a 0 de todos los usuarios
void inicializar_vida_escudo (usuario **u)
{
	int i;
	for(i=0;i<nusuarios;i++)
	{
		(*u)[i].vida=100;
		(*u)[i].escudo=0;
	}
}

//cabecera: void lista_usuarios (usuario *u)
//precondicion: recibe el vector de estructuras por valor usuario
//postcondicion: muestra la lista de usuarios del sistema
void lista_usuarios (usuario *u)
{
	int i;
	system("cls");
	printf("\t| LISTA USUARIOS |\n");
	printf(" | NICK | NOMBRE | NIVEL | VIDA | ESCUDO | ESTADO | DINERO | P.JUG | P.GAN | PERFIL | CONTRASENIA |\n");
	for(i = 0;i < nusuarios;i++){
		printf(" %s - %s - %i - %i - %i - |%s| -",u[i].nick,u[i].nombre,u[i].nivel,u[i].vida,u[i].escudo,u[i].estado);
		printf(" %i - %i - %i - %s - %s\n\n",u[i].dinero,u[i].pjugadas,u[i].pganadas,u[i].perfil,u[i].contrasenia);
	}
}