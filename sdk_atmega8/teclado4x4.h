/*
 * teclado4x4.h
 *
 * Created: 07/04/2016 11:53:00 p.m.
 *  Author: Ale
 */ 

/*
	libreria que lee el teclado matricial de 4x4
	
	1.- El teclado se conecta a un puerto de 8 bits en donde los 4 bits mas significativos son asignados
		a las filas del teclado. Son configurados como salida
		
	2.- Los 4 bits menos significativos seran conectados a las columnas del teclado y seran configurados
		como entradas. activando las resistencias PULL-UP
		
*/

#ifndef TECLADO4X4_H_
#define TECLADO4X4_H_
#include <avr/io.h>

#define TECLADO_PUERTO_PORTX	PORTD
#define TECLADO_PUERTO_DDRX		DDRD
#define TECLADO_PUERTO_PINX		PIND
#define RETARDO	50 // tiempo que espera despues de leer una tecla en mili segundos

/* inicializa los puertos */
void teclado_init_puertos(void);


/*  
	Funcion que retorna la posicion de la tecla presionada, devuelve 0 si no se presiona tecla
*/
int teclado_scan(void);


/*
	Funcion que devuelve el caracter correspondiente a la tecla presionada.
	parametros: int posicion-> posicion de la tecla presionada[1-16]
	retorno: caracter de la tecla presionada
*/
unsigned char teclado_get_key(int posicion);



#endif /* TECLADO4X4_H_ */