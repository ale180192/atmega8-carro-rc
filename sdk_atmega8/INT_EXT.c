/*
 * INT_EXT.c
 *
 * Created: 15/03/2016 07:07:39 a. m.
 *  Author: JLB
 */ 
#include <avr/interrupt.h>
#include <util/delay.h>





void int0_init(void)
{
	MCUCR |= ( 1<<ISC11); //Defino nivel alto a bajo
	GICR |= 1 << INT0; //Activa interrupción 0
	sei(); //Habilita interrupciones generales (sei())
}

void int1_init(void)
{
	MCUCR |= 1 << ISC11; //Defino nivel alto a bajo
	GICR |= 1 << INT1; //Activa interrupción 1
	sei(); //Habilita interrupciones generales (sei())
}

