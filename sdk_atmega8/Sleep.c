/*
 * Sleep.c
 *
 * Created: 31/03/2016 08:05:01 p. m.
 *  Author: JLB
 */ 
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define LED_DDR	DDRB
#define LED_PORT PORTB
#define LED_VELOCIDAD PB3
#define LED_DIRECCION PB4
#define LED_ACELERACION PB5
//------------------------------------

int contador;
int inicia_sleep(void)
{
	MCUCR &= (0 << ISC01) & (0 <<ISC00);
	GICR |= (1 << INT0);
	
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	//cli();
	//if (contador >= 100);
	//{
		sleep_enable();
		sei();
		sleep_cpu();
		//sleep_disable();
	//}
	sei();
	}
	

/*int Sleep_example(void)
{
	//Usar PB4 para observar la salida (inicializa el PB5 en IO_PORTs.c)
	//Usar PB5 para observar la salida (inicializa el PB5 en IO_PORTs.c)
	//Usar el PD2 como entrada (inicializa el PD2 en IO_PORTs.c)
	
	// level interrupt INT0 (low level)
	MCUCR &= ~((1 << ISC01) | (1 << ISC00));

	// infinite main loop
	while (1)
	{
		// trigger leds for testing
		PORTB ^= (1 << PB4); //Enciende LED azul
		_delay_ms(500);

		// enable external interrupt
		GICR |= (1 << INT0);

		// set sleep mode
		set_sleep_mode(SLEEP_MODE_PWR_DOWN);

		// sleep_mode() has a possible race condition
		sleep_enable();
		sei();
		sleep_cpu();
		sleep_disable();
		
		// waking up...
		// disable external interrupt here, in case the external low pulse is too long
		GICR &= ~(1 << INT0);

		// disable all interrupts
		cli();
	}
}
*/

