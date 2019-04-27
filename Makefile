all: ESINAIT.exe
	
ejecutar: ESINAIT.exe
	esinait.exe

ESINAIT.exe: main.c usuario.c configuracion.c partida.c tienda.c usuario.h configuracion.h partida.h tienda.h
	cls
	del ESINAIT.exe main.o usuario.o configuracion.o partida.o
	gcc -c main.c usuario.c configuracion.c partida.c tienda.c Mochila.c 
	gcc -o esinait main.o usuario.o configuracion.o partida.o Mochila.o tienda.o usuario.h configuracion.h partida.h Mochila.h tienda.h

clean: main.o usuario.o configuracion.o partida.o Mochila.o esinait.exe tienda.o
	del main.o usuario.o configuracion.o partida.o Mochila.o esinait.exe tienda.o