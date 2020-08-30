/*
 * LCD_4Bits_I2C.c
 *
 * Created: 29/05/2016 1:55:58
 *  Author: Ale
 */ 
#define F_CPU 1000000L
#include "lcd_4Bits_I2C.h"
#include "I2C.h"
#include <util/delay.h>


/*	secuencia de comandos especificados por el
	datashet hitachi HD470 figura 24 interface
	de 4 bits
*/
void lcd_init(void){
	
	I2C_init(I2C_PRESCALER_1,I2C_INTERRUPCIONES_OFF,0x05);
	I2C_START();
	I2C_WRITE(LCD_DIRECCION); // direccion del lcd
	
	I2C_WRITE(0xff);
	I2C_WRITE(0xff);
	_delay_ms(20);
	
	I2C_WRITE(D5|D4|ENABLE_LCD);
	I2C_WRITE(D5|D4);
	_delay_ms(10);
	
	I2C_WRITE(D5|D4|ENABLE_LCD);
	I2C_WRITE(D5|D4);
	_delay_ms(1);
	
	I2C_WRITE(D5|D4|ENABLE_LCD);
	I2C_WRITE(D5|D4);
	_delay_ms(1);	
	
	I2C_WRITE(D5|ENABLE_LCD);
	I2C_WRITE(D5);
	_delay_ms(1);
	
	I2C_STOP();		




}

void lcd_start(void){
	lcd_init();
	funtion_set_4bits_2lines_5x10puntos();		// Function Set: Modo 4 bits, 2 líneas, resolución 5×10
	lcd_display_on(0);      // Display control: LCD encendido, cursor encendido, parpadeo.
	lcd_cmd(0x06);      // Entry mode: Increment.
	lcd_cmd(0x80);      // Apunta a la dirección de la DDRAM.
}



/*

							CODIGO
							RS	|	RW	|	DB7	|	DB6	|	DB5	|	DB4	|	DB3	|	DB2	|	DB1	|	DB0
							0		0		0		0		0		0		0		0		0		1
							limpiar lcd
							0x01
							

*/

void lcd_clear(void){
	lcd_cmd(0x01);
}


/*

							CODIGO
							RS	|	RW	|	DB7	|	DB6	|	DB5	|	DB4	|	DB3	|	DB2	|	DB1	|	DB0
							0		0		0		0		0		0		0		0		1		x
							retornar home
							0x02
							

*/
void lcd_return_home(void){
	lcd_cmd(0x02);
}
	
	
/*

Establece la direccion de movimiento del cursor y especifica el corrimiento del display.
Todo cuando existe lectura y escritura de la memoria.

							CODIGO
							RS	|	RW	|	DB7	|	DB6	|	DB5	|	DB4	|	DB3	|	DB2	|	DB1	|	DB0
							0		0		0		0		0		0		0		1		I/D		S
							
							Donde:
							I/D=1 incremento
							I/D=0 decremento
							S=1 acompaña corrimiento del display
							
							incremento y acompaño:
							0x07	
							

*/	
void lcd_entry_mode_set(){
	lcd_cmd(0x07);
}


/*
							CODIGO
	RS	|	RW	|	DB7	|	DB6	|	DB5	|	DB4	|	DB3	|	DB2	|	DB1	|	DB0
	0		0		0		0		0		0		1		D		C		B
	
	DONDE:	D=1 enciende display
			D=0 apaga display
			
			C=1 visualiza cursor
			C=0	oculta cursor
			
display apagado
0x08
display enecendido cursor visualizado y parpadeo(blink) activado
0x0f
diplay encendido cursor apagado y parpadeo desctivado
0x0C
	
*/


void lcd_display_on(unsigned char cursor){
	
	if(	cursor==1)
	{
		lcd_cmd(0b00001111);
	}else{
		lcd_cmd(0b00001100);
		}

		
}

void lcd_display_off(void){
	lcd_cmd(0b00001000);
	
}



/*

							CODIGO
							RS	|	RW	|	DB7	|	DB6	|	DB5	|	DB4	|	DB3	|	DB2	|	DB1	|	DB0
							0		0		0		0		1		DL		N		F		x		x
							Donde:
							DL=1 8bits data
							DL=0 4 bits data
							N=1 2 lineas
							N=0 1 linea
							F=1 caracter de 5x10 puntos
							F=0 caracter de 5x8 puntos
							
							4 bits, 2 lineas y caracteres de 5x10 puntos
							0x2C
							4 bits, 1 lineas y caracteres de 5x10 puntos
							0x24

*/
void funtion_set_4bits_2lines_5x10puntos(){
	lcd_cmd(0b00101100);
}

void funtion_set_4bits_1lines_5x10puntos(){
	lcd_cmd(0b00100100);
}


/*
Escribe en la memoria ram un caracter
*/
void lcd_data(unsigned char dat)
{
	I2C_START();
	I2C_WRITE(LCD_DIRECCION);
	I2C_WRITE(	(  (dat & 0xF0) | ENABLE_LCD | RS | LUZ_FONDO )	);
	I2C_WRITE(	 (  (dat & 0xF0)  | RS | LUZ_FONDO )	);
	I2C_WRITE((	(  ( dat << 4   ) & 0xF0	) | ENABLE_LCD | RS | LUZ_FONDO	  ));
	I2C_WRITE( (	(	( dat << 4	) & 0xF0) | RS |LUZ_FONDO		));
	I2C_STOP();
	
	_delay_ms(2);
}


/*
Esbribe en la memoria ram una cadena de texto
*/
void lcd_write_string(char *a)
{
	unsigned int i;
	for(i=0;a[i]!=0;i++)
	lcd_data(a[i]);
}


/* desplaza la pantalla a la izquierda en una posicion */
void lcd_desplazar_pantalla_izquierda(){
	lcd_cmd(0b00011100);
}
/* desplaza la pantalla a la derecha en una posicion */
void lcd_desplazar_pantalla_derecha(){
	lcd_cmd(0b00011000);
}

/********************************************************
*	Posiciona el cursor en Columna y Renglón. Apunta a la direccion de la ram especificada
*	Entrada: Columna y Renglón (1,1)
*	Salida: Ninguna
*********************************************************/
char FirstColumn [2] = {0 , 64};
void lcd_set_posicion_cursor(uint8_t x, uint8_t y)
{
	lcd_cmd(0x80 + FirstColumn[y-1]+(x-1));
}




void lcd_cmd (char cmd){
	
	I2C_START();
	I2C_WRITE(LCD_DIRECCION);
	I2C_WRITE(	(cmd & 0xF0)|ENABLE_LCD | LUZ_FONDO	);
	I2C_WRITE(	(cmd & 0xF0) | LUZ_FONDO );
	I2C_WRITE((  (cmd << 4) & 0xF0  ) | ENABLE_LCD | LUZ_FONDO);
	I2C_WRITE(((cmd << 4) & 0xF0)|LUZ_FONDO);
	I2C_STOP();
	_delay_ms(2);

}




