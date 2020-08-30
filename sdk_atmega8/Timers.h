/*
 * Timers.h
 *
 * Created: 17/03/2016 08:16:20 a. m.
 *  Author: JLB
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_


/* 
Define todas las posibles combinaciones de seleccion de relog y prescala para el timer1 y tinmer2
El relog interno es de 1 MHz o 1 us
*/
enum TIMER_0_1_PRESCALER{TIMER_PRESCALER_NOT_RELOG_INTERNO=1,TIMER_PRESCALER_8_RELOG_INTERNO=2,
					TIMER_PRESCALER_64_RELOG_INTERNO=3, TIMER_PRESCALER_256_RELOG_INTERNO=4,
					TIMER_PRESCALER_1024_RELOG_INTERNO=5, TIMER_PRESCALER_NOT_RELOG_EXTERNO_T0_FLANCO_DESCENDENTE=6,
					TIMER_PRESCALER_NOT_RELOG_EXTERNO_T0_FLANCO_ASCENDENTE=7};
					
enum TIMER2_PRESCALER{TIMER2_PRESCALER_SIN_ESCALA=1, TIMER2_PRESCALER_8, TIMER2_PRESCALER_32, TIMER2_PRESCALER_64,
					  TIMER2_PRESCALER_128, TIMER2_PRESCALER_256, TIMER2_PRESCALER_1024};
					
enum TIMER_INTERRUPCION{TIMER_INTERRUPCION_OFF=0, TIMER_INTERRUPCION_ON=1};

/*
	Inicializa el Timer0 en su unico modo: 'normal'. Pasandole como parametro:
	 1.- la opcion de la fuente de relog-la prescala o divisor de la fuente de relog
	 2.- Opcion de interrupcion de overflow. Esta interrupcion se ejecuta cada que el contador llega a su valor maximo
		de conteo.	 
*/
void timer0_init_modo_normal( enum TIMER_0_1_PRESCALER relog_prescaler_select, enum TIMER_0_1_PRESCALER interrupcion_overflow);



void Timer1_CTCMode_WithInterrupt(void);
void Timer1_CTCMode_NonPWM(void);
void Timer1_FasPWMMode(void);



/*
	Inicializa el Timer2 en modo normal. Pasandole como parametro:
	 1.- la opcion de la fuente de relog-la prescala o divisor de la fuente de relog
	 2.- Opcion de interrupcion de overflow. Esta interrupcion se ejecuta cada que el contador llega a su valor maximo
		de conteo.
	3.- Opcion de interrupcion output compare match. Esta interrupcion se genera cuando el contador TCNT2 tiene el mismo
		valor que el registro OCR2. 
	 
*/
void timer2_init_modo_normal( enum TIMER2_PRESCALER relog_prescaler_select, enum TIMER_INTERRUPCION interrupcion_overflow,
							  enum TIMER_INTERRUPCION interrupcion_comparacion_igualdad);
/*
	Inicializa el Timer2 en modo pwm, es decir, cada que existe una igualdad entre el valor del timer TCNT2
	y el registro OCR2 cambiara el estado de la salida del pin OC2, el conteo del timer sigue y al llegar a su
	valor maximo el pin OC2 cambiara de estado nuevamente. El pin OC2 puede cambiar de cierta manera	configuirando
	 los valores segun la tabla 44 . 
	Recibe como parametros:
	
	 1.- la opcion de la fuente de relog-la prescala o divisor de la fuente de relog
	 2.- Opcion de interrupcion de overflow. Esta interrupcion se ejecuta cada que el contador llega a su valor maximo
		de conteo.
	3.- Opcion de interrupcion output compare match. Esta interrupcion se genera cuando el contador TCNT2 tiene el mismo
		valor que el registro OCR2. 
	 
*/
void timer2_init_modo_pwm_rapido( enum TIMER_0_1_PRESCALER relog_prescaler_select, enum TIMER_0_1_PRESCALER interrupcion_overflow,
								 enum TIMER_0_1_PRESCALER interrupcion_comparacion_igualdad );

/*
	Desactiva el timer2
*/								 
void timer2_desactivar();


void Timer2_CTCMode(void);






#endif /* TIMERS_H_ */