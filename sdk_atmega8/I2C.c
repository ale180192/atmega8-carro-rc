/*
 * I2C.c
 *
 * Created: 04/05/2016 08:27:29 p. m.
 *  Author: JLB
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "I2C.h"


 uint8_t read_i2c()
 {
	 TWCR = (1<<TWINT)|(1<<TWEN); //Lectura sin reconocimiento (TWEA=0)
	 while((TWCR & (1<<TWINT))==0); //Espera hasta que TWINT=0 (TWI termina su trabajo)
	 return TWDR; //Regresa el valor leído
 }


void I2C_init(enum I2C_PRESCALER TWPS_value, enum I2C_INTERRUPCIONES int_value, uint8_t TWBR_value){
	TWSR=TWPS_value;
	if(int_value)
	TWCR|=(1<<TWIE);
	TWBR=TWBR_value;
	TWCR = (1<<TWEN); //Activa la interfaz TWI	
}



void I2C_START(void){
	TWCR=(		(1<<TWINT)|(1<<TWSTA)|(1<<TWEN)	);
	while(!(TWCR & (1<<TWINT)))
	;
}

void I2C_STOP(void){
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	_delay_ms(1);
}

void I2C_WRITE(uint8_t x){
	TWDR = x;
	TWCR = (1<<TWINT) | (1<<TWEN)|(1<<TWEA);
	while(		!(TWCR & (1<<TWINT))		)
	;
}

	


 

 
