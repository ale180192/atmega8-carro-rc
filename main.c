/*
 * Carro.c
 *
 * Created: 20/05/2016 14:53:14
 * Author :
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#include "sdk_atmega8/USART.h"
#include "sdk_atmega8/Timers.h"
//#include "sdk_atmega8/lcd_4Bits_I2C.h"
//#include "sdk_atmega8/RTC.h"
//#include "sdk_atmega8/INT_EXT.h"

// define velocidad de trasmision -> 9600 para la comunicacion con el BLUETOOTH
#define BAUD_RATE 9600 
// define el valor que debe tener el registro UBRR para lograr un baud rate de 9600. Formula de la hoja de datos                                  
#define UBRR_VALUE (	(F_CPU)/(BAUD_RATE*8UL)-1	) 
// define la variacion de velocidad que tendra algun motor para poder girar hacia alfuga direccion   
#define SENSIBILIDAD_GIRO 70

// constantes para manipular los leds. Prenderan cada ves que el usart reciba un valor
#define LED_DDR	DDRB
#define LED_PORT PORTB
#define LED_VELOCIDAD PB3
#define LED_DIRECCION PB4
#define LED_ACELERACION PB5

// motor izquierdo
#define IN1 PD4
#define IN2 PD5
#define MOTOR_IZQUIERDO OCR1B

// motor derecho
#define IN3 PD6
#define IN4 PD7
#define MOTOR_DERECHO OCR1A


/*
	Variables generales
*/  
unsigned char velocidad=0; //al macena la velocidad configurada para los motores [0-255]
unsigned char esta_corriendo=0; // almacena el estado del carro,0 si esta parado y 1 si esta corriendo
uint8_t mostrar_hora=1;

/*
	Vectores de interrupcion
*/
ISR(USART_RXC_vect){ // interrupcion que se ejecuta cuando se recibe un nuevo dato por el usart
	mostrar_hora=0;
	int temp=UDR; // se leen datos para limpiar el flag de interrupcion
	UCSRA&=(		~(1<<RXCIE)		); // se desactivan interrupciones
}


/*
	Funciones generales

*/
/*
	gira el carro a la izquierda. Esto se logra disminuyendo la velocidad del motor izquierdo
	 y aumentando la velocidad del motor derecho.
*/
void carro_girar_izquierda();

/*
	gira el carro a la derecha. Esto se logra disminuyendo la velocidad del motor derecho
	 y aumentando la velocidad del motor izquierdo.
*/
void carro_girar_derecha();

/*
	acelerar y reversa giran los motores a la velocidad que este esteblecida
*/
void carro_acelerar();
void carro_reversa();

// establece la velocodad de los motores en cero
void carro_frenar();


// configura los motores para que giren hacia adelante o hacia atras
void carro_avanzar();
void carro_retroceder();


/*
	declaracion de variables
*/

// enumeracion que contiene todos los posibles numeros enteros que recibira el puerto RX del USART. Mayores 
// a 10 configuran la velocidad
enum CARRO{CARRO_ACELERAR = 0, CARRO_APAGAR, CARRO_IZQUIERDA, CARRO_DERECHA, CARRO_REVERSA, CARRO_MOSTRAR_HORA,
			CARRO_DORMIR} ;



int main(void)
{
	
	/*
		configuracion leds prueba
	*/
	LED_DDR|=(		(1<<LED_ACELERACION)|(1<<LED_DIRECCION)|(1<<LED_VELOCIDAD)		);
	// pines de salida para manejar el puente H de cada motor.
	DDRD|=(1<<IN1)|(1<<IN2);
	DDRD|=(  (1<<IN3)|(1<<IN4)  );	
	/*
		Inicializacion de componentes
	*/
	
	// se establece la velocidad de trasmision, y las interrupciones desactivadas
	USART_init(UBRR_VALUE,USART_INT_RX_COMPLETA_OFF,USART_INT_TX_COMPLETA_OFF,USART_INT_UDR_VACIO_OFF);	
	// inicializa el lcd
	//lcd_start();
	// inicializa el timer1 sin interrupciones y el timer2 con interrupcion de overflow y un prescaler
	Timer1_FasPWMMode();
	// inicializa el rtc
	//rtc_init();	
	// configura valor en el registro OCR1A(MOTOR_DERECHO) y OCR1B(MOTOR_IZQUIERDO)
	MOTOR_DERECHO=velocidad;
	MOTOR_IZQUIERDO=velocidad;

	
// 	lcd_write_string("UNAM-FESC ITSE");
// 	lcd_set_posicion_cursor(1,2);
// 	lcd_write_string("MICROCONTROLADORES");
// 	_delay_ms(1500);
// 	lcd_clear();
// 	lcd_write_string("Menu de opciones");
// 	lcd_set_posicion_cursor(2,2);
// 	lcd_write_string("config  ");
// 	lcd_write_string("Iniciar");
	
	
	
	unsigned char comando=0; // variable que guarda el valor recibido por el pin RX
    while (1) 
    {
		// se espera un a que llegue un dato por el pin RX del modulo USART
		comando=USART_receive();
		//lcd_clear();
				
		switch(comando){   
			
			case CARRO_ACELERAR: 
				esta_corriendo=1;
				carro_acelerar();
				// prende y apaga led correspondiente
				LED_PORT|=(1<<LED_ACELERACION);
				_delay_ms(100);
				LED_PORT&=(		~(1<<LED_ACELERACION)	);
				//lcd_write_string("ruun runnn ");
				break;
				
			case CARRO_APAGAR:
				esta_corriendo=0;
				carro_frenar();	
				// prende y apaga led correspondiente
				LED_PORT|=(1<<LED_ACELERACION);
				_delay_ms(100);
				LED_PORT&=(		~(1<<LED_ACELERACION)	);	
				//lcd_write_string(" Carro detenido ");	
				break;	
				
			case CARRO_IZQUIERDA:
				carro_girar_izquierda();
				LED_PORT|=(1<<LED_DIRECCION);
				_delay_ms(100);
				// prende y apaga led correspondiente
				LED_PORT&=(		~(1<<LED_DIRECCION)	);	
				//lcd_write_string(" dir. izquierda ");			
				break;
				
			case CARRO_DERECHA:
				LED_PORT|=(1<<LED_DIRECCION);
				_delay_ms(100);
				LED_PORT&=(		~(1<<LED_DIRECCION)	);
				carro_girar_derecha();	
				//lcd_write_string(" dir. derecha  ");				
				break;
				
			case CARRO_REVERSA:
				esta_corriendo=1;
				carro_reversa();
				// prende y apaga led correspondiente
				LED_PORT|=(1<<LED_ACELERACION);
				_delay_ms(100);
				LED_PORT&=(		~(1<<LED_ACELERACION)	);			
				//lcd_write_string("De reversa mami ");
				break;	
				
			case CARRO_MOSTRAR_HORA:
			// activa las interrupciones del RX. Es para salir del bucle cuando llegue un nuevo comando
				mostrar_hora=1;
				// prende y apaga led correspondiente
				LED_PORT|=(1<<LED_ACELERACION);
				_delay_ms(100);				
				LED_PORT&=(		~(1<<LED_ACELERACION)	);	
				//lcd_write_string("Hora: ");
				while(mostrar_hora){
// 				 // se activan las interrupciones durante 500 milisegundos para evitar que se 
// 				 // ejecuten durante una comunicacion i2c
//  					UCSRB|=(1<<RXCIE);
// 					_delay_ms(500);
// 					UCSRB&=(  ~(1<<RXCIE)  );
// 					lcd_set_posicion_cursor(7,1);
// 					rtc_imprimir_hora(RTC_MODE_12HRS);
// 					lcd_write_string(":");
// 					rtc_imprimir_minutos();
// 					lcd_write_string(":");
// 					rtc_imprimir_segundos();
				}
				break;
				
			case CARRO_DORMIR:{ // entra en modo sleep power down
// 				LED_PORT|=(1<<LED_DIRECCION);
// 				_delay_ms(500);
// 				int i;
// 				LED_PORT&=(		~(1<<LED_DIRECCION)		);
// 				lcd_write_string("Durmiendo");
// 				for(i=0;i<5;i++){
// 					lcd_write_string(".");
// 					_delay_ms(300);
				}
				break;				
				
			default:			
			if(comando>=10){ // es un valor de la velocidad
					velocidad=comando;
					LED_PORT|=(1<<LED_VELOCIDAD);
					_delay_ms(100);
					LED_PORT&=(		~(1<<LED_VELOCIDAD)	);
				//lcd_write_string("conf. velocidad");				
			} // fin de if		
			break;		
			
				
		} // fin de switch
	} // fin de while
	
}// fin de main




void carro_girar_izquierda(){
	if(	esta_corriendo==0   ){ // si esta parado el carro solo se arranca el motor derecho
		MOTOR_DERECHO=SENSIBILIDAD_GIRO+100;
		_delay_ms(200);	
		MOTOR_DERECHO=0;	
	}else{ // si el carro esta en marcha se disminuye la velocidad del motor izquierdo
		MOTOR_IZQUIERDO-=SENSIBILIDAD_GIRO;
		_delay_ms(200);
		MOTOR_IZQUIERDO+=SENSIBILIDAD_GIRO;		
	}
	
}

void carro_girar_derecha(){
	if( esta_corriendo==0  ){ // si esta parado el carro solo se arranca el motor izquierdo
		MOTOR_IZQUIERDO=SENSIBILIDAD_GIRO+100;		
		_delay_ms(200);
		MOTOR_IZQUIERDO=0;
		}else{ // si el carro esta en marcha se disminuye la velocidad del motor derecho
		MOTOR_DERECHO-=SENSIBILIDAD_GIRO;
		_delay_ms(200);
		MOTOR_DERECHO+=SENSIBILIDAD_GIRO;
	}
}


void carro_acelerar(){
	
	MOTOR_IZQUIERDO=velocidad;
	MOTOR_DERECHO=velocidad;
	carro_avanzar();	
}


void carro_frenar(){
	MOTOR_DERECHO=0;
	MOTOR_IZQUIERDO=0;	
}

/*
	Aceleran los motores en modo inverso
*/
void carro_reversa(){
	MOTOR_DERECHO=velocidad++;
	MOTOR_IZQUIERDO=velocidad++;	
	carro_retroceder();
}


void carro_avanzar(){
	// Se usan IN1=1 y IN2=0 para manejar la direccion de giro del motor izquierdo
	PORTD|=(1<<IN1); // giro hacia adelante
	PORTD&=(	~(1<<IN2)		);
	// Se usan IN3=1 y IN4=0 para manejar la direccion de giro del motor derecho.
	PORTD|=(1<<IN3); // giro hacia adelante
	PORTD&=(	~(1<<IN4)		);
}

void carro_retroceder(){
	// Se usan IN1=0 y IN2=1 para manejar la direccion de giro del motor izquierdo
	PORTD&=(	~(1<<IN1)		);
	PORTD|=(1<<IN2); 
		
	// Se usan IN3=0 y IN4=1 para manejar la direccion de giro del motor derecho.
	PORTD&=(	~(1<<IN3)		);
	PORTD|=(1<<IN4); 
}

