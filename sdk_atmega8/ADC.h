/*
 * ADC.h
 *
 * Created: 15/03/2016 08:05:14 a. m.
 *  Author: JLB
 */ 


#ifndef ADC_H_
#define ADC_H_

void ADC_WithoutInterrupt(void);
uint16_t Read_ADC(void);


/************************************************************************
* USO DEL ADC CON INTERRUPCIONES
************************************************************************/
void ADC_WithInterrupt(void);

enum ADC_CANAL{ADC_CANAL_ADC0=0, ADC_CANAL_ADC1, ADC_CANAL_ADC2, ADC_CANAL_ADC3, ADC_CANAL_ADC4, ADC_CANAL_ADC5};
	
/*
	inicializa el adc pasandole como argumento el canal deseado.
	ajusta los bits de la conversion a la izquierda.
	El prescalador se selecciona a la mas alta frecuencia
	La referencia de voltaje es de 5v. poner capacitor entre el pin arf y gnd
	
*/
void adc_interrupcion_activa_init(enum ADC_CANAL);

/*
	Activa la conversion adc una sola ves. Al terminar la conversion se activa la interrupcion
	correspondiente
*/
void adc_enable_conversion(void);

/*
	Activa la conversion adc en modo funcionamiento libre, es decir una vez que termina de muestreas y
	convertir lo vuelve a hacer siempre. Al terminar la conversion se activa la interrupcion
	correspondiente
*/
void adc_enable_conversion_modo_funcionamiento_libre(void);





#endif /* ADC_H_ */