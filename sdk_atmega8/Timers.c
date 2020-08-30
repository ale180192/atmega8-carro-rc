/*
 * Timers.c
 *
 * Created: 17/03/2016 08:16:05 a. m.
 *  Author: JLB
 */ 

#define F_CPU	1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Timers.h"



void timer0_init_modo_normal( enum TIMER_0_1_PRESCALER relog_prescaler_select, enum TIMER_0_1_PRESCALER value_TOIE0 ){
		TIMSK|= (  value_TOIE0<<TOIE0  ); // activa interrupcion
		TCCR0|=relog_prescaler_select;
		if(value_TOIE0==1)
		sei();
		TCNT0=0;	
}

void timer2_init_modo_normal( enum TIMER2_PRESCALER relog_prescaler_select, enum TIMER_INTERRUPCION value_TOIE2, 
							 enum TIMER_INTERRUPCION value_OCIE2 ){
		TIMSK |= (value_TOIE2<<TOIE2); // activa interrupcion
		TIMSK |= (value_OCIE2<<OCIE2); // activa interrupcion
		TCCR2|=relog_prescaler_select;
		if(		(value_TOIE2==1) ||  (value_OCIE2==1)	)
		sei();
		TCNT2=0;
		
}


void timer2_init_modo_pwm_rapido( enum TIMER_0_1_PRESCALER relog_prescaler_select, enum TIMER_0_1_PRESCALER value_TOIE2,
								  enum TIMER_0_1_PRESCALER value_OCIE2 ){
	TIMSK |= (value_TOIE2<<TOIE2); // activa interrupcion
	TIMSK |= (value_OCIE2<<OCIE2); // activa interrupcion
	TCCR2|=relog_prescaler_select;
	TCCR2 |= (	(1<<WGM21)|(1<<WGM20)	); // se establece el modo pwm rapido
	TCCR2 |= (1<<COM21); // se establece la salida del comparador como no inversora-toggle	
	if(		(value_TOIE2==1) ||  (value_OCIE2==1)	)
	sei();	DDRB|=(1<<PB3); // salida pwm, es nesesario configurarlo como salida el pin
	TCNT2=0;
}

void timer2_desactivar(){	
	 SFIOR|=(1<<PSR2); // restablece el prescaler poniendolo a cero y por lo tanto desactivando el timer
}


/************************************************************************
* USO DEL TIMER EN MODO CTC
************************************************************************/


void Timer2_CTCMode(void)
{
	TCCR2 |= 1 << WGM21; //Configura Timer2 para el modo CTC (tabla 42 pag.115)
	OCR2 = 124; //fosc=1Mh, T=1ms N=(1ms*1Mhz)/256=3.9 =>8 (valor de 2xN) (Fórmula en pag.110)
				//OCR2 = ((1ms*1Mhz)/8)-1 = 124 (Fórmula en pag.109)
	
	TCCR2 |= (1 << CS21); //Activa Timer, CS01= 1 prescaler(clk/8)
	
	while (1)
	{
		//La bandera OCF2 del registro TIFR sé pone en 1 cuando TimerCounter2 es igual a OCR2
		if (TIFR & (1 << OCF2)) //Prueba si llegó a la cuenta
		{
			PORTD ^= 1<<PIND3; //Usar PD3 para observar la salida (inicializa el PID3 en IO_PORTs.c)
			TIFR =  (1<< OCF2); //Regresa la bandera a 1 (set) CTC
		}
	}
}

/************************************************************************
* USO DEL TIMER EN MODO CTC Y CON INTERRUPCIONES
************************************************************************/


/***Fin de rutina***/
void Timer1_CTCMode_WithInterrupt(void)
{
	
	TCCR1B |= 1<<WGM12; //Configura timer1 para el modo CTC (tabla 39, pag.97)
	TCCR1B |= 1<<CS11;	//Configura prescaler=8 (tabla 40, pag.99) de acuerdo al cálculo:
						//fosc=1Mh, T=100ms N=(100ms*1Mhz)/65535=1.52 =>8 (valor de N)
	
	OCR1A |= 12499;		//Valor a comparar OCR1A=((100ms*1Mhz)/8)-1 = 12499
	
	TCNT1 = 0;			//Inicia contador
	
	TIMSK |= 1<<OCIE1A;	//Habilita interrupciones de comparación
	
	sei();				//Habilita las interrupciones globales
	
}

/************************************************************************
* USO DEL TIMER EN MODO CTC Y SALIDA EN OC1A
************************************************************************/

void Timer1_CTCMode_NonPWM(void)
{
	//Usa PB1 (OC1A) como salida (definir el PINB1--> salida en IO_PORTs.c)
	
	TCCR1B |= 1<<WGM12; //Configura timer1 para el modo CTC (tabla 39, pag.98)
	TCCR1B |= 1<<CS11;	//Configura prescaler=8 (tabla 40, pag.99) de acuerdo al cálculo:
						//fosc=1Mh, T=100ms N=(100ms*1Mhz)/65535=1.52 =>8 (valor de N)
	
	TCCR1A |= 1<<COM1A0; //Configura OC1A pin en modo toggle (tabla 38, pag.97)
	
	OCR1A |= 12499;		//Valor a comparar OCR1A=((100ms*1Mhz)/8)-1 = 12499
	
	TCNT1 = 0;			//Inicia contador
}

/************************************************************************
* USO DEL TIMER EN MODO PWM
************************************************************************/


/*
	*poner pin OC1x como salida
	
*/
void Timer1_FasPWMMode(void)
{	
	// define pin OC1A(PB1) y OC1B(PB2) como salida. De estos pines se obtiene la señal PWM
	DDRB|=(		(1<<PB1) | (1<<PB2)	);
	
	TCCR1A = 0;			//Deshabilita PWM en el TIMER1
	TCCR1B = 0;
	
	//Define modo FAST PWM, cuenta hasta ff. Modo 5 de la tabla 39-pag.97 de la hoja de datos
	TCCR1A |= (1 << WGM10);
	TCCR1B |= (1 << WGM12);
	
	//No prescaling. tabla 40 pag. 90
	TCCR1B |= 1 << CS10;
	
	// no inverting mode (COM1A1=1, COM1A0=0). Se activan las dos salidas A y B. Tabla 37 pag. 96
	TCCR1A |=( (1<<COM1A1)|(1<<COM1B1) );

}