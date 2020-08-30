/*
 * teclado4x4.c
 *
 * Created: 08/04/2016 12:45:41 a.m.
 *  Author: Ale
 */ 
#define F_CPU 1000000L
#include "teclado4x4.h"
#include "lcd_4Bits_I2C.h"
#include <util/delay.h>


/* inicializa los puertos */
void teclado_init_puertos(void){
	TECLADO_PUERTO_DDRX=0xf0; // cuatro bits mas significativos como salidas(filas) y los demas como entradas(columnas)	
}


/*
	Funcion que escanea el teclado, si se presiona alguna tecla devuelve la posicion de la
	tecla presionada, la numeracion va desde 1 hasta 16, por ejemlo fila1-columna1 es la posicion 1,
	fila3-columna2 es la posicion 10. Si no se presiona alguna tecla devuelve 0
*/
int teclado_scan(void){
	// las salidas(filas) se ponen en alto y las entradas(columnas) se activa la resistencia pull-up(nivel alto)
	TECLADO_PUERTO_PORTX=0b11111111; 
	unsigned char tecla;
	int fila=1;
	/*  ciclo que va poniendo en bajo cada una de las filas pero solo una a la ves.  */
	do{
		// se pone en bajo el bit numero 8, despues el 7, despues el 6 y por ultimo el 5
		TECLADO_PUERTO_PORTX=(		0b00001111 | (   ~( 1<<(8-fila) )	)		);
		_delay_ms(5);
		// El valor por default de las columnas es todas en alto. Se leen las columnas y si el valor por
		// defecto es diferente quiere decir que se presiono alguna tecla. Se identifica la posicion de 
		// la tecla presionada y se devuelve el valor saliendo de la funcion.
		tecla=TECLADO_PUERTO_PINX;
		tecla=( 0b00001111&tecla );
		if( !(tecla==0x0f) ){ // si es diferente quiere decir que una tecla se presiono
				int posicion;
				switch(tecla){
					// 1 columna
				case 0b0111: 
				posicion=( 1+( (fila-1)*4 ) );
				return posicion;
				
				break;
					// 2 columna
				case 0b1011: 
				posicion=( 2+( (fila-1)*4 ) );	
				return posicion;
				break;
					// 3 columna
				case 0b1101:
				posicion=( 3+( (fila-1)*4 ) );
				return posicion;
				break;
					// 4 columna
				case 0b1110:
				posicion=( 4+( (fila-1)*4 ) );
				return posicion;
				break;								
				default:lcd_write_string("error");
							 
				} // fin switch 
				 
		}//fin if exterior
	 fila++;
	}while(fila<5); // fin do while exterior
	
	return 0;	// si no se presiono tecla se devuelve 0		 
						
} /// fin funcion

/*
	funcion que devuelve un caracter ascii correspondiente a la posicion del teclado que toma
	como paeametro. En la matriz teclado sustituir los carecteres del teclado, estos caracteres
	con los que devuelve la funcion a partir del valor del parametreo de entrada.
	La enumeracion va desde 1 hasta 16, por ejemplo para la posicion uno corresponde el caracter '1'
	y para la 16 el caracter 'D'
	*/
unsigned char teclado_get_key(int posicion){
	if(posicion==0)
	{
		return 0;
	}
	unsigned char teclado[4][4]={		{'1', '2', '3', 'A'},
										{'4', '5', '6', 'B'},
										{'7' ,'8' ,'9' ,'C'},
									    {'*', '0', '#', 'D'}	};
											
	int fila,columna;
	posicion=posicion-1;
	fila=(int)posicion/4;
	columna=(int)posicion%4;
	unsigned char tecla=teclado[fila][columna];
				
	return tecla;
}











