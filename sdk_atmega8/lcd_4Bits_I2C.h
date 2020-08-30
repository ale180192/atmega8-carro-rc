/*
 * lcd.h
 *
 * Created: 04/04/2016 11:30:32 p.m.
 *  Author: Ale
 */ 


/*

	el orden de las conexiones del LCD es el siguiente, no importa en que puerto se conecte
	
	-------------------------------------------------------------
	|D7	|	D6	|	D5	|	D4	|	D3	|	D2	|	D1	|	D0	|			->Pines del Puerto
	-------------------------------------------------------------
	|LCD7|	LCD6|	LCD5|	LCD4|	GND	|	E	|	RW	|	RS	|			-> Pines del LCD
	
	Donde el peso de cada bit es el siguinte:
		
			BIT		DECIMAL		HEXADECIMAL
			RS		1			0x01
			RW		2			0x02	
			E		4			0x04
		-------------------------------------
			D4		16			0x10
			D5		32			0x20
			D6		64			0x40
			D7		128			0x80
			
	Para activar cada bit del puerto en especifico se nesecitan sumar cada variable y asignarle el
	valor al LCD_PORT. Ejemplo:
	
	si se dese enviar el bit de control siguiente : 
	RS R/W D7   D6   D5 D4
	0   0   0    0   1   1
	
	Su instruccion correspondiente es la siguiente:
	LCD_PORT=0x10+0x20; ó LCD_PORT=D4+D5 ( en el caso de haber definido D4 y D5 -> ' #DEFINE D4	0x10 ' )
	

				
*/



#ifndef LCD_4BITS_I2C_H_
#define LCD_4BITS_I2C_H_

#include <avr/io.h>

/*************************************************
**                Configuraciones               **
**************************************************/
#define		LCD_PORT	PORTB 
#define		LCD_PORT_IO	DDRB


/*	Se definen los pesos de cada bit en hexadecimal	*/

#define		RS				0x01	// Selec Register
#define		RW				0x02	//	Read Write
#define		ENABLE_LCD		0x04	// ENABLE_LCD

#define		D4				0x10	// bits de datos para el display
#define		D5				0x20
#define		D6				0x40
#define		D7				0x80
#define		LCD_DIRECCION	0x7E
#define LUZ_FONDO	0x08


void lcd_data (unsigned char dat);
void lcd_cmd(char cmd);
void lcd_start(void);
void lcd_init(void);
void lcd_write_string(char *a);
void funtion_set_4bits_2lines_5x10puntos();
void funtion_set_4bits_1lines_5x10puntos();


/*
	limpia todas las direcciones de la DDRAM escribiendo espacios en blanco
	y regresando el contador de direcciones al valor 0, regresa el cursor a la 
	primer linea paspadeando
*/
void lcd_clear(void);


/*
	activa el display manteniendo
	Como opciones visualiza el cursor
*/
void lcd_display_on(unsigned char cursor);

/*
	Apaga el display manteniendo en sueño todos los datos y recuperandolos cuando
	se vuelva a activar
*/
void lcd_display_off(void);



/*
	regresa el cursor a la primer linea, elimina los desplazamientos de la pantalla
	No modifica valores de la DDRAM
*/
void lcd_return_home(void);



/*
	desplaza la pantalla en una posicion
*/
void lcd_desplazar_pantalla_izquierda();

/*
	desplaza la pantalla en una posicion
*/
void lcd_desplazar_pantalla_derecha();
/*
	pone el cursor en la posicion indicada. Apartir de ahi
	se escribe o lee de la memoria DDRAM del lcd
*/
void lcd_set_posicion_cursor(uint8_t columna, uint8_t fila);




#endif /* LCD_4BITS_I2C_H_ */