all: ESINAIT.exe
	
ejecutar: ESINAIT.exe
	esinait.exe

ESINAIT.exe: main.c usuario.c configuracion.c partida.c tienda.c mapa.c tormenta.c usuario.h configuracion.h partida.h tienda.h mapa.h tormenta.h
	cls
	gcc -c main.c usuario.c configuracion.c partida.c Mochila.c tienda.c mapa.c tormenta.c
	gcc -o esinait main.o usuario.o configuracion.o partida.o Mochila.o tienda.o mapa.o tormenta.o usuario.h configuracion.h partida.h Mochila.h tienda.h mapa.h tormenta.h

clean: main.o usuario.o configuracion.o partida.o Mochila.o esinait.exe tienda.o
	del main.o usuario.o configuracion.o partida.o Mochila.o esinait.exe tienda.o mapa.o