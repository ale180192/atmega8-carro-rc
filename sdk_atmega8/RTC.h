/*
 * RTC.h
 *
 * Created: 04/05/2016 08:55:11 p. m.
 *  Author: Josè Luis Barbosa
 */ 


#ifndef RTC_H_
#define RTC_H_

#define  RTC_DIRECCION_ESCRITURA	0b11010000
#define  RTC_DIRECCION_LECTURA	0b11010001
#define  RTC_DIRECCION_REGISTRO_SEGUNDOS	0x00
#define  RTC_DIRECCION_REGISTRO_MINUTOS	0x01
#define  RTC_DIRECCION_REGISTRO_HORAS	0x02
#define  RTC_DIRECCION_REGISTRO_DIA_SEMANA	0x03
#define  RTC_DIRECCION_REGISTRO_DIA_MES	0x04
#define  RTC_DIRECCION_REGISTRO_MES	0x05
#define  RTC_DIRECCION_REGISTRO_ANIO 0x06
#define  RTC_DIRECCION_REGISTRO_CONTROL	0x07

#define RTC_PIN_SQW_OUT_HIGH	0b10000000
#define RTC_PIN_SQW_OUT_LOW	0b00000000


enum RTC_MODE{RTC_MODE_24HRS=0,RTC_MODE_12HRS, RTC_MODE_12HRS_AM, RTC_MODE_12HRS_PM};



 void rtc_write(uint8_t dato, uint8_t RTC_DIRECCION_REGISTRO);
  
 uint8_t rtc_read(uint8_t direcion_registro);

 
 void rtc_init(void);
 
 /*
	Establece la hora del rtc, pasandole como ´parametros la hora en un formato de 12 o 24 hrs, los minutos
	y los segundos. Cada valor se paso descompuesto en unidades y decenas
 */
void rtc_set_hora(uint8_t seg_decenas, uint8_t seg_unidades, uint8_t min_decenas, uint8_t min_unidades,
uint8_t horas_decenas, uint8_t horas_unidades, enum RTC_MODE modo_12_24_hrs);


/*
	Establece la fecha del rtc. SE le pasan como parametros el dia de la semana[1-7], el dia del mes[1-31], 
	el mes de año[1-12] y el año[00-99]
*/
void rtc_set_fecha(uint8_t dia_semana, uint8_t dia_mes, uint8_t mes, uint8_t anio);

 
 
 
 
 /*
	Funcion que retorna las decenas de los minutos o segundos dependiendo si se le pasa
	como parametro el bit de segundos o minutos.
	parametros:
	uint8_t value_bcd-> Byte que contiene tanto las unidades como las decenas en formato BCD de los minutos o segundos
	retorno:
	uint8_t value_decenas -> byte en formato binario que contiene el valor de las decenas
 */ 
  uint8_t rtc_get_min_seg_formato_bin_decena(uint8_t value_bcd);
  
   /*
	Funcion que retorna las unidades de los minutos o segundos dependiendo si se le pasa
	como parametro el bit de segundos o minutos.
	parametros:
	uint8_t value_bcd-> Byte que contiene tanto las unidades como las decenas en formato BCD de los minutos o segundos
	retorno:
	uint8_t value_decenas -> byte en formato binario que contiene el valor de las unidades
 */
  uint8_t rtc_get_min_seg_formato_bin_unidad(uint8_t value_bcd);

/*
	Funcion que retorna el valor actual de los segundos en formato binario-rango de [00-59]
	parametros:
	ninguno
	retorno:
	uint8_t segundos_binario -> Byte que contiene el valor de los segundos en formato binario
*/
void rtc_imprimir_segundos();

/*
	Funcion que retorna el valor actual de los minutos en formato binario-rango de [00-59]
	parametros:
	ninguno
	retorno:
	uint8_t minutos_binario -> Byte que contiene el valor de los minutos en formato binario
*/
void rtc_imprimir_minutos();
/*
	las horas se pueden configurar en modo de 12 o 24 horas, esto se establece en el bit 6.
	High=12hrs, Low=24 hrs, para el modo de 12 hrs el bit 5 es el de AM/PM, si es High se configura como PM
	En el modo de 24 hrs el bit 5 es el bit que contiene valores de las unidades
	
*/
void rtc_imprimir_hora(enum RTC_MODE value_mode);

/*
	devuelve uno si la hora es PM y 0 si es AM
*/
uint8_t rtc_hora_is_PM();

int RTC_Example();

/*
	Funcion que regresa el valor del mes. Rango de 0 a 31 en formato en binario
*/
uint8_t rtc_get_dia_del_mes();
/*
	Funcion que regresa el valor de la semana. Rango de 0 a 7 en formato en binario
*/
uint8_t rtc_get_dia_semana();

/*
	Funcion que regresa el valor del mes del año. Rango de 0 a 12 en formato en binario
*/
uint8_t rtc_get_mes_anio();

/*
	Funcion que regresa el valor del año. Rango de 0 a 99 en formato en binario
*/
uint8_t rtc_get_anio();

/*
	Funcion que establece los sugundos.
*/
void rtc_set_segundos(uint8_t value_segundos_unidades, uint8_t value_segundos_decenas);
/*
	Funcion que establece los minutos.
*/
void rtc_set_minutos(uint8_t value_minutos_unidades, uint8_t value_minutos_decenas);

/*
	Funcion que establece las horas en un modo especifico, ya sea 12 hrs o 24 hrs
*/
void rtc_set_horas(uint8_t value_horas_unidades,uint8_t value_horas_decenas, enum RTC_MODE);

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




#endif /* RTC_H_ */