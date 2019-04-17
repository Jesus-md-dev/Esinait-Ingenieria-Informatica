all: ESINAIT.exe
	
ejecutar: ESINAIT.exe
	esinait.exe

ESINAIT.exe: main.c usuario.c configuracion.c partida.c usuario.h configuracion.h partida.h
	cls
	del ESINAIT.exe main.o usuario.o configuracion.o partida.o
	gcc -c main.c usuario.c configuracion.c partida.c Mochila.c
	gcc -o esinait main.o usuario.o configuracion.o partida.o Mochila.o usuario.h configuracion.h partida.h Mochila.h