/*
 * ADC.c
 *
 * Created: 15/03/2016 08:05:29 a. m.
 *  Author: JLB
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "ADC.h"



/************************************************************************
* USO DEL ADC SIN INTERRUPCIONES
* Las funciones ADC_WithoutInterrupt y Read_ADC, se utilizan de manera
* conjunta. La primera inicia el ADC y la segunda se debe llamar cada
* vez que se quiere leer un dato del ADC.
************************************************************************/
void ADC_WithoutInterrupt(void)
{
	ADMUX=(1<<REFS0);		//Selecciona el voltaje de referencia REF1=0, REFS0=1
							//(AVCC with external capacitor at AREF pin)
							//Entrada AVcc= 5v y Aref= con un capacitor a GND
							//Internamente: Vref=0-5v
	ADCSRA=	(1<<ADEN)|							//Habilita el convertidor
			(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);	//Prescaler div factor =128 
												//fo=1,000,000/128 ~ 7Khz
}

uint16_t Read_ADC(void)
{
	//Seleccciona el canal del ADC (entre 0-5)
	ADMUX &=0b11111000;

	//Comienza la conversion
	ADCSRA|=(1<<ADSC);

	//Espera a que la conversion se complete
	while(!(ADCSRA & (1<<ADIF)));
	
	//poner en "0" la bandera, para la siguiente conversion
	ADCSRA|=(1<<ADIF);

	//Regresa el valor de la conversion en la funcion Read_ADC.
	return(ADC);
}

/************************************************************************
* USO DEL ADC CON INTERRUPCIONES
************************************************************************/

/*
// / ***Rutina de atención a las interrupciones del convertidor*** /
// ISR (ADC_vect)
// {
// 	char ADCResult [4];
// 	uint8_t LowPart = ADCL;	//10-bit resolution
// 	uint16_t TenBitResult = ADCH << 2 | LowPart >> 6; //10-bit resolution
// 	
// / *	
// 	itoa(TenBitResult,ADCResult,10);	//10-bit resolution
// 	//	itoa(ADCH,ADCResult,10); //8-bit resolution
// 	gotoXy_4b(1,1);
// 	Send_A_String(ADCResult);
// 	Send_A_String(" ");
// 	//Comenzar la conversión
// 	ADCSRA |= 1<<ADSC;
// 	* /
// }
*/
/***Fin de rutina***/


void adc_interrupcion_activa_init(enum ADC_CANAL mi_ADC_CANAL){
	ADCSRA |= 1<<ADEN;	// activa el adc
	
	ADMUX|=mi_ADC_CANAL;	// selecciona canal
	ADMUX|=1<<REFS0; // referencia de voltaje AVcc +5v segun tabla 74 pag 199
	ADMUX|=1<<ADLAR;	// ajusta los bits de conversion a la izquierda	
		
};

void adc_enable_conversion(void){
	ADCSRA|= 1<<ADSC;

}

void adc_enable_conversion_modo_funcionamiento_libre(void){
	ADCSRA|= 1<<ADFR;
}


