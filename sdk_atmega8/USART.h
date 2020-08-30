#ifndef USART_H_
#define USART_H_

/*
	La comunicacion USART usa dos pines para trasmitir y recibir datos; RX y TX
	para inicializar el modulo usart se debe establecer la velocodad de trasmision, activar los pines RX y TX.
	establecer la configuracion para la trama de datos, es decir, la longitud de los datos en bits, la paridad,
	# de bits de parada etc.
	Tambien se debe establecer el modo sincrono o asincrono
	
	Una vez configurado el usart, para leer y recibir datos se deben leer las banderas correspondientes ya que cada
	que hay una lectura o escritura se activan estas banderas y asi es posible saber cuando existen datos que leer o
	es posible enviar datos
	
	Tambien se pueden usar las interrupciones las cuales se activan al mismo tiempo que las banderas se establecen
	es nesesario leer el registro UDR en el caso de una lectura y escribir en el durante la rutina de interrupcion, 
	esto para que las banderas se eliminen.
*/



#include <avr/io.h>
/*
	ENUMERACIONES PARA MANEJAR LA HABILITACION DE LAS INTERRUPCIONES
*/
enum USART_INT_TX_COMPLETA{USART_INT_TX_COMPLETA_OFF=0, USART_INT_TX_COMPLETA_ON=1};
enum USART_INT_RX_COMPLETA{USART_INT_RX_COMPLETA_OFF=0, USART_INT_RX_COMPLETA_ON=1};
enum USART_INT_UDR_VACIO{USART_INT_UDR_VACIO_OFF=0, USART_INT_UDR_VACIO_ON=1};
	

/*
	Inicializa el USART.
	parametros:
	unsigned int baudrate -> velocidad de trasmision del USART
	enum USART_IN_RX_COMPLETA value_TXCIE -> constantes que activan o desactivan la interrupcion especificada
*/
void USART_init( unsigned int baudrate, enum USART_INT_RX_COMPLETA value_RXCIE, enum USART_INT_TX_COMPLETA value_TXCIE, enum USART_INT_UDR_VACIO value_UDRIE );

/*
	metodo que espera hasta que exista una trama de datos que leer, por lo tanto
	bloquea el flujo del programa
*/
unsigned char USART_receive( void );

/*
	metodo que trasmite un dato 
*/
void USART_transmit( uint8_t data );

/*
	Metodo que trasmite una cadena de caracteres
	de longitud maxima de 64 caracteres
*/
void USART_transmit_string( char s[] );

#endif /* USART_H_ */