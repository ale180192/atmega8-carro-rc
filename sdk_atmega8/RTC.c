/*
 * RTC.c
 *
 * Created: 04/05/2016 08:54:58 p. m.
 *  Author: Josè Luis Barbosa
 */ 
#include <util/delay.h>
#include <avr/io.h>

#include "I2C.h"
#include "RTC.h"
#include "lcd_4Bits_I2C.h"

 void rtc_write(uint8_t dato, uint8_t RTC_DIRECCION_REGISTRO){
	 I2C_START();
	 I2C_WRITE(RTC_DIRECCION_ESCRITURA);
	 I2C_WRITE(RTC_DIRECCION_REGISTRO);
	 I2C_WRITE(dato);
	 I2C_STOP();
	 _delay_ms(10);
 }
 
  uint8_t rtc_read(uint8_t dev_loc)
  {
	  uint8_t ch;

	  I2C_START();

	  I2C_WRITE(RTC_DIRECCION_ESCRITURA); // se escribe la direccion que tiene para escribir en el rtc
	  I2C_WRITE(dev_loc);	// se escribe la direccion del registro a escribir para apunter a este registro

	  I2C_START();	// un segundo start para empezar a leer desde el ultimo registro apuntado
	  I2C_WRITE(RTC_DIRECCION_LECTURA);		// se escribe la dirrecion del rtc que tiene para leer de el
	  ch = read_i2c();	// Se lee el valor del registro apuntado

	  I2C_STOP();	// condicion de stop para finalizar la consulta
	  return ch;
  }
 
 void rtc_init(void){
	 I2C_init(I2C_PRESCALER_1,I2C_INTERRUPCIONES_OFF,0);
 }
 
void rtc_set_hora(uint8_t seg_decenas, uint8_t seg_unidades, uint8_t min_decenas, uint8_t min_unidades,
					uint8_t horas_decenas, uint8_t horas_unidades, enum RTC_MODE modo_12_24_hrs){
	
	rtc_set_segundos(seg_unidades,seg_decenas);
	rtc_set_minutos(min_unidades,min_decenas);
	rtc_set_horas(horas_unidades,horas_decenas,modo_12_24_hrs);
}


void rtc_set_fecha(uint8_t dia_semana, uint8_t dia_mes, uint8_t mes, uint8_t anio){
	
}




uint8_t rtc_get_min_seg_formato_bin_decena(uint8_t val_bcd){
	uint8_t value_binario=0;
	value_binario|=(		(  (0b11110000)&(val_bcd)  )>>4			);
	return value_binario;
}

 uint8_t rtc_get_min_seg_formato_bin_unidad(uint8_t val_bcd){
	 uint8_t value_binario=0;
	 value_binario|=(	(0b00001111)&(val_bcd)		);
	 return value_binario;
 }
 
void rtc_imprimir_segundos(){
	uint8_t segundos_bcd=rtc_read(RTC_DIRECCION_REGISTRO_SEGUNDOS);
	uint8_t segundos_binario[]={0,0};
	segundos_binario[0]=rtc_get_min_seg_formato_bin_decena(segundos_bcd);
	segundos_binario[1]=rtc_get_min_seg_formato_bin_unidad(segundos_bcd);
	lcd_data(segundos_binario[0]+48);
	lcd_data(segundos_binario[1]+48);
}

void rtc_imprimir_minutos(){

	uint8_t minutos_bcd=rtc_read(RTC_DIRECCION_REGISTRO_MINUTOS);
	uint8_t minutos_binario[]={0,0};
	minutos_binario[0]=rtc_get_min_seg_formato_bin_decena(minutos_bcd);
	minutos_binario[1]=rtc_get_min_seg_formato_bin_unidad(minutos_bcd);
	lcd_data(minutos_binario[0]+48);
	lcd_data(minutos_binario[1]+48);

} 

void rtc_imprimir_hora(enum RTC_MODE value_mode){

	uint8_t horas_bcd=rtc_read(RTC_DIRECCION_REGISTRO_HORAS);
	//uint8_t horas_binario=(			horas_bcd/16 * 10 + horas_bcd%16		);
	char str_horas[2];
	//itoa(horas_binario,str_horas,10);
// 	lcd_write_string(str_horas);
// 	
// 	
// 	//horas_binario|=(		(0b00001111) & (horas_bcd)		); // entero de 0 a 4 o de 0 a 2 en el modo 12 hrs
// 	if(		(	(1<<4)&(horas_bcd)	)==1		) // si esta en high el bit cuatro se suman 10 hrs
// 		horas_binario+=10;
// 	// si el modo es de 24 hrs y el bit 5 esta establecido se suman 10 hrs
// 	if(		(value_mode==RTC_MODE_24HRS) && (	 (  (1<<5)&(horas_bcd)  ) == 1		)	){
// 		horas_binario+=10;
// 		
// 	}
// 	lcd_data(horas_binario+48);
} // fin funcion
		
		
		
uint8_t rtc_hora_is_PM(){	
	uint8_t horas_bcd=rtc_read(RTC_DIRECCION_REGISTRO_HORAS);
	// si se obtiene la hora en modo de 12 hrs y el bit 5 esta en high es PM	
	if(		 (  (1<<5)&(horas_bcd)  ) == 1	 	)
		return 1;
	else
		return 0;
}

uint8_t rtc_get_dia_del_mes(){
	uint8_t dia_bcd=rtc_read(RTC_DIRECCION_REGISTRO_DIA_MES);
	uint8_t dia_binario=0;
	dia_binario=(		(0b00001111)&(dia_bcd)		); // valor del 0 al 9
	dia_binario+=(		(dia_binario>>4)*10		); // el valor de las decenas, esta en un intervalo de 0 a 3.
	return dia_binario;	
}

uint8_t rtc_get_dia_semana(){
	uint8_t dia_bcd=rtc_read(RTC_DIRECCION_REGISTRO_DIA_SEMANA); // valor de 0 a 7
	return dia_bcd;
}

uint8_t rtc_get_mes_anio(){
	uint8_t mes_bcd=rtc_read(RTC_DIRECCION_REGISTRO_MES);
	uint8_t mes_binario=0;
	mes_binario=(		(0b00001111)&(mes_bcd)		);// valor entre 0 y 9
	mes_binario+=(		(mes_bcd>>4)*10		); // valor de las decenas. Rango de 0 a 1
	
	return mes_binario;	
}

uint8_t rtc_get_anio(){
	uint8_t anio_bcd=rtc_read(RTC_DIRECCION_REGISTRO_ANIO);
	uint8_t anio_binario=0;
	anio_binario=(		(0b00001111)&(anio_bcd)		);// valor entre 0 y 9
	anio_binario+=(		(anio_bcd>>4)*10		); // valor de las decenas. Rango de 0 a 9
	
	return anio_binario;
}


/*
	Funciones que escriben en el rtc y configuran el tiempo
*/


/*
	Funcion que establece los sugundos.
*/
void rtc_set_segundos(uint8_t value_segundos_unidades, uint8_t value_segundos_decenas){
	uint8_t segundos_bcd=value_segundos_unidades;
	segundos_bcd|=(value_segundos_decenas<<4);	
	rtc_write(segundos_bcd,RTC_DIRECCION_REGISTRO_SEGUNDOS);
	
}
/*
	Funcion que establece los minutos.
*/
void rtc_set_minutos(uint8_t value_minutos_unidades, uint8_t value_minutos_decenas){
	uint8_t minutos_bcd=value_minutos_unidades;
	minutos_bcd|=(value_minutos_decenas<<4);
	rtc_write(minutos_bcd,RTC_DIRECCION_REGISTRO_MINUTOS);
}

/*
	Funcion que establece las horas en un modo especifico, ya sea 12 hrs o 24 hrs
*/
void rtc_set_horas(uint8_t value_horas_unidades,uint8_t value_horas_decenas, enum RTC_MODE VALUE_RTC_MODE){
	
	uint8_t horas_bcd=value_horas_unidades;
	if(VALUE_RTC_MODE==RTC_MODE_12HRS_PM){
		horas_bcd|=(1<<5); // se establece PM
		horas_bcd|=(value_horas_decenas<<4);	// se establece el bit 4
	}else if(VALUE_RTC_MODE==RTC_MODE_12HRS_AM){
		horas_bcd|=(value_horas_decenas<<4);	// se establece el bit 4
	}else{ // si es el modo 24 hrs
		if(value_horas_decenas==1){ // 
			horas_bcd|=(1<<4);
		}else if(value_horas_decenas==2){
			horas_bcd|=(0b00110000);	// se establece el bit 4 y 5		
		}
	} // fin de else
	rtc_write(horas_bcd,RTC_DIRECCION_REGISTRO_HORAS);
	
}// fin funcion

/*
	Funcion que establece el dia de la semana
*/
void rtc_set_dia_semana(uint8_t value_dia_semana);

/*
	Funcion que establece el mes del año
*/
void rtc_set_mes_anio(uint8_t value_mes_anio);

/*
	Funcion que establece el año
*/
void rtc_set_anio(uint8_t value_anio);


	
		
	
	
	
 
 
 
/*
//   void disp_time_date()
//   {
// 	  uint8_t ch;
// 
// 	  ch = rtc_read(0xd0 , 0x02);
// 	  ch = rtc_read(0xd0 , 0x01);
// 	  ch = rtc_read(0xd0 , 0x00);
// 	  ch = rtc_read(0xd0 , 0x04);
// 	  ch = rtc_read(0xd0 , 0x05);
// 	  ch = rtc_read(0xd0 , 0x06);
// 
//   }
*/
  
/*
   {
	   DDRC =(1 << PC5)|(1 << PC4); //SDA y SCL como salidas
	   I2C_init();
		//Ajusta tiempo
	   rtc_write(0xd0,0x00,0x00); //Segundos
	   rtc_write(0xd0,0x01,0x32); //Minutos
	   rtc_write(0xd0,0x02,0x19); //horas
		//Ajusta fecha
	   rtc_write(0xd0,0x04,0x05); //Día
	   rtc_write(0xd0,0x05,0x05); //Mes
	   rtc_write(0xd0,0x06,0x16); //Año

	   _delay_ms(10000);


	   while(1)
	   {
			disp_time_date();
	   }

   }*/