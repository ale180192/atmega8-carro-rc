/*
 * WDT.c
 *
 * Created: 29/03/2016 08:36:17 a. m.
 *  Author: JLB
 */ 
#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>

/************************************************************************
* USO DEL WATCHDOG 
* -Espera en el primer "while" hasta que se oprima el botón, mientras, 
*  el LED aparece encendido.
* -Se habilita el wd, está activo y necesita ser "reseteado" por lo menos 
*  cada 2s (WDTO_2S) para evitar que el MCU sea "reseteado".
* -Mientras mantenemos oprimido el botón, el LED enciende y apaga por 100ms 
*  y el wd es "reseteado cada vez"
* -Cuando soltamos el botón, el programa cae en el "while infinito" (para
*  indicarlo, el LED se apaga), pero, debido a que el wd ya no es "reseteado",
*  después de 2 segundos (WDTO_2S) provocará un reset al MCU, el programa
* iniciará y volveremos a ver el LED encendido.
************************************************************************/
void WDT_example(void)
{
	//Usar PB5 para observar la salida (inicializa el PB5 en IO_PORTs.c)	
	//Usar el PD2 como entrada (inicializa el PD2 en IO_PORTs.c)
		
	while ((PIND & (1<<PD2)) >= 1)//Espera hasta que se presione el botón
	{
		PORTB = 0 << PINB5; //LED encendido.
	}
	wdt_enable(WDTO_2S); //Habilita el wd y define 2s para enviar reset al MCU
	
	while((PIND & (1<<PD2)) == 0)//Permanece en el ciclo mientras esté presionado el botón
	{
		wdt_reset(); //Reset al wd
		
		PORTB ^= 1 << PINB5; //LED enciende 50ms y apaga 50ms
		_delay_ms(50);
	}
	while(1) //Ciclo infinito
	{
		PORTB |= 1 << PINB5;//Espera hasta que se presione el botón
	} /*lock up to allow WDT to time out*/
}
