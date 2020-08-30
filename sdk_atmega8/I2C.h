/*
 * I2C.h
 *
 * Created: 04/05/2016 08:27:49 p. m.
 *  Author: Josè Luis Barbosa
 */ 


#ifndef I2C_H_
#define I2C_H_

/*
// #define I2C_START	 TWCR=(		(1<<TWINT)|(1<<TWSTA)|(TWEN)	);\
// 					while(!(TWCR & (1<<TWINT)))
// #define I2C_STOP	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);\
// 					_delay_ms(1)
// // envia el byte x
// #define I2C_WRITE(x)	TWDR = x;\
// 						TWCR = (1<<TWINT) | (1<<TWEN)|(1<<TWEA);\
// 						while(		!(TWCR & (1<<TWINT))		)
*/


enum I2C_PRESCALER{I2C_PRESCALER_1=0, I2C_PRESCALER_4, I2C_PRESCALER_16, I2C_PRESCALER_64 };
enum I2C_INTERRUPCIONES{I2C_INTERRUPCIONES_OFF=0,I2C_INTERRUPCIONES_ON};	


uint8_t read_i2c();

/*
	Inicializa el modulo I2C
	
	parametros:
	enum I2C_PRESCALER -> Define la prescala para la velocidad de trasmision de bit. se asigna a los bits TWPS del registro TWCR
	enum I2C_INTERRUPCIONES -> Define si se activan las interrupciones. se asigna al bit TWI del registro TWCR
	TWBR_value -> entero de ocho bits que se asignara al registro TWBR para establecer la velocidad de bit
	
	SCL_FRECUENCIA=	CPU_CLOCK_FRECUENCIA / (	16+2(TWBR)*4^TWPS	)		
	
	return:
	void

*/
void I2C_init(enum I2C_PRESCALER a,enum I2C_INTERRUPCIONES b, uint8_t TWBR_value);

/*
	envia señal de start
*/
void I2C_START(void);

/*
	envia señal de stop
*/
void I2C_STOP(void);

/*
	Envia trama de datos y espera hasta que responda el dispositivo esclavo
	
	parametros:
	uint8_t dato -> dato a enviar. debe ser de 8 bits
*/
void I2C_WRITE(uint8_t dato);



#endif /* I2C_H_ */